#include "open62541.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "Classic6dofKine.h"

UA_Boolean running = true;
float q0[6] = { 0,0,0,0,0,0 };
float q[6] = { 0,0,1.570796f,0,1.570796f,0 };
float q_last[6] = { 0,0,0,0,0,0 };
Kine6d pose;
Kine6dSol q_sol;
char ch = '\0';


// 查询节点id的包装函数, 官方用法
static UA_StatusCode translateBrowsePathsToNodeIdsRequest(UA_Client *client, UA_NodeId *returnId, char **paths) {
    UA_StatusCode ret = UA_STATUSCODE_GOOD;
    #define BROWSE_PATHS_SIZE 4
    //char *paths[BROWSE_PATHS_SIZE] = {"myFirstRobot", "link1", "angle", "angleValue"};
    UA_UInt32 ids[BROWSE_PATHS_SIZE] = {UA_NS0ID_ORGANIZES, UA_NS0ID_HASCOMPONENT, UA_NS0ID_HASCOMPONENT, UA_NS0ID_HASCOMPONENT};
    int nsNumOfQualifiedName[BROWSE_PATHS_SIZE] = {1, 2, 2, 2};

    UA_BrowsePath browsePath;
    UA_BrowsePath_init(&browsePath);
    browsePath.startingNode = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    browsePath.relativePath.elements = (UA_RelativePathElement*)UA_Array_new(BROWSE_PATHS_SIZE, &UA_TYPES[UA_TYPES_RELATIVEPATHELEMENT]);
    browsePath.relativePath.elementsSize = BROWSE_PATHS_SIZE;

    for (size_t i = 0; i < BROWSE_PATHS_SIZE; ++i) {
        UA_RelativePathElement *elem = &browsePath.relativePath.elements[i];
        elem->referenceTypeId = UA_NODEID_NUMERIC(0, ids[i]);
        elem->targetName = UA_QUALIFIEDNAME_ALLOC(nsNumOfQualifiedName[i], paths[i]);
    }

    UA_TranslateBrowsePathsToNodeIdsRequest request;
    UA_TranslateBrowsePathsToNodeIdsRequest_init(&request);

    request.browsePaths = &browsePath;
    request.browsePathsSize = 1;
    
    
    UA_TranslateBrowsePathsToNodeIdsResponse response = UA_Client_Service_translateBrowsePathsToNodeIds(client, request);
    
    if (response.responseHeader.serviceResult == UA_STATUSCODE_GOOD) {
        if (response.resultsSize == 1 && response.results[0].targetsSize == 1) {
            UA_NodeId_copy(&response.results[0].targets[0].targetId.nodeId, returnId); // this has problem
            // printf("%u\n", (*returnId).identifier.numeric);
        } else {
            printf("%d\n", response.results[0].targetsSize);
        }
    } else {
        printf("Error: %s\n", UA_StatusCode_name(response.responseHeader.serviceResult));
        ret = response.responseHeader.serviceResult;
    }

    UA_BrowsePath_deleteMembers(&browsePath);
    UA_TranslateBrowsePathsToNodeIdsResponse_deleteMembers(&response);

    return ret;
}

// Deprecated
static UA_StatusCode callMethodGetNodeId(UA_Client *client, char *path, UA_NodeId *returnId) {
    UA_StatusCode retval1;
    UA_String arg = UA_STRING(path);
    UA_Variant input;
    UA_Variant_init(&input);
    UA_Variant_setScalarCopy(&input, &arg, &UA_TYPES[UA_TYPES_STRING]);
    size_t outputSize;
    UA_Variant *output;
    UA_NodeId outNodeId;
    retval1 = UA_Client_call(client, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), UA_NODEID_NUMERIC(1, 62541), 1, &input, &outputSize, &output);
    if (retval1 == UA_STATUSCODE_GOOD) {
        outNodeId = *(UA_NodeId*) output->data;
        UA_NodeId_copy((UA_NodeId*) output->data, returnId);
        printf("%u \n", outNodeId.identifier.numeric);
        UA_Array_delete(output, outputSize, &UA_TYPES[UA_TYPES_VARIANT]);

    } else {
        printf("Method call was unsuccessful, and %x returned values available.\n", retval1);
        
    }

    UA_Variant_clear(&input);
}

static UA_StatusCode writeServerValueDouble(UA_Client *client, const UA_NodeId id, double value) {
    UA_StatusCode retval;
    UA_Double link1_angle_angleValue = value;
    UA_Variant newValue;
    UA_Variant_init(&newValue);
    UA_Variant_setScalar(&newValue, &link1_angle_angleValue, &UA_TYPES[UA_TYPES_DOUBLE]);
    retval = UA_Client_writeValueAttribute(client, id, &newValue);
    if (retval == UA_STATUSCODE_GOOD) {

    }
    return retval;
}

void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

/*
1. 创建一个订阅请求，使用函数UA_Client_Subscriptions_create()去做，会得到一个订阅ID
2. 创建一个监测项请求，这里监测Server，其NodeId是UA_NODEID_NUMERIC(0, 2253)
3. Server能提供很多内容，这里只关注其事件通知器属性，即UA_ATTRIBUTEID_EVENTNOTIFIER
4. 使用UA_EventFilter创建事件过滤器，然后调用setupSelectClauses()来设置我们关心的事件类型及其Property
5. 把设置好的事件过滤器放到监测项请求中
6. 调用UA_Client_MonitoredItems_createEvent()来使用监测项请求去创建监测项，并会得到一个监测项ID
7. 监测项可以看做是订阅内容，例如你订阅了一个up主，这个up主有各种系列的视频，监测项就是指定哪个系列的视频，当up主更新该系列视频，你就会收到通知
*/
#ifdef UA_ENABLE_SUBSCRIPTIONS
const size_t nSelectClauses = 2;

static void handler_events(UA_Client *client, UA_UInt32 subId, void *subContext,
               UA_UInt32 monId, void *monContext,
               size_t nEventFields, UA_Variant *eventFields) 
{
    int robotNo = -1;
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Event triggered received by Robot Client");
    UA_assert(*(UA_UInt32*)monContext == monId);
    for(size_t i = 0; i < nEventFields; ++i) {
        if(UA_Variant_hasScalarType(&eventFields[i], &UA_TYPES[UA_TYPES_UINT16])) {
            UA_UInt16 severity = *(UA_UInt16 *)eventFields[i].data;
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Severity: %u", severity);
        } else if (UA_Variant_hasScalarType(&eventFields[i], &UA_TYPES[UA_TYPES_LOCALIZEDTEXT])) {
            UA_LocalizedText *lt = (UA_LocalizedText *)eventFields[i].data;
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                        "Message: %d", atoi(lt->text.data)); // C语言这个库传字符串有问题，总会多点东西，只好用数字
            robotNo = atoi(lt->text.data);
        }
        else {
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                        "Don't know how to handle type: '%s'", eventFields[i].type->typeName);
        }
    }

    if (robotNo == 1) {

    } else if (robotNo == 2) {
        
    }
}

/*
typedef struct {
    UA_NodeId typeDefinitionId;
    size_t browsePathSize;
    UA_QualifiedName *browsePath;
    UA_UInt32 attributeId;
    UA_String indexRange;
} UA_SimpleAttributeOperand;
*/

static UA_SimpleAttributeOperand *setupSelectClauses(void) 
{
    UA_SimpleAttributeOperand *selectClauses = (UA_SimpleAttributeOperand*)
        UA_Array_new(nSelectClauses, &UA_TYPES[UA_TYPES_SIMPLEATTRIBUTEOPERAND]);
    if(!selectClauses)
        return NULL;

    for(size_t i =0; i<nSelectClauses; ++i) {
        UA_SimpleAttributeOperand_init(&selectClauses[i]);
    }

    selectClauses[0].typeDefinitionId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEEVENTTYPE);
    selectClauses[0].browsePathSize = 1;
    selectClauses[0].browsePath = (UA_QualifiedName*)
        UA_Array_new(selectClauses[0].browsePathSize, &UA_TYPES[UA_TYPES_QUALIFIEDNAME]);
    if(!selectClauses[0].browsePath) {
        UA_SimpleAttributeOperand_delete(selectClauses);
        return NULL;
    }
    selectClauses[0].attributeId = UA_ATTRIBUTEID_VALUE;
    selectClauses[0].browsePath[0] = UA_QUALIFIEDNAME_ALLOC(0, "Message");

    selectClauses[1].typeDefinitionId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEEVENTTYPE);
    selectClauses[1].browsePathSize = 1;
    selectClauses[1].browsePath = (UA_QualifiedName*)
        UA_Array_new(selectClauses[1].browsePathSize, &UA_TYPES[UA_TYPES_QUALIFIEDNAME]);
    if(!selectClauses[1].browsePath) {
        UA_SimpleAttributeOperand_delete(selectClauses);
        return NULL;
    }
    selectClauses[1].attributeId = UA_ATTRIBUTEID_VALUE;
    selectClauses[1].browsePath[0] = UA_QUALIFIEDNAME_ALLOC(0, "Severity");

    return selectClauses;
}
#endif

int main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);
    // robot
    pose.fgR = 0;

    UA_Client *client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
    if (retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return (int)retval;
    }

    printf("%s", "SUCESSFULLY ESTABLISHED\n");

#ifdef UA_ENABLE_SUBSCRIPTIONS
    // 创建一个订阅请求与接受
    UA_CreateSubscriptionRequest request = UA_CreateSubscriptionRequest_default();
    UA_CreateSubscriptionResponse response = UA_Client_Subscriptions_create(client, request, NULL, NULL, NULL);
    UA_UInt32 subId = response.subscriptionId;
    if (response.responseHeader.serviceResult != UA_STATUSCODE_GOOD) {
        UA_Client_disconnect(client);
        UA_Client_delete(client);
        return EXIT_FAILURE;
    }
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "创建订阅请求完成, id是 %u", subId);

    // 创建一个监测项请求，这里监测Server，其NodeId是UA_NODEID_NUMERIC(0, 2253)
    UA_MonitoredItemCreateRequest item;
    UA_MonitoredItemCreateRequest_init(&item);
    item.itemToMonitor.nodeId = UA_NODEID_NUMERIC(0, 2253); // Root->Objects->Server
    item.itemToMonitor.attributeId = UA_ATTRIBUTEID_EVENTNOTIFIER;
    item.monitoringMode = UA_MONITORINGMODE_REPORTING;

    // Server能提供很多内容，这里只关注其事件通知器属性，即UA_ATTRIBUTEID_EVENTNOTIFIER
    // 使用UA_EventFilter创建事件过滤器，然后调用setupSelectClauses()来设置我们关心的事件类型及其Property
    UA_EventFilter filter;
    UA_EventFilter_init(&filter);
    filter.selectClauses = setupSelectClauses();
    filter.selectClausesSize = nSelectClauses;
    // 配置代码
    item.requestedParameters.filter.encoding = UA_EXTENSIONOBJECT_DECODED;
    item.requestedParameters.filter.content.decoded.data = &filter;
    item.requestedParameters.filter.content.decoded.type = &UA_TYPES[UA_TYPES_EVENTFILTER];
    // 调用UA_Client_MonitoredItems_createEvent()来使用监测项请求去创建监测项，并会得到一个监测项ID
    UA_UInt32 monId = 0;
    UA_MonitoredItemCreateResult result =
        UA_Client_MonitoredItems_createEvent(client, subId,
                                             UA_TIMESTAMPSTORETURN_BOTH, item,
                                             &monId, handler_events, NULL);
    if(result.statusCode != UA_STATUSCODE_GOOD) {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "监控失败 %s", UA_StatusCode_name(retval));
        goto cleanup;
    } else {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "监控 'Root->Objects->Server', id %u", response.subscriptionId);
    }
    monId = result.monitoredItemId;
    // 监控代码完成

    // WARNING: 必须用取地址的方式
    // ROBOT 1
    char *robot1_link1_angle_angleValue_paths[4] = {"myFirstRobot", "link1", "angle", "angleValue"};
    UA_NodeId robot1_link1_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &robot1_link1_angle_angleValue_Id, robot1_link1_angle_angleValue_paths);
    
    char *robot1_link2_angle_angleValue_paths[4] = {"myFirstRobot", "link2", "angle", "angleValue"};
    UA_NodeId robot1_link2_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &robot1_link2_angle_angleValue_Id, robot1_link2_angle_angleValue_paths);

    char *robot1_link3_angle_angleValue_paths[4] = {"myFirstRobot", "link3", "angle", "angleValue"};
    UA_NodeId robot1_link3_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &robot1_link3_angle_angleValue_Id, robot1_link3_angle_angleValue_paths);

    char *robot1_link4_angle_angleValue_paths[4] = {"myFirstRobot", "link4", "angle", "angleValue"};
    UA_NodeId robot1_link4_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &robot1_link4_angle_angleValue_Id, robot1_link4_angle_angleValue_paths);

    char *robot1_link5_angle_angleValue_paths[4] = {"myFirstRobot", "link5", "angle", "angleValue"};
    UA_NodeId robot1_link5_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &robot1_link5_angle_angleValue_Id, robot1_link5_angle_angleValue_paths);

    char *robot1_link6_angle_angleValue_paths[4] = {"myFirstRobot", "link6", "angle", "angleValue"};
    UA_NodeId robot1_link6_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &robot1_link6_angle_angleValue_Id, robot1_link6_angle_angleValue_paths);
    
    // ROBOT 2
    char *robot2_link1_angle_angleValue_paths[4] = {"myFirstRobot", "link1", "angle", "angleValue"};
    UA_NodeId robot2_link1_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &robot2_link1_angle_angleValue_Id, robot2_link1_angle_angleValue_paths);
    
    char *robot2_link2_angle_angleValue_paths[4] = {"myFirstRobot", "link2", "angle", "angleValue"};
    UA_NodeId robot2_link2_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &robot2_link2_angle_angleValue_Id, robot2_link2_angle_angleValue_paths);

    char *robot2_link3_angle_angleValue_paths[4] = {"myFirstRobot", "link3", "angle", "angleValue"};
    UA_NodeId robot2_link3_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &robot2_link3_angle_angleValue_Id, robot2_link3_angle_angleValue_paths);

    char *robot2_link4_angle_angleValue_paths[4] = {"myFirstRobot", "link4", "angle", "angleValue"};
    UA_NodeId robot2_link4_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &robot2_link4_angle_angleValue_Id, robot2_link4_angle_angleValue_paths);

    char *robot2_link5_angle_angleValue_paths[4] = {"myFirstRobot", "link5", "angle", "angleValue"};
    UA_NodeId robot2_link5_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &robot2_link5_angle_angleValue_Id, robot2_link5_angle_angleValue_paths);

    char *robot2_link6_angle_angleValue_paths[4] = {"myFirstRobot", "link6", "angle", "angleValue"};
    UA_NodeId robot2_link6_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &robot2_link6_angle_angleValue_Id, robot2_link6_angle_angleValue_paths);

    
    #define MAX_LINE 1024
    char buf[MAX_LINE];
    FILE *fp;
    if ((fp = fopen("C:\\Users\\17222\\Desktop\\path2.txt", "r")) == NULL) {
        perror("fail to read");
    }

    int len;
    printf("%s", "FIRST ROBOT START");
    /*
    while (fgets(buf, MAX_LINE, fp) != NULL) {
        len = strlen(buf);
        buf[len-1] = '\0';
        if (len == 1) {
            clock_t endwait;
            endwait = clock() + 50; // 100ms
            while (clock() < endwait) {

            }
        } else {
            if (buf[11] == '0') {
                double A0 = -atof(buf+14);
                writeServerValueDouble(client, robot1_link1_angle_angleValue_Id, A0);
            } else if (buf[11] == '1') {
                double A1 = atof(buf+14);
                writeServerValueDouble(client, robot1_link2_angle_angleValue_Id, A1);
            } else if (buf[11] == '2') {
                double A2 = atof(buf+14);
                writeServerValueDouble(client, robot1_link3_angle_angleValue_Id, A2);
            } else if (buf[11] == '3') {
                double A3 = atof(buf+14);
                writeServerValueDouble(client, robot1_link4_angle_angleValue_Id, A3);
            } else if (buf[11] == '4') {
                double A4 = atof(buf+14);
                writeServerValueDouble(client, robot1_link5_angle_angleValue_Id, A4);
            } else if (buf[11] == '5') {
                double A5 = atof(buf+14);
                writeServerValueDouble(client, robot1_link6_angle_angleValue_Id, A5);
            }
        }
    }
    */
    printf("%s", "FIRST ROBOT END");
    while (running) {
        retval = UA_Client_run_iterate(client, 100);
    }
cleanup:
    UA_MonitoredItemCreateResult_clear(&result);
    UA_Client_Subscriptions_deleteSingle(client, response.subscriptionId);
    UA_Array_delete(filter.selectClauses, nSelectClauses, &UA_TYPES[UA_TYPES_SIMPLEATTRIBUTEOPERAND]);
#endif
    UA_Client_disconnect(client);
    UA_Client_delete(client);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;

    
}