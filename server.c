#include "open62541.h"

#include <signal.h>
#include <stdlib.h>

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
    UA_StatusCode status = UA_STATUSCODE_GOOD;
    UA_Variant value;
    UA_Variant_setScalar(&value, &status, &UA_TYPES[UA_TYPES_STATUSCODE]);
    UA_Server_writeValue(server, nodeId, value);
}

// 读回调函数 写回调函数 以及绑定函数的自动生成 code


static void beforeReadStatus_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Status_Value is to be updated.");
    updateCurrentStatus_Value(server, *nodeid);
}

static void afterWriteStatus_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Status_Value is modified.");
}

static void addStatus_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadStatus_Value;
    callback.onWrite = afterWriteStatus_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

static void beforeReadlink1_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_Value is to be updated.");
    updateCurrentlink1_Value(server, *nodeid);
}
static void afterWritelink1_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_Value is modified.");
}
static void addlink1_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink1_Value;
    callback.onWrite = afterWritelink1_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink1_angle_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_angle_Value is to be updated.");
    updateCurrentlink1_angle_Value(server, *nodeid);
}
static void afterWritelink1_angle_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_angle_Value is modified.");
}
static void addlink1_angle_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink1_angle_Value;
    callback.onWrite = afterWritelink1_angle_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink1_angle_angleDownLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_angle_angleDownLimit_Value is to be updated.");
    updateCurrentlink1_angle_angleDownLimit_Value(server, *nodeid);
}
static void afterWritelink1_angle_angleDownLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_angle_angleDownLimit_Value is modified.");
}
static void addlink1_angle_angleDownLimit_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink1_angle_angleDownLimit_Value;
    callback.onWrite = afterWritelink1_angle_angleDownLimit_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink1_angle_angleUpLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_angle_angleUpLimit_Value is to be updated.");
    updateCurrentlink1_angle_angleUpLimit_Value(server, *nodeid);
}
static void afterWritelink1_angle_angleUpLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_angle_angleUpLimit_Value is modified.");
}
static void addlink1_angle_angleUpLimit_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink1_angle_angleUpLimit_Value;
    callback.onWrite = afterWritelink1_angle_angleUpLimit_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink1_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_angle_angleValue_Value is to be updated.");
    updateCurrentlink1_angle_angleValue_Value(server, *nodeid);
}
static void afterWritelink1_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_angle_angleValue_Value is modified.");
}
static void addlink1_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink1_angle_angleValue_Value;
    callback.onWrite = afterWritelink1_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink1_x_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_x_Value is to be updated.");
    updateCurrentlink1_x_Value(server, *nodeid);
}
static void afterWritelink1_x_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_x_Value is modified.");
}
static void addlink1_x_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink1_x_Value;
    callback.onWrite = afterWritelink1_x_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink1_y_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_y_Value is to be updated.");
    updateCurrentlink1_y_Value(server, *nodeid);
}
static void afterWritelink1_y_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_y_Value is modified.");
}
static void addlink1_y_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink1_y_Value;
    callback.onWrite = afterWritelink1_y_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink1_z_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_z_Value is to be updated.");
    updateCurrentlink1_z_Value(server, *nodeid);
}
static void afterWritelink1_z_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link1_z_Value is modified.");
}
static void addlink1_z_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink1_z_Value;
    callback.onWrite = afterWritelink1_z_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink2_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_Value is to be updated.");
    updateCurrentlink2_Value(server, *nodeid);
}
static void afterWritelink2_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_Value is modified.");
}
static void addlink2_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink2_Value;
    callback.onWrite = afterWritelink2_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink2_angle_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_angle_Value is to be updated.");
    updateCurrentlink2_angle_Value(server, *nodeid);
}
static void afterWritelink2_angle_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_angle_Value is modified.");
}
static void addlink2_angle_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink2_angle_Value;
    callback.onWrite = afterWritelink2_angle_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink2_angle_angleDownLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_angle_angleDownLimit_Value is to be updated.");
    updateCurrentlink2_angle_angleDownLimit_Value(server, *nodeid);
}
static void afterWritelink2_angle_angleDownLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_angle_angleDownLimit_Value is modified.");
}
static void addlink2_angle_angleDownLimit_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink2_angle_angleDownLimit_Value;
    callback.onWrite = afterWritelink2_angle_angleDownLimit_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink2_angle_angleUpLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_angle_angleUpLimit_Value is to be updated.");
    updateCurrentlink2_angle_angleUpLimit_Value(server, *nodeid);
}
static void afterWritelink2_angle_angleUpLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_angle_angleUpLimit_Value is modified.");
}
static void addlink2_angle_angleUpLimit_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink2_angle_angleUpLimit_Value;
    callback.onWrite = afterWritelink2_angle_angleUpLimit_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink2_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_angle_angleValue_Value is to be updated.");
    updateCurrentlink2_angle_angleValue_Value(server, *nodeid);
}
static void afterWritelink2_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_angle_angleValue_Value is modified.");
}
static void addlink2_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink2_angle_angleValue_Value;
    callback.onWrite = afterWritelink2_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink2_x_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_x_Value is to be updated.");
    updateCurrentlink2_x_Value(server, *nodeid);
}
static void afterWritelink2_x_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_x_Value is modified.");
}
static void addlink2_x_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink2_x_Value;
    callback.onWrite = afterWritelink2_x_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink2_y_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_y_Value is to be updated.");
    updateCurrentlink2_y_Value(server, *nodeid);
}
static void afterWritelink2_y_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_y_Value is modified.");
}
static void addlink2_y_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink2_y_Value;
    callback.onWrite = afterWritelink2_y_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink2_z_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_z_Value is to be updated.");
    updateCurrentlink2_z_Value(server, *nodeid);
}
static void afterWritelink2_z_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link2_z_Value is modified.");
}
static void addlink2_z_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink2_z_Value;
    callback.onWrite = afterWritelink2_z_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink3_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_Value is to be updated.");
    updateCurrentlink3_Value(server, *nodeid);
}
static void afterWritelink3_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_Value is modified.");
}
static void addlink3_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink3_Value;
    callback.onWrite = afterWritelink3_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink3_angle_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_angle_Value is to be updated.");
    updateCurrentlink3_angle_Value(server, *nodeid);
}
static void afterWritelink3_angle_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_angle_Value is modified.");
}
static void addlink3_angle_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink3_angle_Value;
    callback.onWrite = afterWritelink3_angle_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink3_angle_angleDownLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_angle_angleDownLimit_Value is to be updated.");
    updateCurrentlink3_angle_angleDownLimit_Value(server, *nodeid);
}
static void afterWritelink3_angle_angleDownLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_angle_angleDownLimit_Value is modified.");
}
static void addlink3_angle_angleDownLimit_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink3_angle_angleDownLimit_Value;
    callback.onWrite = afterWritelink3_angle_angleDownLimit_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink3_angle_angleUpLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_angle_angleUpLimit_Value is to be updated.");
    updateCurrentlink3_angle_angleUpLimit_Value(server, *nodeid);
}
static void afterWritelink3_angle_angleUpLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_angle_angleUpLimit_Value is modified.");
}
static void addlink3_angle_angleUpLimit_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink3_angle_angleUpLimit_Value;
    callback.onWrite = afterWritelink3_angle_angleUpLimit_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink3_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_angle_angleValue_Value is to be updated.");
    updateCurrentlink3_angle_angleValue_Value(server, *nodeid);
}
static void afterWritelink3_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_angle_angleValue_Value is modified.");
}
static void addlink3_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink3_angle_angleValue_Value;
    callback.onWrite = afterWritelink3_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink3_x_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_x_Value is to be updated.");
    updateCurrentlink3_x_Value(server, *nodeid);
}
static void afterWritelink3_x_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_x_Value is modified.");
}
static void addlink3_x_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink3_x_Value;
    callback.onWrite = afterWritelink3_x_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink3_y_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_y_Value is to be updated.");
    updateCurrentlink3_y_Value(server, *nodeid);
}
static void afterWritelink3_y_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_y_Value is modified.");
}
static void addlink3_y_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink3_y_Value;
    callback.onWrite = afterWritelink3_y_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink3_z_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_z_Value is to be updated.");
    updateCurrentlink3_z_Value(server, *nodeid);
}
static void afterWritelink3_z_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link3_z_Value is modified.");
}
static void addlink3_z_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink3_z_Value;
    callback.onWrite = afterWritelink3_z_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink4_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_Value is to be updated.");
    updateCurrentlink4_Value(server, *nodeid);
}
static void afterWritelink4_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_Value is modified.");
}
static void addlink4_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink4_Value;
    callback.onWrite = afterWritelink4_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink4_angle_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_angle_Value is to be updated.");
    updateCurrentlink4_angle_Value(server, *nodeid);
}
static void afterWritelink4_angle_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_angle_Value is modified.");
}
static void addlink4_angle_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink4_angle_Value;
    callback.onWrite = afterWritelink4_angle_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink4_angle_angleDownLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_angle_angleDownLimit_Value is to be updated.");
    updateCurrentlink4_angle_angleDownLimit_Value(server, *nodeid);
}
static void afterWritelink4_angle_angleDownLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_angle_angleDownLimit_Value is modified.");
}
static void addlink4_angle_angleDownLimit_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink4_angle_angleDownLimit_Value;
    callback.onWrite = afterWritelink4_angle_angleDownLimit_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink4_angle_angleUpLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_angle_angleUpLimit_Value is to be updated.");
    updateCurrentlink4_angle_angleUpLimit_Value(server, *nodeid);
}
static void afterWritelink4_angle_angleUpLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_angle_angleUpLimit_Value is modified.");
}
static void addlink4_angle_angleUpLimit_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink4_angle_angleUpLimit_Value;
    callback.onWrite = afterWritelink4_angle_angleUpLimit_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink4_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_angle_angleValue_Value is to be updated.");
    updateCurrentlink4_angle_angleValue_Value(server, *nodeid);
}
static void afterWritelink4_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_angle_angleValue_Value is modified.");
}
static void addlink4_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink4_angle_angleValue_Value;
    callback.onWrite = afterWritelink4_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink4_x_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_x_Value is to be updated.");
    updateCurrentlink4_x_Value(server, *nodeid);
}
static void afterWritelink4_x_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_x_Value is modified.");
}
static void addlink4_x_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink4_x_Value;
    callback.onWrite = afterWritelink4_x_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink4_y_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_y_Value is to be updated.");
    updateCurrentlink4_y_Value(server, *nodeid);
}
static void afterWritelink4_y_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_y_Value is modified.");
}
static void addlink4_y_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink4_y_Value;
    callback.onWrite = afterWritelink4_y_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink4_z_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_z_Value is to be updated.");
    updateCurrentlink4_z_Value(server, *nodeid);
}
static void afterWritelink4_z_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link4_z_Value is modified.");
}
static void addlink4_z_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink4_z_Value;
    callback.onWrite = afterWritelink4_z_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink5_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_Value is to be updated.");
    updateCurrentlink5_Value(server, *nodeid);
}
static void afterWritelink5_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_Value is modified.");
}
static void addlink5_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink5_Value;
    callback.onWrite = afterWritelink5_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink5_angle_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_angle_Value is to be updated.");
    updateCurrentlink5_angle_Value(server, *nodeid);
}
static void afterWritelink5_angle_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_angle_Value is modified.");
}
static void addlink5_angle_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink5_angle_Value;
    callback.onWrite = afterWritelink5_angle_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink5_angle_angleDownLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_angle_angleDownLimit_Value is to be updated.");
    updateCurrentlink5_angle_angleDownLimit_Value(server, *nodeid);
}
static void afterWritelink5_angle_angleDownLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_angle_angleDownLimit_Value is modified.");
}
static void addlink5_angle_angleDownLimit_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink5_angle_angleDownLimit_Value;
    callback.onWrite = afterWritelink5_angle_angleDownLimit_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink5_angle_angleUpLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_angle_angleUpLimit_Value is to be updated.");
    updateCurrentlink5_angle_angleUpLimit_Value(server, *nodeid);
}
static void afterWritelink5_angle_angleUpLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_angle_angleUpLimit_Value is modified.");
}
static void addlink5_angle_angleUpLimit_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink5_angle_angleUpLimit_Value;
    callback.onWrite = afterWritelink5_angle_angleUpLimit_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink5_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_angle_angleValue_Value is to be updated.");
    updateCurrentlink5_angle_angleValue_Value(server, *nodeid);
}
static void afterWritelink5_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_angle_angleValue_Value is modified.");
}
static void addlink5_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink5_angle_angleValue_Value;
    callback.onWrite = afterWritelink5_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink5_x_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_x_Value is to be updated.");
    updateCurrentlink5_x_Value(server, *nodeid);
}
static void afterWritelink5_x_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_x_Value is modified.");
}
static void addlink5_x_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink5_x_Value;
    callback.onWrite = afterWritelink5_x_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink5_y_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_y_Value is to be updated.");
    updateCurrentlink5_y_Value(server, *nodeid);
}
static void afterWritelink5_y_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_y_Value is modified.");
}
static void addlink5_y_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink5_y_Value;
    callback.onWrite = afterWritelink5_y_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink5_z_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_z_Value is to be updated.");
    updateCurrentlink5_z_Value(server, *nodeid);
}
static void afterWritelink5_z_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link5_z_Value is modified.");
}
static void addlink5_z_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink5_z_Value;
    callback.onWrite = afterWritelink5_z_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

static void beforeReadlink6_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_Value is to be updated.");
    updateCurrentlink6_Value(server, *nodeid);
}
static void afterWritelink6_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_Value is modified.");
}
static void addlink6_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink6_Value;
    callback.onWrite = afterWritelink6_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink6_angle_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_angle_Value is to be updated.");
    updateCurrentlink6_angle_Value(server, *nodeid);
}
static void afterWritelink6_angle_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_angle_Value is modified.");
}
static void addlink6_angle_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink6_angle_Value;
    callback.onWrite = afterWritelink6_angle_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink6_angle_angleDownLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_angle_angleDownLimit_Value is to be updated.");
    updateCurrentlink6_angle_angleDownLimit_Value(server, *nodeid);
}
static void afterWritelink6_angle_angleDownLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_angle_angleDownLimit_Value is modified.");
}
static void addlink6_angle_angleDownLimit_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink6_angle_angleDownLimit_Value;
    callback.onWrite = afterWritelink6_angle_angleDownLimit_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink6_angle_angleUpLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_angle_angleUpLimit_Value is to be updated.");
    updateCurrentlink6_angle_angleUpLimit_Value(server, *nodeid);
}
static void afterWritelink6_angle_angleUpLimit_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_angle_angleUpLimit_Value is modified.");
}
static void addlink6_angle_angleUpLimit_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink6_angle_angleUpLimit_Value;
    callback.onWrite = afterWritelink6_angle_angleUpLimit_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink6_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    // UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_angle_angleValue_Value is to be updated.");
    updateCurrentlink6_angle_angleValue_Value(server, *nodeid);
}
static void afterWritelink6_angle_angleValue_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_angle_angleValue_Value is modified.");
}
static void addlink6_angle_angleValue_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink6_angle_angleValue_Value;
    callback.onWrite = afterWritelink6_angle_angleValue_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink6_x_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_x_Value is to be updated.");
    updateCurrentlink6_x_Value(server, *nodeid);
}
static void afterWritelink6_x_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_x_Value is modified.");
}
static void addlink6_x_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink6_x_Value;
    callback.onWrite = afterWritelink6_x_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink6_y_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_y_Value is to be updated.");
    updateCurrentlink6_y_Value(server, *nodeid);
}
static void afterWritelink6_y_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_y_Value is modified.");
}
static void addlink6_y_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink6_y_Value;
    callback.onWrite = afterWritelink6_y_Value;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}
static void beforeReadlink6_z_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_z_Value is to be updated.");
    updateCurrentlink6_z_Value(server, *nodeid);
}
static void afterWritelink6_z_Value(UA_Server *server,
        const UA_NodeId *sessionId, void *sessionContext,
        const UA_NodeId *nodeid, void *nodeContext,
        const UA_NumericRange *range, const UA_DataValue *data) { 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "link6_z_Value is modified.");
}
static void addlink6_z_CallbackToRobot(UA_Server *server, UA_NodeId currentNodeId) {
    UA_ValueCallback callback;
    callback.onRead = beforeReadlink6_z_Value;
    callback.onWrite = afterWritelink6_z_Value;
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

        // 获取节点nodeid的自动生成code
        UA_QualifiedName link1_nameArr[2] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link1")};
        UA_NodeId link1_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 2, link1_nameArr, &link1_id);
        hashmap_set(hashmap, "link1_", &link1_id, NULL);

        UA_QualifiedName link1_angle_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link1"), UA_QUALIFIEDNAME(2, "angle")};
        UA_NodeId link1_angle_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link1_angle_nameArr, &link1_angle_id);
        hashmap_set(hashmap, "link1_angle_", &link1_angle_id, NULL);

        UA_QualifiedName link1_angle_angleDownLimit_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link1"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleDownLimit")};
        UA_NodeId link1_angle_angleDownLimit_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link1_angle_angleDownLimit_nameArr, &link1_angle_angleDownLimit_id);
        hashmap_set(hashmap, "link1_angle_angleDownLimit_", &link1_angle_angleDownLimit_id, NULL);

        UA_QualifiedName link1_angle_angleUpLimit_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link1"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleUpLimit")};
        UA_NodeId link1_angle_angleUpLimit_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link1_angle_angleUpLimit_nameArr, &link1_angle_angleUpLimit_id);
        hashmap_set(hashmap, "link1_angle_angleUpLimit_", &link1_angle_angleUpLimit_id, NULL);

        UA_QualifiedName link1_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link1"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId link1_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link1_angle_angleValue_nameArr, &link1_angle_angleValue_id);
        hashmap_set(hashmap, "link1_angle_angleValue_", &link1_angle_angleValue_id, NULL);

        UA_QualifiedName link1_x_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link1"), UA_QUALIFIEDNAME(2, "x")};
        UA_NodeId link1_x_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link1_x_nameArr, &link1_x_id);
        hashmap_set(hashmap, "link1_x_", &link1_x_id, NULL);

        UA_QualifiedName link1_y_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link1"), UA_QUALIFIEDNAME(2, "y")};
        UA_NodeId link1_y_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link1_y_nameArr, &link1_y_id);
        hashmap_set(hashmap, "link1_y_", &link1_y_id, NULL);

        UA_QualifiedName link1_z_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link1"), UA_QUALIFIEDNAME(2, "z")};
        UA_NodeId link1_z_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link1_z_nameArr, &link1_z_id);
        hashmap_set(hashmap, "link1_z_", &link1_z_id, NULL);

        UA_QualifiedName link2_nameArr[2] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link2")};
        UA_NodeId link2_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 2, link2_nameArr, &link2_id);
        hashmap_set(hashmap, "link2_", &link2_id, NULL);

        UA_QualifiedName link2_angle_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link2"), UA_QUALIFIEDNAME(2, "angle")};
        UA_NodeId link2_angle_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link2_angle_nameArr, &link2_angle_id);
        hashmap_set(hashmap, "link2_angle_", &link2_angle_id, NULL);

        UA_QualifiedName link2_angle_angleDownLimit_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link2"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleDownLimit")};
        UA_NodeId link2_angle_angleDownLimit_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link2_angle_angleDownLimit_nameArr, &link2_angle_angleDownLimit_id);
        hashmap_set(hashmap, "link2_angle_angleDownLimit_", &link2_angle_angleDownLimit_id, NULL);

        UA_QualifiedName link2_angle_angleUpLimit_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link2"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleUpLimit")};
        UA_NodeId link2_angle_angleUpLimit_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link2_angle_angleUpLimit_nameArr, &link2_angle_angleUpLimit_id);
        hashmap_set(hashmap, "link2_angle_angleUpLimit_", &link2_angle_angleUpLimit_id, NULL);

        UA_QualifiedName link2_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link2"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId link2_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link2_angle_angleValue_nameArr, &link2_angle_angleValue_id);
        hashmap_set(hashmap, "link2_angle_angleValue_", &link2_angle_angleValue_id, NULL);

        UA_QualifiedName link2_x_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link2"), UA_QUALIFIEDNAME(2, "x")};
        UA_NodeId link2_x_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link2_x_nameArr, &link2_x_id);
        hashmap_set(hashmap, "link2_x_", &link2_x_id, NULL);

        UA_QualifiedName link2_y_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link2"), UA_QUALIFIEDNAME(2, "y")};
        UA_NodeId link2_y_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link2_y_nameArr, &link2_y_id);
        hashmap_set(hashmap, "link2_y_", &link2_y_id, NULL);

        UA_QualifiedName link2_z_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link2"), UA_QUALIFIEDNAME(2, "z")};
        UA_NodeId link2_z_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link2_z_nameArr, &link2_z_id);
        hashmap_set(hashmap, "link2_z_", &link2_z_id, NULL);

        UA_QualifiedName link3_nameArr[2] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link3")};
        UA_NodeId link3_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 2, link3_nameArr, &link3_id);
        hashmap_set(hashmap, "link3_", &link3_id, NULL);

        UA_QualifiedName link3_angle_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link3"), UA_QUALIFIEDNAME(2, "angle")};
        UA_NodeId link3_angle_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link3_angle_nameArr, &link3_angle_id);
        hashmap_set(hashmap, "link3_angle_", &link3_angle_id, NULL);

        UA_QualifiedName link3_angle_angleDownLimit_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link3"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleDownLimit")};
        UA_NodeId link3_angle_angleDownLimit_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link3_angle_angleDownLimit_nameArr, &link3_angle_angleDownLimit_id);
        hashmap_set(hashmap, "link3_angle_angleDownLimit_", &link3_angle_angleDownLimit_id, NULL);

        UA_QualifiedName link3_angle_angleUpLimit_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link3"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleUpLimit")};
        UA_NodeId link3_angle_angleUpLimit_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link3_angle_angleUpLimit_nameArr, &link3_angle_angleUpLimit_id);
        hashmap_set(hashmap, "link3_angle_angleUpLimit_", &link3_angle_angleUpLimit_id, NULL);

        UA_QualifiedName link3_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link3"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId link3_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link3_angle_angleValue_nameArr, &link3_angle_angleValue_id);
        hashmap_set(hashmap, "link3_angle_angleValue_", &link3_angle_angleValue_id, NULL);

        UA_QualifiedName link3_x_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link3"), UA_QUALIFIEDNAME(2, "x")};
        UA_NodeId link3_x_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link3_x_nameArr, &link3_x_id);
        hashmap_set(hashmap, "link3_x_", &link3_x_id, NULL);

        UA_QualifiedName link3_y_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link3"), UA_QUALIFIEDNAME(2, "y")};
        UA_NodeId link3_y_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link3_y_nameArr, &link3_y_id);
        hashmap_set(hashmap, "link3_y_", &link3_y_id, NULL);

        UA_QualifiedName link3_z_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link3"), UA_QUALIFIEDNAME(2, "z")};
        UA_NodeId link3_z_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link3_z_nameArr, &link3_z_id);
        hashmap_set(hashmap, "link3_z_", &link3_z_id, NULL);

        UA_QualifiedName link4_nameArr[2] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link4")};
        UA_NodeId link4_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 2, link4_nameArr, &link4_id);
        hashmap_set(hashmap, "link4_", &link4_id, NULL);

        UA_QualifiedName link4_angle_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link4"), UA_QUALIFIEDNAME(2, "angle")};
        UA_NodeId link4_angle_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link4_angle_nameArr, &link4_angle_id);
        hashmap_set(hashmap, "link4_angle_", &link4_angle_id, NULL);

        UA_QualifiedName link4_angle_angleDownLimit_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link4"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleDownLimit")};
        UA_NodeId link4_angle_angleDownLimit_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link4_angle_angleDownLimit_nameArr, &link4_angle_angleDownLimit_id);
        hashmap_set(hashmap, "link4_angle_angleDownLimit_", &link4_angle_angleDownLimit_id, NULL);

        UA_QualifiedName link4_angle_angleUpLimit_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link4"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleUpLimit")};
        UA_NodeId link4_angle_angleUpLimit_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link4_angle_angleUpLimit_nameArr, &link4_angle_angleUpLimit_id);
        hashmap_set(hashmap, "link4_angle_angleUpLimit_", &link4_angle_angleUpLimit_id, NULL);

        UA_QualifiedName link4_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link4"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId link4_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link4_angle_angleValue_nameArr, &link4_angle_angleValue_id);
        hashmap_set(hashmap, "link4_angle_angleValue_", &link4_angle_angleValue_id, NULL);

        UA_QualifiedName link4_x_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link4"), UA_QUALIFIEDNAME(2, "x")};
        UA_NodeId link4_x_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link4_x_nameArr, &link4_x_id);
        hashmap_set(hashmap, "link4_x_", &link4_x_id, NULL);

        UA_QualifiedName link4_y_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link4"), UA_QUALIFIEDNAME(2, "y")};
        UA_NodeId link4_y_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link4_y_nameArr, &link4_y_id);
        hashmap_set(hashmap, "link4_y_", &link4_y_id, NULL);

        UA_QualifiedName link4_z_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link4"), UA_QUALIFIEDNAME(2, "z")};
        UA_NodeId link4_z_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link4_z_nameArr, &link4_z_id);
        hashmap_set(hashmap, "link4_z_", &link4_z_id, NULL);

        UA_QualifiedName link5_nameArr[2] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link5")};
        UA_NodeId link5_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 2, link5_nameArr, &link5_id);
        hashmap_set(hashmap, "link5_", &link5_id, NULL);

        UA_QualifiedName link5_angle_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link5"), UA_QUALIFIEDNAME(2, "angle")};
        UA_NodeId link5_angle_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link5_angle_nameArr, &link5_angle_id);
        hashmap_set(hashmap, "link5_angle_", &link5_angle_id, NULL);

        UA_QualifiedName link5_angle_angleDownLimit_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link5"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleDownLimit")};
        UA_NodeId link5_angle_angleDownLimit_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link5_angle_angleDownLimit_nameArr, &link5_angle_angleDownLimit_id);
        hashmap_set(hashmap, "link5_angle_angleDownLimit_", &link5_angle_angleDownLimit_id, NULL);

        UA_QualifiedName link5_angle_angleUpLimit_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link5"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleUpLimit")};
        UA_NodeId link5_angle_angleUpLimit_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link5_angle_angleUpLimit_nameArr, &link5_angle_angleUpLimit_id);
        hashmap_set(hashmap, "link5_angle_angleUpLimit_", &link5_angle_angleUpLimit_id, NULL);

        UA_QualifiedName link5_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link5"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId link5_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link5_angle_angleValue_nameArr, &link5_angle_angleValue_id);
        hashmap_set(hashmap, "link5_angle_angleValue_", &link5_angle_angleValue_id, NULL);

        UA_QualifiedName link5_x_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link5"), UA_QUALIFIEDNAME(2, "x")};
        UA_NodeId link5_x_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link5_x_nameArr, &link5_x_id);
        hashmap_set(hashmap, "link5_x_", &link5_x_id, NULL);

        UA_QualifiedName link5_y_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link5"), UA_QUALIFIEDNAME(2, "y")};
        UA_NodeId link5_y_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link5_y_nameArr, &link5_y_id);
        hashmap_set(hashmap, "link5_y_", &link5_y_id, NULL);

        UA_QualifiedName link5_z_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link5"), UA_QUALIFIEDNAME(2, "z")};
        UA_NodeId link5_z_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link5_z_nameArr, &link5_z_id);
        hashmap_set(hashmap, "link5_z_", &link5_z_id, NULL);

        UA_QualifiedName link6_nameArr[2] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link6")};
        UA_NodeId link6_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 2, link6_nameArr, &link6_id);
        hashmap_set(hashmap, "link6_", &link6_id, NULL);

        UA_QualifiedName link6_angle_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link6"), UA_QUALIFIEDNAME(2, "angle")};
        UA_NodeId link6_angle_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link6_angle_nameArr, &link6_angle_id);
        hashmap_set(hashmap, "link6_angle_", &link6_angle_id, NULL);

        UA_QualifiedName link6_angle_angleDownLimit_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link6"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleDownLimit")};
        UA_NodeId link6_angle_angleDownLimit_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link6_angle_angleDownLimit_nameArr, &link6_angle_angleDownLimit_id);
        hashmap_set(hashmap, "link6_angle_angleDownLimit_", &link6_angle_angleDownLimit_id, NULL);

        UA_QualifiedName link6_angle_angleUpLimit_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link6"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleUpLimit")};
        UA_NodeId link6_angle_angleUpLimit_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link6_angle_angleUpLimit_nameArr, &link6_angle_angleUpLimit_id);
        hashmap_set(hashmap, "link6_angle_angleUpLimit_", &link6_angle_angleUpLimit_id, NULL);

        UA_QualifiedName link6_angle_angleValue_nameArr[4] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link6"), UA_QUALIFIEDNAME(2, "angle"), UA_QUALIFIEDNAME(2, "angleValue")};
        UA_NodeId link6_angle_angleValue_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 4, link6_angle_angleValue_nameArr, &link6_angle_angleValue_id);
        hashmap_set(hashmap, "link6_angle_angleValue_", &link6_angle_angleValue_id, NULL);

        UA_QualifiedName link6_x_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link6"), UA_QUALIFIEDNAME(2, "x")};
        UA_NodeId link6_x_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link6_x_nameArr, &link6_x_id);
        hashmap_set(hashmap, "link6_x_", &link6_x_id, NULL);

        UA_QualifiedName link6_y_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link6"), UA_QUALIFIEDNAME(2, "y")};
        UA_NodeId link6_y_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link6_y_nameArr, &link6_y_id);
        hashmap_set(hashmap, "link6_y_", &link6_y_id, NULL);

        UA_QualifiedName link6_z_nameArr[3] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "link6"), UA_QUALIFIEDNAME(2, "z")};
        UA_NodeId link6_z_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 3, link6_z_nameArr, &link6_z_id);
        hashmap_set(hashmap, "link6_z_", &link6_z_id, NULL);

        // 获取节点nodeid自动生成code结束

        // UA_QualifiedName Start_nameArr[2] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "Start")};
        // UA_NodeId Start_id;
        // ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 2, Start_nameArr, &Start_id);
        // hashmap_set(hashmap, "Start_", &Start_id, NULL);

        UA_QualifiedName Status_nameArr[2] = {UA_QUALIFIEDNAME(1, "myFirstRobot"), UA_QUALIFIEDNAME(2, "Status")};
        UA_NodeId Status_id;
        ret = findNodeID(server, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 2, Status_nameArr, &Status_id);
        hashmap_set(hashmap, "Status_", &Status_id, NULL);
        
        UA_NodeId tmp = *(UA_NodeId *)hashmap_get(hashmap, "link1_");
        printf("%u \n", tmp.identifier.numeric);


        // 将回调函数绑定到server
        addStatus_CallbackToRobot(server, Status_id);
        addlink1_x_CallbackToRobot(server, link1_x_id);
        addlink1_x_CallbackToRobot(server, link1_y_id);
        addlink1_x_CallbackToRobot(server, link1_z_id);
        addlink5_x_CallbackToRobot(server, link5_x_id);
        addlink5_y_CallbackToRobot(server, link5_y_id);
        addlink5_z_CallbackToRobot(server, link5_z_id);
        
        addlink5_angle_angleUpLimit_CallbackToRobot(server, link5_angle_angleUpLimit_id);
        addlink5_angle_angleDownLimit_CallbackToRobot(server, link5_angle_angleDownLimit_id);


        addlink1_angle_angleValue_CallbackToRobot(server, link1_angle_angleValue_id);
        addlink2_angle_angleValue_CallbackToRobot(server, link2_angle_angleValue_id);
        addlink3_angle_angleValue_CallbackToRobot(server, link3_angle_angleValue_id);
        addlink4_angle_angleValue_CallbackToRobot(server, link4_angle_angleValue_id);
        addlink5_angle_angleValue_CallbackToRobot(server, link5_angle_angleValue_id);
        addlink6_angle_angleValue_CallbackToRobot(server, link6_angle_angleValue_id);
        

        retval = UA_Server_run(server, &running);
    }

    UA_Server_delete(server);

    return (int) retval;
}