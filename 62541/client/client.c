#include "open62541.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

// 暂时不用
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



    // WARNING: 必须用取地址的方式
    char *link1_angle_angleValue_paths[4] = {"myFirstRobot", "link1", "angle", "angleValue"};
    UA_NodeId link1_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &link1_angle_angleValue_Id, link1_angle_angleValue_paths);
    
    char *link2_angle_angleValue_paths[4] = {"myFirstRobot", "link2", "angle", "angleValue"};
    UA_NodeId link2_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &link2_angle_angleValue_Id, link2_angle_angleValue_paths);

    char *link3_angle_angleValue_paths[4] = {"mySecondRobot", "link3", "angle", "angleValue"};
    UA_NodeId link3_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &link3_angle_angleValue_Id, link3_angle_angleValue_paths);

    char *link4_angle_angleValue_paths[4] = {"mySecondRobot", "link4", "angle", "angleValue"};
    UA_NodeId link4_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &link4_angle_angleValue_Id, link4_angle_angleValue_paths);

    char *link5_angle_angleValue_paths[4] = {"myFirstRobot", "link5", "angle", "angleValue"};
    UA_NodeId link5_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &link5_angle_angleValue_Id, link5_angle_angleValue_paths);

    char *link6_angle_angleValue_paths[4] = {"myFirstRobot", "link6", "angle", "angleValue"};
    UA_NodeId link6_angle_angleValue_Id;
    translateBrowsePathsToNodeIdsRequest(client, &link6_angle_angleValue_Id, link6_angle_angleValue_paths);

    // UA_NodeId link1_angle_angleValue_Id;
    // char *link1_angle_angleValue_path = "link1_angle_angleValue_";
    // callMethodGetNodeId(client, link1_angle_angleValue_path, &link1_angle_angleValue_Id);

    // UA_NodeId link2_angle_angleValue_Id;
    // char *link2_angle_angleValue_path = "link2_angle_angleValue_";
    // callMethodGetNodeId(client, link2_angle_angleValue_path, &link2_angle_angleValue_Id);

    // UA_NodeId link3_angle_angleValue_Id;
    // char *link3_angle_angleValue_path = "link3_angle_angleValue_";
    // callMethodGetNodeId(client, link3_angle_angleValue_path, &link3_angle_angleValue_Id);

    // UA_NodeId link4_angle_angleValue_Id;
    // char *link4_angle_angleValue_path = "link4_angle_angleValue_";
    // callMethodGetNodeId(client, link4_angle_angleValue_path, &link4_angle_angleValue_Id);

    // UA_NodeId link5_angle_angleValue_Id;
    // char *link5_angle_angleValue_path = "link5_angle_angleValue_";
    // callMethodGetNodeId(client, link5_angle_angleValue_path, &link5_angle_angleValue_Id);

    // UA_NodeId link6_angle_angleValue_Id;
    // char *link6_angle_angleValue_path = "link6_angle_angleValue_";
    // callMethodGetNodeId(client, link6_angle_angleValue_path, &link6_angle_angleValue_Id);

    // UA_Double link1_angle_angleValue = 13.0;
    // UA_Variant newValue;
    // UA_Variant_init(&newValue);
    // UA_Variant_setScalar(&newValue, &link1_angle_angleValue, &UA_TYPES[UA_TYPES_DOUBLE]);
    // retval = UA_Client_writeValueAttribute(client, *link1_angle_angleValue_Id, &newValue);
    // if (retval == UA_STATUSCODE_GOOD) {

    // }

    

    int joint;
    while (1) {
        printf("quit 'q' or continue 'c' ?");
        scanf(" %c", &ch);
		printf("%c\n", ch);
		if ('q' == ch) break;
        while ((ch = getchar()) != '\n' && ch != EOF);

        printf("input q:=");
		scanf("%f %f %f %f %f %f", &q[0], &q[1], &q[2], &q[3], &q[4], &q[5]);
        for (joint = 0; joint < 6; joint++) {
			q[joint] *= (3.14159265f / 180.0f);
		}
        classic6dofForKine(q, &pose);
        printf("FK      :=< %.6f, %.6f, %.6f, %.6f, %.6f, %.6f >\n", pose.X, pose.Y, pose.Z, pose.A, pose.B, pose.C);
        classic6dofInvKine(&pose, q_last, &q_sol);
        for (joint = 0; joint < 6; joint++) {
			q_sol.sol[0][joint] *= (180.0f / 3.14159265f);
		}
        joint = 0;
        writeServerValueDouble(client, link1_angle_angleValue_Id, q_sol.sol[joint][0]);
        writeServerValueDouble(client, link2_angle_angleValue_Id, q_sol.sol[joint][1]);
        writeServerValueDouble(client, link3_angle_angleValue_Id, q_sol.sol[joint][2]);
        writeServerValueDouble(client, link4_angle_angleValue_Id, q_sol.sol[joint][3]);
        writeServerValueDouble(client, link5_angle_angleValue_Id, q_sol.sol[joint][4]);
        writeServerValueDouble(client, link6_angle_angleValue_Id, q_sol.sol[joint][5]);
		printf("q[%d]    :=< %.6f, %.6f, %.6f, %.6f, %.6f, %.6f >\n", joint, q_sol.sol[joint][0], q_sol.sol[joint][1], q_sol.sol[joint][2], q_sol.sol[joint][3], q_sol.sol[joint][4], q_sol.sol[joint][5]);
    }

    UA_Client_delete(client);

    return EXIT_SUCCESS;

    
}