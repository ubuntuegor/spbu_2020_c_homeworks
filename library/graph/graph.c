#include "graph.h"
#include <stdlib.h>

struct Graph {
    bool bidirectional;
    int nodeCount;
    int** connectionMatrix;
};

struct GraphNode {
    int id;
    int distance;
};

Graph* createGraph(int nodeCount, bool bidirectional)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->bidirectional = bidirectional;
    graph->nodeCount = nodeCount;
    graph->connectionMatrix = (int**)calloc(nodeCount, sizeof(int*));
    for (int i = 0; i < nodeCount; ++i)
        graph->connectionMatrix[i] = (int*)calloc(nodeCount, sizeof(int));
    return graph;
}

void connectGraph(Graph* graph, int fromNode, int toNode, int distance)
{
    if (graph == NULL)
        return;

    graph->connectionMatrix[fromNode][toNode] = distance;
    if (graph->bidirectional)
        graph->connectionMatrix[toNode][fromNode] = distance;
}

void destroyGraph(Graph** graphPtr)
{
    if (graphPtr == NULL || *graphPtr == NULL)
        return;

    Graph* graph = *graphPtr;

    for (int i = 0; i < graph->nodeCount; ++i)
        free(graph->connectionMatrix[i]);

    free(graph);
    *graphPtr = NULL;
}

GraphNode* createGraphNode(int id, int distance)
{
    GraphNode* graphNode = (GraphNode*)malloc(sizeof(GraphNode));
    graphNode->id = id;
    graphNode->distance = distance;
    return graphNode;
}

void destroyGraphNode(GraphNode** graphNodePtr)
{
    if (graphNodePtr == NULL || *graphNodePtr == NULL)
        return;

    free(*graphNodePtr);
    *graphNodePtr = NULL;
}

int getOutwardGraphConnections(Graph* graph, int node, GraphNode*** connectionsPtr)
{
    if (graph == NULL || connectionsPtr == NULL)
        return 0;

    int foundNodes = 0;
    GraphNode** nodeArray = NULL;

    for (int i = 0; i < graph->nodeCount; ++i) {
        if (graph->connectionMatrix[node][i] == 0)
            continue;

        foundNodes++;
        if (nodeArray == NULL)
            nodeArray = (GraphNode**)calloc(1, sizeof(GraphNode*));
        else
            nodeArray = (GraphNode**)realloc(nodeArray, foundNodes * sizeof(GraphNode*));

        nodeArray[foundNodes - 1] = createGraphNode(i, graph->connectionMatrix[node][i]);
    }

    *connectionsPtr = nodeArray;
    return foundNodes;
}

int getInwardGraphConnections(Graph* graph, int node, GraphNode*** connectionsPtr)
{
    if (graph == NULL || connectionsPtr == NULL)
        return 0;

    int foundNodes = 0;
    GraphNode** nodeArray = NULL;

    for (int i = 0; i < graph->nodeCount; ++i) {
        if (graph->connectionMatrix[i][node] == 0)
            continue;

        foundNodes++;
        if (nodeArray == NULL)
            nodeArray = (GraphNode**)calloc(1, sizeof(GraphNode*));
        else
            nodeArray = (GraphNode**)realloc(nodeArray, foundNodes * sizeof(GraphNode*));

        nodeArray[foundNodes - 1] = createGraphNode(i, graph->connectionMatrix[i][node]);
    }

    *connectionsPtr = nodeArray;
    return foundNodes;
}

int getGraphConnections(Graph* graph, int node, GraphNode*** connectionsPtr)
{
    if (graph == NULL || connectionsPtr == NULL)
        return 0;

    int foundNodes = 0;
    GraphNode** nodeArray = NULL;

    bool* visitedNodes = (bool*)calloc(graph->nodeCount, sizeof(bool));

    for (int i = 0; i < graph->nodeCount; ++i) {
        if (graph->connectionMatrix[i][node] == 0 || visitedNodes[i])
            continue;

        foundNodes++;
        if (nodeArray == NULL)
            nodeArray = (GraphNode**)calloc(1, sizeof(GraphNode*));
        else
            nodeArray = (GraphNode**)realloc(nodeArray, foundNodes * sizeof(GraphNode*));

        nodeArray[foundNodes - 1] = createGraphNode(i, graph->connectionMatrix[i][node]);
        visitedNodes[i] = true;
    }

    for (int j = 0; j < graph->nodeCount; ++j) {
        if (graph->connectionMatrix[node][j] == 0 || visitedNodes[j])
            continue;

        foundNodes++;
        if (nodeArray == NULL)
            nodeArray = (GraphNode**)calloc(1, sizeof(GraphNode*));
        else
            nodeArray = (GraphNode**)realloc(nodeArray, foundNodes * sizeof(GraphNode*));

        nodeArray[foundNodes - 1] = createGraphNode(j, graph->connectionMatrix[node][j]);
        visitedNodes[j] = true;
    }

    free(visitedNodes);

    *connectionsPtr = nodeArray;
    return foundNodes;
}

int getIdGraphNode(GraphNode* graphNode)
{
    if (graphNode == NULL)
        return 0;
    return graphNode->id;
}

int getDistanceGraphNode(GraphNode* graphNode)
{
    if (graphNode == NULL)
        return 0;
    return graphNode->distance;
}

void destroyGraphConnections(GraphNode*** connectionsPtr, int connectionCount)
{
    if (connectionsPtr == NULL || *connectionsPtr == NULL)
        return;

    GraphNode** connections = *connectionsPtr;
    for (int i = 0; i < connectionCount; ++i)
        destroyGraphNode(&connections[i]);

    free(connections);
    *connectionsPtr = NULL;
}

bool existsGraphPathRecursive(Graph* graph, int fromNode, int toNode, bool* visitedNodes)
{
    visitedNodes[fromNode] = true;
    for (int i = 0; i < graph->nodeCount; ++i) {
        if (graph->connectionMatrix[fromNode][i] == 0)
            continue;
        if (i == toNode)
            return true;
        if (visitedNodes[i])
            continue;
        if (existsGraphPathRecursive(graph, i, toNode, visitedNodes))
            return true;
    }
    return false;
}

bool existsGraphPath(Graph* graph, int fromNode, int toNode)
{
    if (graph == NULL)
        return false;

    bool* visitedNodes = (bool*)calloc(graph->nodeCount, sizeof(bool));
    bool result = existsGraphPathRecursive(graph, fromNode, toNode, visitedNodes);
    free(visitedNodes);

    return result;
}

bool isGraphAcyclicRecursive(Graph* graph, int currentNode, bool* visitedNodes, bool* markedNodes)
{
    visitedNodes[currentNode] = true;
    markedNodes[currentNode] = true;
    int markedNodesAroundCount = 0;
    for (int i = 0; i < graph->nodeCount; ++i) {
        if (graph->connectionMatrix[currentNode][i] == 0)
            continue;

        if (markedNodes[i])
            markedNodesAroundCount++;
        if (graph->bidirectional && markedNodesAroundCount >= 2)
            return false;
        if (!graph->bidirectional && markedNodesAroundCount >= 1)
            return false;

        if (visitedNodes[i])
            continue;
        if (!isGraphAcyclicRecursive(graph, i, visitedNodes, markedNodes))
            return false;
    }
    return true;
}

bool isGraphAcyclic(Graph* graph)
{
    if (graph == NULL)
        return false;

    bool result = true;
    bool* visitedNodes = (bool*)calloc(graph->nodeCount, sizeof(bool));

    for (int i = 0; i < graph->nodeCount; ++i) {
        if (visitedNodes[i])
            continue;

        bool* markedNodes = (bool*)calloc(graph->nodeCount, sizeof(bool));
        bool isSubtreeAcyclic = isGraphAcyclicRecursive(graph, i, visitedNodes, markedNodes);
        free(markedNodes);

        if (!isSubtreeAcyclic) {
            result = false;
            break;
        }
    }

    free(visitedNodes);

    return result;
}
