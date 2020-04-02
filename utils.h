#ifndef UTILS_H_
#define UTILS_H_

#include "open62541.h"
#include "stdio.h"
/**
 * Description: 寻找节点的id
 * Author: tanghuyin
*/
int findNodeID(UA_Server *server,
                UA_NodeId parentNode,
                const int relativePathCnt,
                const UA_QualifiedName targetNameArr[],
                UA_NodeId *result);

size_t hash(const void *key);

bool compare(const void *key1, const void *key2);

#endif