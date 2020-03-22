#include "utils.h"


int findNodeID(UA_Server *server,
                      UA_NodeId parentNode,
                      const int relativePathCnt,
                      const UA_QualifiedName targetNameArr[],
                      UA_NodeId *result) {
    int ret = 0;
    UA_BrowsePathResult bpr = UA_Server_browseSimplifiedBrowsePath(server, parentNode, relativePathCnt, targetNameArr);
    
    if (bpr.statusCode != UA_STATUSCODE_GOOD || bpr.targetsSize < 1) {
        printf("error: %s\n", UA_StatusCode_name(bpr.statusCode));
        ret = -1;
    } else {
        UA_NodeId_copy(&bpr.targets[0].targetId.nodeId, result);
    }

    UA_BrowsePathResult_deleteMembers(&bpr);
    
    return ret;
}