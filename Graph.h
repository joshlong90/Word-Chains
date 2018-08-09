// Graph ADT interface ... COMP9024 17s2
#include "queue.h"
#include <stdbool.h>

typedef struct GraphRep *Graph;

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
   Vertex v;
   Vertex w;
} Edge;

Graph newGraph(int);
void  insertEdge(Graph, Edge);
void  removeEdge(Graph, Edge);
bool  adjacent(Graph, Vertex, Vertex);
void  showGraph(Graph);
void  freeGraph(Graph);

// Additional functions.
void  showEdges(Graph, char **);    // print edges as strings.
int adjacentNode(Graph, int, int);  // Checks if pair of nodes are adjacent.
