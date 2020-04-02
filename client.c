#include "open62541.h"
#include <signal.h>
#include <stdlib.h>

UA_Boolean running = true;

void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

int main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_Client *client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
    if (retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return (int)retval;
    }

    printf("%s", "SUCESSFULLY ESTABLISHED\n");

    UA_NodeId *returnId;
    
    #define BROWSE_PATHS_SIZE 3
    char *paths[BROWSE_PATHS_SIZE] = {"myFirstRobot", "link1", "x"};
    UA_UInt32 ids[BROWSE_PATHS_SIZE] = {UA_NS0ID_ORGANIZES, UA_NS0ID_HASCOMPONENT, UA_NS0ID_HASCOMPONENT};
    int nsNumOfQualifiedName[BROWSE_PATHS_SIZE] = {1, 2, 2};

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
            UA_NodeId_copy(&response.results[0].targets[0].targetId.nodeId, returnId);
            printf("%u\n", (*returnId).identifier.numeric);
        } else {
            printf("%d\n", response.results[0].targetsSize);
        }
    } else {
        printf("Error: %s\n", UA_StatusCode_name(response.responseHeader.serviceResult));
    }

    UA_BrowsePath_deleteMembers(&browsePath);
    UA_TranslateBrowsePathsToNodeIdsResponse_deleteMembers(&response);


    UA_StatusCode retval1;

    UA_String arg = UA_STRING("link1_y_");
    UA_Variant input;
    UA_Variant_init(&input);
    UA_Variant_setScalarCopy(&input, &arg, &UA_TYPES[UA_TYPES_STRING]);
    size_t outputSize;
    UA_Variant *output;
    UA_NodeId outNodeId;
    retval1 = UA_Client_call(client, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), UA_NODEID_NUMERIC(1, 62541), 1, &input, &outputSize, &output);
    if (retval1 != UA_STATUSCODE_GOOD) {
        printf("Method call was unsuccessful, and %x returned values available.\n", retval);
        return;
    } else {
        outNodeId = *(UA_NodeId*) output->data;
        printf("%u", outNodeId.identifier.numeric);
        UA_Array_delete(output, outputSize, &UA_TYPES[UA_TYPES_VARIANT]);
    }

    UA_Variant_clear(&input);
    
    UA_Client_delete(client);

    return EXIT_SUCCESS;

    
}