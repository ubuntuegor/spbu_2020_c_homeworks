#ifndef SPBU_2020_C_GRAPH_H
#define SPBU_2020_C_GRAPH_H
#include <stdbool.h>

typedef struct Graph Graph;
typedef struct GraphNode GraphNode;

Graph* createGraph(int nodeCount, bool bidirectional);
void connectGraph(Graph*, int fromNode, int toNode, int distance);
void destroyGraph(Graph**);

int getOutwardGraphConnections(Graph*, int node, GraphNode*** connectionsPtr);
int getInwardGraphConnections(Graph*, int node, GraphNode*** connectionsPtr);
int getGraphConnections(Graph*, int node, GraphNode*** connectionsPtr);

int getIdGraphNode(GraphNode*);
int getDistanceGraphNode(GraphNode*);

void destroyGraphConnections(GraphNode*** connectionsPtr, int connectionCount);

bool existsGraphPath(Graph*, int fromNode, int toNode);
bool isGraphAcyclic(Graph*);

#endif /* SPBU_2020_C_GRAPH_H */
