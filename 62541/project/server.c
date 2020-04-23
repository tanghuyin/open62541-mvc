#include "open62541.h"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "myNS.h"
#include "utils.h"
#include "hashmap.h"

Hashmap *hashmap = NULL;
UA_Boolean running = true;

// server终止的回调函数
static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "receive ctrl-c");
    running = false;
}

// event的node
static UA_NodeId RobotJobEventTypeId;
static UA_NodeId RobotFailureEventTypeId;

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

// 加入一个时间数据源 仅供娱乐
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

// 更新机器人的状态，自动生成的code
// 按需要自行补充，补充格式如下，需要明确当前节点的数据类型，查询模型即可
/*
    UA_StatusCode status = UA_STATUSCODE_GOOD;
    UA_Variant value;
    UA_Variant_setScalar(&value, &status, &UA_TYPES[UA_TYPES_STATUSCODE]);
    UA_Server_writeValue(server, nodeId, value);
*/
static void updateCurrentlink1_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink1_angle_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink1_angle_angleDownLimit_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink1_angle_angleUpLimit_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink1_angle_angleValue_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink1_x_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink1_y_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink1_z_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink2_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink2_angle_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink2_angle_angleDownLimit_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink2_angle_angleUpLimit_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink2_angle_angleValue_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink2_x_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink2_y_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink2_z_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink3_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink3_angle_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink3_angle_angleDownLimit_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink3_angle_angleUpLimit_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink3_angle_angleValue_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink3_x_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink3_y_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink3_z_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink4_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink4_angle_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink4_angle_angleDownLimit_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink4_angle_angleUpLimit_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink4_angle_angleValue_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink4_x_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink4_y_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink4_z_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink5_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink5_angle_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink5_angle_angleDownLimit_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink5_angle_angleUpLimit_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink5_angle_angleValue_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink5_x_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink5_y_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink5_z_Value(UA_Server *server, UA_NodeId nodeId) {
}

static void updateCurrentlink6_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink6_angle_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink6_angle_angleDownLimit_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink6_angle_angleUpLimit_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink6_angle_angleValue_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink6_x_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink6_y_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentlink6_z_Value(UA_Server *server, UA_NodeId nodeId) {
}

static void updateCurrentStart_Value(UA_Server *server, UA_NodeId nodeId) {
}
static void updateCurrentStatus_Value(UA_Server *server, UA_NodeId nodeId) {
}

// 读回调函数 写回调函数 以及绑定函数的自动生成 code


static void beforeRead_robot1_Status_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
}

static void afterWrite_robot1_Status_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot1_Status_Value is modified.");
}

static void add_robot1_Status_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot1_Status_Value;
    callback.onWrite = afterWrite_robot1_Status_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

static void beforeRead_robot2_Status_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
}

static void afterWrite_robot2_Status_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot1_Status_Value is modified.");
}

static void add_robot2_Status_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot2_Status_Value;
    callback.onWrite = afterWrite_robot2_Status_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

// Robot 1
static void beforeRead_robot1_link1_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_angle_angleValue_Value is to be updated.");
    updateCurrentlink1_angle_angleValue_Value(server, *nodeid);
}
static void afterWrite_robot1_link1_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot1_link1_angle_angleValue_Value is modified.");
}
static void add_robot1_link1_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot1_link1_angle_angleValue_Value;
    callback.onWrite = afterWrite_robot1_link1_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

static void beforeRead_robot1_link2_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_angle_angleValue_Value is to be updated.");
    updateCurrentlink2_angle_angleValue_Value(server, *nodeid);
}

static void afterWrite_robot1_link2_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot1_link2_angle_angleValue_Value is modified.");
}

static void add_robot1_link2_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot1_link2_angle_angleValue_Value;
    callback.onWrite = afterWrite_robot1_link2_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}


static void beforeRead_robot1_link3_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_angle_angleValue_Value is to be updated.");
    updateCurrentlink3_angle_angleValue_Value(server, *nodeid);
}
static void afterWrite_robot1_link3_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot1_link3_angle_angleValue_Value is modified.");
}
static void add_robot1_link3_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot1_link3_angle_angleValue_Value;
    callback.onWrite = afterWrite_robot1_link3_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

static void beforeRead_robot1_link4_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_angle_angleValue_Value is to be updated.");
    updateCurrentlink4_angle_angleValue_Value(server, *nodeid);
}
static void afterWrite_robot1_link4_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot1_link4_angle_angleValue_Value is modified.");
}
static void add_robot1_link4_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot1_link4_angle_angleValue_Value;
    callback.onWrite = afterWrite_robot1_link4_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

static void beforeRead_robot1_link5_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_angle_angleValue_Value is to be updated.");
    updateCurrentlink5_angle_angleValue_Value(server, *nodeid);
}
static void afterWrite_robot1_link5_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot1_link5_angle_angleValue_Value is modified.");
}

static void add_robot1_link5_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot1_link5_angle_angleValue_Value;
    callback.onWrite = afterWrite_robot1_link5_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

static void beforeRead_robot1_link6_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    updateCurrentlink6_angle_angleValue_Value(server, *nodeid);
}

static void afterWrite_robot1_link6_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot1_link6_angle_angleValue_Value is modified.");
}

static void add_robot1_link6_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot1_link6_angle_angleValue_Value;
    callback.onWrite = afterWrite_robot1_link6_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

// robot 2
static void beforeRead_robot2_link1_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_angle_angleValue_Value is to be updated.");
    updateCurrentlink1_angle_angleValue_Value(server, *nodeid);
}
static void afterWrite_robot2_link1_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot2_link1_angle_angleValue_Value is modified.");
}
static void add_robot2_link1_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot2_link1_angle_angleValue_Value;
    callback.onWrite = afterWrite_robot2_link1_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

static void beforeRead_robot2_link2_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_angle_angleValue_Value is to be updated.");
    updateCurrentlink2_angle_angleValue_Value(server, *nodeid);
}

static void afterWrite_robot2_link2_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot2_link2_angle_angleValue_Value is modified.");
}

static void add_robot2_link2_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot2_link2_angle_angleValue_Value;
    callback.onWrite = afterWrite_robot2_link2_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}


static void beforeRead_robot2_link3_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_angle_angleValue_Value is to be updated.");
    updateCurrentlink3_angle_angleValue_Value(server, *nodeid);
}
static void afterWrite_robot2_link3_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot2_link3_angle_angleValue_Value is modified.");
}
static void add_robot2_link3_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot2_link3_angle_angleValue_Value;
    callback.onWrite = afterWrite_robot2_link3_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

static void beforeRead_robot2_link4_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_angle_angleValue_Value is to be updated.");
    updateCurrentlink4_angle_angleValue_Value(server, *nodeid);
}
static void afterWrite_robot2_link4_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot2_link4_angle_angleValue_Value is modified.");
}
static void add_robot2_link4_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot2_link4_angle_angleValue_Value;
    callback.onWrite = afterWrite_robot2_link4_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

static void beforeRead_robot2_link5_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_angle_angleValue_Value is to be updated.");
    updateCurrentlink5_angle_angleValue_Value(server, *nodeid);
}
static void afterWrite_robot2_link5_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot2_link5_angle_angleValue_Value is modified.");
}

static void add_robot2_link5_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot2_link5_angle_angleValue_Value;
    callback.onWrite = afterWrite_robot2_link5_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

static void beforeRead_robot2_link6_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    updateCurrentlink6_angle_angleValue_Value(server, *nodeid);
}

static void afterWrite_robot2_link6_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "robot2_link6_angle_angleValue_Value is modified.");
}

static void add_robot2_link6_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeRead_robot2_link6_angle_angleValue_Value;
    callback.onWrite = afterWrite_robot2_link6_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
// 读回调函数 写回调函数 以及绑定函数的自动生成 code 结束

static UA_StatusCode getNodeIdMethodCallback(UA_Server *server,
                                    const UA_NodeId *sessionId, void *sessionHandle,
                                    const UA_NodeId *methodId, void *methodContext,
                                    const UA_NodeId *objectId, void *objectContext,
                                    size_t inputSize, const UA_Variant *input,
                                    size_t outputSize, UA_Variant *output) {
    
    UA_String *inputStr = (UA_String*) input->data;
    UA_String tmp = UA_STRING_ALLOC("_");
    // tmp.data = (UA_Byte *)UA_realloc(tmp.data, inputStr->length + tmp.length);
    // memcpy(&(*inputStr).data[(*inputStr).length-1], tmp.data, inputStr->length);

    // printf("%d \n", inputStr->length);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, (*inputStr).data);
    UA_NodeId nodeId = *(UA_NodeId *)hashmap_get(hashmap, (*inputStr).data);
    // UA_NodeId nodeId = UA_NODEID_NUMERIC(1,62541);
    UA_Variant_setScalarCopy(output, &nodeId, &UA_TYPES[UA_TYPES_NODEID]);
    UA_String_clear(&tmp);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "getNodeIdMethod called");
    return UA_STATUSCODE_GOOD;
}

static void addGetNodeIdMethod(UA_Server *server) {
    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);
    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "Node Description Name");
    inputArgument.name = UA_STRING("MyInput");
    inputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    inputArgument.valueRank = UA_VALUERANK_SCALAR;

    UA_Argument outputArgument;
    UA_Argument_init(&outputArgument);
    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "Node Id");
    outputArgument.dataType = UA_TYPES[UA_TYPES_NODEID].typeId;
    outputArgument.valueRank =UA_VALUERANK_SCALAR;

    UA_MethodAttributes getAttr = UA_MethodAttributes_default;
    getAttr.description = UA_LOCALIZEDTEXT("en-US", "get ID");
    getAttr.displayName = UA_LOCALIZEDTEXT("en-US", "get ID");
    getAttr.executable = true;
    getAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1,62541),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "get NodeId"),
                            getAttr, &getNodeIdMethodCallback,
                            1, &inputArgument, 1, &outputArgument, NULL, NULL);
}


static UA_StatusCode addRobotFailureEventType(UA_Server *server) {
    UA_ObjectTypeAttributes attr = UA_ObjectTypeAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "RobotFailureEventType");
    attr.description = UA_LOCALIZEDTEXT("en-US", "An event which shows a failure of a robot");
    return UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                                        UA_NODEID_NUMERIC(0, UA_NS0ID_BASEEVENTTYPE),
                                        UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                        UA_QUALIFIEDNAME(0, "RobotFailureEventType"),
                                        attr, NULL, &RobotFailureEventTypeId);
}


static UA_StatusCode setUpRobotFailureEvent(UA_Server *server, UA_NodeId *outId, UA_LocalizedText *eventMessage) {
    UA_StatusCode retval = UA_Server_createEvent(server, RobotFailureEventTypeId, outId);
    if (retval != UA_STATUSCODE_GOOD) {
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                       "createEvent failed. StatusCode %s", UA_StatusCode_name(retval));
        return retval;
    }
    UA_DateTime eventTime = UA_DateTime_now();
    UA_Server_writeObjectProperty_scalar(server, *outId, UA_QUALIFIEDNAME(0, "Time"),
                                         &eventTime, &UA_TYPES[UA_TYPES_DATETIME]);

    UA_UInt16 eventSeverity = 200;
    UA_Server_writeObjectProperty_scalar(server, *outId, UA_QUALIFIEDNAME(0, "Severity"),
                                         &eventSeverity, &UA_TYPES[UA_TYPES_UINT16]);

    // UA_LocalizedText eventMessage = UA_LOCALIZEDTEXT("en-US", "An event has been generated.");
    UA_Server_writeObjectProperty_scalar(server, *outId, UA_QUALIFIEDNAME(0, "Message"),
                                         eventMessage, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);

    return UA_STATUSCODE_GOOD;
}

static UA_StatusCode generateRobotFailureEventMethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "RobotFailureEvent triggered");

    UA_Int16 *robotNo = (UA_Int16*) input->data;
    char robotNoC[2];
    sprintf(robotNoC, "%d", (*robotNo));
    UA_LocalizedText eventMessage = UA_LOCALIZEDTEXT("en-US", robotNoC);
    /* set up event */
    UA_NodeId eventNodeId;
    UA_StatusCode retval = setUpRobotFailureEvent(server, &eventNodeId, &eventMessage);
    if(retval != UA_STATUSCODE_GOOD) {
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                       "Creating event failed. StatusCode %s", UA_StatusCode_name(retval));
        return retval;
    }

    retval = UA_Server_triggerEvent(server, eventNodeId,
                                    UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER),
                                    NULL, UA_TRUE);
    if(retval != UA_STATUSCODE_GOOD)
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                       "Triggering event failed. StatusCode %s", UA_StatusCode_name(retval));

    return retval;
}


static void addGenerateRobotFailureEventMethod(UA_Server *server) 
{
    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);
    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "Robot No");
    inputArgument.name = UA_STRING("MyInput");
    inputArgument.dataType = UA_TYPES[UA_TYPES_INT16].typeId;
    inputArgument.valueRank = UA_VALUERANK_SCALAR;

    UA_MethodAttributes generateAttr = UA_MethodAttributes_default;
    generateAttr.description = UA_LOCALIZEDTEXT("en-US","Generate a failure of a robot");
    generateAttr.displayName = UA_LOCALIZEDTEXT("en-US","Generate RobotFailure Event");
    generateAttr.executable = true;
    generateAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1, 62543),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "Generate RobotFailureEvent"),
                            generateAttr, &generateRobotFailureEventMethodCallback,
                            1, &inputArgument, 0, NULL, NULL, NULL);
}


static UA_StatusCode addRobotJobEventType(UA_Server *server) {
    UA_ObjectTypeAttributes attr = UA_ObjectTypeAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "RobotJobEventType");
    attr.description = UA_LOCALIZEDTEXT("en-US", "An event which will assign the robot a job");
    return UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                                        UA_NODEID_NUMERIC(0, UA_NS0ID_BASEEVENTTYPE),
                                        UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                        UA_QUALIFIEDNAME(0, "AssignRobotJobEventType"),
                                        attr, NULL, &RobotJobEventTypeId);
}

static UA_StatusCode setUpRobotJobEvent(UA_Server *server, UA_NodeId *outId, UA_LocalizedText *eventMessage) {
    UA_StatusCode retval = UA_Server_createEvent(server, RobotJobEventTypeId, outId);
    if (retval != UA_STATUSCODE_GOOD) {
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                       "createEvent failed. StatusCode %s", UA_StatusCode_name(retval));
        return retval;
    }

    UA_DateTime eventTime = UA_DateTime_now();
    UA_Server_writeObjectProperty_scalar(server, *outId, UA_QUALIFIEDNAME(0, "Time"),
                                         &eventTime, &UA_TYPES[UA_TYPES_DATETIME]);

    UA_UInt16 eventSeverity = 100;
    UA_Server_writeObjectProperty_scalar(server, *outId, UA_QUALIFIEDNAME(0, "Severity"),
                                         &eventSeverity, &UA_TYPES[UA_TYPES_UINT16]);

    // UA_LocalizedText eventMessage = UA_LOCALIZEDTEXT("en-US", "An event has been generated.");
    UA_Server_writeObjectProperty_scalar(server, *outId, UA_QUALIFIEDNAME(0, "Message"),
                                         eventMessage, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);

    UA_String eventSourceName = UA_STRING("RobotJob");
    UA_Server_writeObjectProperty_scalar(server, *outId, UA_QUALIFIEDNAME(0, "SourceName"),
                                         &eventSourceName, &UA_TYPES[UA_TYPES_STRING]);


    return UA_STATUSCODE_GOOD;
}


static UA_StatusCode generateRobotJobEventMethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) 
{

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "RobotJobEvent triggered");

    UA_Int16 *robotNo = (UA_Int16*) input->data;
    char robotNoC[2];
    sprintf(robotNoC, "%d", (*robotNo));
    UA_LocalizedText eventMessage = UA_LOCALIZEDTEXT("en-US", robotNoC);
    /* set up event */
    UA_NodeId eventNodeId;
    UA_StatusCode retval = setUpRobotJobEvent(server, &eventNodeId, &eventMessage);
    if(retval != UA_STATUSCODE_GOOD) {
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                       "Creating event failed. StatusCode %s", UA_StatusCode_name(retval));
        return retval;
    }

    retval = UA_Server_triggerEvent(server, eventNodeId,
                                    UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER),
                                    NULL, UA_TRUE);
    if(retval != UA_STATUSCODE_GOOD)
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                       "Triggering event failed. StatusCode %s", UA_StatusCode_name(retval));

    return retval;
}


static void addGenerateRobotJobEventMethod(UA_Server *server) 
{
    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);
    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "Robot No");
    inputArgument.name = UA_STRING("MyInput");
    inputArgument.dataType = UA_TYPES[UA_TYPES_INT16].typeId;
    inputArgument.valueRank = UA_VALUERANK_SCALAR;

    UA_MethodAttributes generateAttr = UA_MethodAttributes_default;
    generateAttr.description = UA_LOCALIZEDTEXT("en-US","Generate an Robot Job event.");
    generateAttr.displayName = UA_LOCALIZEDTEXT("en-US","Generate RobotJob Event");
    generateAttr.executable = true;
    generateAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1, 62542),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "Generate RobotJobEvent"),
                            generateAttr, &generateRobotJobEventMethodCallback,
                            1, &inputArgument, 0, NULL, NULL, NULL);
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

        addGetNodeIdMethod(server);
        // 添加一个时钟源，仅供娱乐
        addCurrentTimeDataSourceVariable(server); 

        hashmap = hashmap_new(16, hash, compare); // 存储名称和nodeid对的hashmap

        // 第一个机器人
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

        // 第二个机器人

        UA_NodeId Robot2Id;
        UA_ObjectAttributes object_attr2 = UA_ObjectAttributes_default;
        object_attr2.description = UA_LOCALIZEDTEXT("en-US", "mySecondRobot");
        object_attr2.displayName = UA_LOCALIZEDTEXT("en-US", "Robot_2#");
        UA_Server_addObjectNode(server, UA_NODEID_NULL,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                                UA_QUALIFIEDNAME(1, "mySecondRobot"),
                                UA_NODEID_NUMERIC(2, 1003),
                                object_attr2, NULL, &Robot2Id);

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

        // 事件
        addRobotJobEventType(server);
        addGenerateRobotJobEventMethod(server);

        addRobotFailureEventType(server);
        addGenerateRobotFailureEventMethod(server);
        

        int ret;

        // Robot1 的node
        UA_QualifiedName robot1_link1_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link1"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId robot1_link1_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, robot1_link1_angle_angleValue_nameArr, &robot1_link1_angle_angleValue_id);
        hashmap_set(hashmap, "robot1_link1_angle_angleValue_", &robot1_link1_angle_angleValue_id, NULL);

        UA_QualifiedName robot1_link2_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link2"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId robot1_link2_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, robot1_link2_angle_angleValue_nameArr, &robot1_link2_angle_angleValue_id);
        hashmap_set(hashmap, "robot1_link2_angle_angleValue_", &robot1_link2_angle_angleValue_id, NULL);

        UA_QualifiedName robot1_link3_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link3"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId robot1_link3_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, robot1_link3_angle_angleValue_nameArr, &robot1_link3_angle_angleValue_id);
        hashmap_set(hashmap, "robot1_link3_angle_angleValue_", &robot1_link3_angle_angleValue_id, NULL);

        UA_QualifiedName robot1_link4_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link4"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId robot1_link4_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, robot1_link4_angle_angleValue_nameArr, &robot1_link4_angle_angleValue_id);
        hashmap_set(hashmap, "robot1_link4_angle_angleValue_", &robot1_link4_angle_angleValue_id, NULL);

        UA_QualifiedName robot1_link5_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link5"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId robot1_link5_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, robot1_link5_angle_angleValue_nameArr, &robot1_link5_angle_angleValue_id);
        hashmap_set(hashmap, "robot1_link5_angle_angleValue_", &robot1_link5_angle_angleValue_id, NULL);

        UA_QualifiedName robot1_link6_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link6"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId robot1_link6_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, robot1_link6_angle_angleValue_nameArr, &robot1_link6_angle_angleValue_id);
        hashmap_set(hashmap, "robot1_link6_angle_angleValue_", &robot1_link6_angle_angleValue_id, NULL);


        // Robot2 的node
        UA_QualifiedName robot2_link1_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "mySecondRobot"), UA_QUALIFIEDNAME(2, "link1"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId robot2_link1_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, robot2_link1_angle_angleValue_nameArr, &robot2_link1_angle_angleValue_id);
        hashmap_set(hashmap, "robot2_link1_angle_angleValue_", &robot2_link1_angle_angleValue_id, NULL);

        UA_QualifiedName robot2_link2_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "mySecondRobot"), UA_QUALIFIEDNAME(2, "link2"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId robot2_link2_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, robot2_link2_angle_angleValue_nameArr, &robot2_link2_angle_angleValue_id);
        hashmap_set(hashmap, "robot2_link2_angle_angleValue_", &robot2_link2_angle_angleValue_id, NULL);

        UA_QualifiedName robot2_link3_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "mySecondRobot"), UA_QUALIFIEDNAME(2, "link3"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId robot2_link3_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, robot2_link3_angle_angleValue_nameArr, &robot2_link3_angle_angleValue_id);
        hashmap_set(hashmap, "robot2_link3_angle_angleValue_", &robot2_link3_angle_angleValue_id, NULL);

        UA_QualifiedName robot2_link4_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "mySecondRobot"), UA_QUALIFIEDNAME(2, "link4"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId robot2_link4_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, robot2_link4_angle_angleValue_nameArr, &robot2_link4_angle_angleValue_id);
        hashmap_set(hashmap, "robot2_link4_angle_angleValue_", &robot2_link4_angle_angleValue_id, NULL);

        UA_QualifiedName robot2_link5_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "mySecondRobot"), UA_QUALIFIEDNAME(2, "link5"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId robot2_link5_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, robot2_link5_angle_angleValue_nameArr, &robot2_link5_angle_angleValue_id);
        hashmap_set(hashmap, "robot2_link5_angle_angleValue_", &robot2_link5_angle_angleValue_id, NULL);

        UA_QualifiedName robot2_link6_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "mySecondRobot"), UA_QUALIFIEDNAME(2, "link6"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId robot2_link6_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, robot2_link6_angle_angleValue_nameArr, &robot2_link6_angle_angleValue_id);
        hashmap_set(hashmap, "robot2_link6_angle_angleValue_", &robot2_link6_angle_angleValue_id, NULL);

        // 获取节点nodeid自动生成code结束

        // UA_QualifiedName Start_nameArr[2] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "Start")};
        // UA_NodeId Start_id;
        // ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 2, Start_nameArr, &Start_id);
        // hashmap_set(hashmap, "Start_", &Start_id, NULL);

        UA_QualifiedName robot1_Status_nameArr[2] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "Status")};
        UA_NodeId robot1_Status_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 2, robot1_Status_nameArr, &robot1_Status_id);
        hashmap_set(hashmap, "robot1_Status_", &robot1_Status_id, NULL);

        UA_QualifiedName robot2_Status_nameArr[2] = {UA_QUALIFIEDNAME(1, "mySecondRobot"), UA_QUALIFIEDNAME(2, "Status")};
        UA_NodeId robot2_Status_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 2, robot2_Status_nameArr, &robot2_Status_id);
        hashmap_set(hashmap, "robot2_Status_", &robot2_Status_id, NULL);
        


        // 将回调函数绑定到server
        add_robot1_Status_CallbackToRobot(server, robot1_Status_id);
        add_robot2_Status_CallbackToRobot(server, robot2_Status_id);


        add_robot1_link1_angle_angleValue_CallbackToRobot(server, robot1_link1_angle_angleValue_id);
        add_robot1_link2_angle_angleValue_CallbackToRobot(server, robot1_link2_angle_angleValue_id);
        add_robot1_link3_angle_angleValue_CallbackToRobot(server, robot1_link3_angle_angleValue_id);
        add_robot1_link4_angle_angleValue_CallbackToRobot(server, robot1_link4_angle_angleValue_id);
        add_robot1_link5_angle_angleValue_CallbackToRobot(server, robot1_link5_angle_angleValue_id);
        add_robot1_link6_angle_angleValue_CallbackToRobot(server, robot1_link6_angle_angleValue_id);
        
        add_robot2_link1_angle_angleValue_CallbackToRobot(server, robot2_link1_angle_angleValue_id);
        add_robot2_link2_angle_angleValue_CallbackToRobot(server, robot2_link2_angle_angleValue_id);
        add_robot2_link3_angle_angleValue_CallbackToRobot(server, robot2_link3_angle_angleValue_id);
        add_robot2_link4_angle_angleValue_CallbackToRobot(server, robot2_link4_angle_angleValue_id);
        add_robot2_link5_angle_angleValue_CallbackToRobot(server, robot2_link5_angle_angleValue_id);
        add_robot2_link6_angle_angleValue_CallbackToRobot(server, robot2_link6_angle_angleValue_id);
        

        retval = UA_Server_run(server, &running);
    }

    UA_Server_delete(server);

    return (int) retval;
}