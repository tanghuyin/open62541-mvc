#include "open62541.h"

#include <signal.h>
#include <stdlib.h>

#include "myNS.h"
#include "utils.h"

UA_Boolean running = true;

// server终止的回调函数
static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "receive ctrl-c");
    running = false;
}

// 读取现在的时间
static UA_StatusCode readCurrentTime(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue) 
{
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "read current time");
    UA_DateTime now = UA_DateTime_now();
    UA_Variant_setScalarCopy(&dataValue->value, &now,
                             &UA_TYPES[UA_TYPES_DATETIME]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

// 加入一个时间数据源
static void addCurrentTimeDataSourceVariable(UA_Server *server) {
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Current time");
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "current-time-datasource");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "current-time-datasource");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource timeDataSource;
    timeDataSource.read = readCurrentTime;
    // timeDataSource.write = writeCurrentTime; 时间源是不可以写的
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        timeDataSource, NULL, NULL);
}

// 更新机器人的状态
static void updateCurrentRobotStatus(UA_Server *server, UA_NodeId robotStatusNodeId) {
    UA_StatusCode status = UA_STATUSCODE_GOOD;
    UA_Variant value;
    UA_Variant_setScalar(&value, &status, &UA_TYPES[UA_TYPES_STATUSCODE]);
    UA_Server_writeValue(server, robotStatusNodeId, value);
}

// 机器人状态回调函数读，调用updateCurrentRobotStatus函数
static void beforeReadRobotStatusValue(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Robot Status Code is to be updated.");
	updateCurrentRobotStatus(server, *nodeid);
}

// 机器人状态回调函数写，必须要有，不然写不进去。WARNING
static void afterWriteRobotStatusValue(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeId, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data) 
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "The variable was updated");
}

// 绑定回到函数到server
static void addValueCallbackToRobotStatusVariable(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadRobotStatusValue;
    callback.onWrite = afterWriteRobotStatusValue;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}


int main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_Server *server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    UA_StatusCode retval;
    if (myNS(server) != UA_STATUSCODE_GOOD) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not add the nodeset.");
        retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
    } else {
        // 添加一个时钟源，仅供娱乐
        addCurrentTimeDataSourceVariable(server); 

        UA_NodeId RobotId;
        UA_ObjectAttributes object_attr = UA_ObjectAttributes_default;

        object_attr.description = UA_LOCALIZEDTEXT("en-US", "myFirstRobot");
        object_attr.displayName = UA_LOCALIZEDTEXT("en-US", "Robot_1#");

        UA_Server_addObjectNode(server, UA_NODEID_NULL, 
                                UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                                UA_QUALIFIEDNAME(1, "myFirstRobot"),
                                UA_NODEID_NUMERIC(2, 1003),
                                object_attr, NULL, &RobotId);

        // TODO: 获得机器人对象的根节点以及机器人定义的模型，可以将所有节点以及其NodeId以map的方式返回
        /*
        MODEL

        Robot:
            link1:
                x(double)
                y
                z
                angle(AngleType):
                    angle(double)
                    angleUpLimit(double)
                    angleDownLimit(double)
            link2:
                x
                y
                z
                ...
            ...
            Status

        OPC UA
        3D Model(given by w.dai)
        Physic
        */
        int ret;
        
        // 找到Status的节点
        UA_QualifiedName targetNameArr[2] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "Status")};
        UA_NodeId statusId;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 2, targetNameArr, &statusId);
        if (ret == 0) {
            if (statusId.identifierType == UA_NODEIDTYPE_NUMERIC) {
                printf("===> StatusId: %u \n", statusId.identifier.numeric);
            }
        }


        // 找到Link1的节点
        UA_QualifiedName link1NameArr[2] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link1")};
        UA_NodeId link1Id;
        ret = findNodeID(server,UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 2, link1NameArr, &link1Id);
        if (ret == 0) {
            if (link1Id.identifierType == UA_NODEIDTYPE_NUMERIC) {
                printf("===> link1Id: %u \n", link1Id.identifier.numeric);
            }
        }


        // 找到Link1-x的节点
        UA_QualifiedName link1XNameArr[1] = {UA_QUALIFIEDNAME(2, "x")};
        UA_NodeId link1XId;
        ret = findNodeID(server, link1Id, 1, link1XNameArr, &link1XId);
        if (ret == 0) {
            if (link1XId.identifierType == UA_NODEIDTYPE_NUMERIC) {
                printf("===> link1XId: %u \n", link1XId.identifier.numeric);
            }
        }

        // 将回调函数绑定到server
        addValueCallbackToRobotStatusVariable(server, statusId);

        retval = UA_Server_run(server, &running);
    }

    UA_Server_delete(server);

    return (int) retval;
}