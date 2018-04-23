#include <stdio.h>
#include <stdlib.h>

typedef struct _Vertex {
	int data;
	struct _Vertex* nextvertex;
	struct _Edge* edgelist;
}Vertex;

typedef struct _Edge {
	int weight;
	struct _Edge* nextedge;
	Vertex* from;
	Vertex* target;
}Edge;

typedef struct _Graph {
	Vertex* vertices;
}Graph;

Graph* CreateGraph()
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->vertices = NULL;

	return graph;
}

Vertex* CreateVertex(int data)
{
	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
	vertex->data = data;
	vertex->edgelist = NULL;
	vertex->nextvertex = NULL;

	return vertex;
}

Edge* CreateEdge(Vertex* from, Vertex* target, int weight)
{
	Edge* edge = (Edge*)malloc(sizeof(Edge));
	edge->weight = weight;
	edge->from = from;
	edge->target = target;
	edge->nextedge = NULL;

	return edge;
}

void AddVertex(Graph* graph, Vertex* vertex)
{
	Vertex* vertexlist = graph->vertices;

	if (vertexlist == NULL)
		graph->vertices = vertex;
	else
	{
		while (vertexlist->nextvertex != NULL)
			vertexlist = vertexlist->nextvertex;
		vertexlist->nextvertex = vertex;
	}
}

void AddEdge(Vertex* from, Vertex* target, int weight)
{
	Edge* edge = CreateEdge(from, target, weight);
	Edge* edgelist = from->edgelist;

	if (edgelist == NULL)
		from->edgelist = edge;
	else
	{
		while (edgelist->nextedge != NULL)
			edgelist = edgelist->nextedge;
		edgelist->nextedge = edge;
	}
}

void DestroyVertex(Vertex* vertex);

void DestroyGraph(Graph* graph)
{
	while (graph->vertices != NULL)
	{
		Vertex* nextvertex = graph->vertices->nextvertex;
		DestroyVertex(graph->vertices);
		graph->vertices = nextvertex;
	}

	free(graph);
}

void DestroyVertex(Vertex* vertex)
{
	while (vertex->edgelist != NULL)
	{
		Edge* nextedge = vertex->edgelist->nextedge;
		free(vertex->edgelist);
		vertex->edgelist = nextedge;
	}

	free(vertex);
}

void PrintGraph(Graph* graph)
{
	if (graph->vertices == NULL)
		return;

	Vertex* vertex = graph->vertices;
	Edge* edge = NULL;

	while (vertex != NULL)
	{
		printf("%d : ", vertex->data);

		edge = vertex->edgelist;
		if (edge != NULL)
		{
			while (edge != NULL)
			{
				printf("%d[%d] ", edge->target->data, edge->weight);
				edge = edge->nextedge;
			}
		}
		printf("\n");
		vertex = vertex->nextvertex;
	}
}

int main()
{
	Graph* graph = CreateGraph();

	Vertex* v1 = CreateVertex(1);
	Vertex* v2 = CreateVertex(2);
	Vertex* v3 = CreateVertex(3);
	Vertex* v4 = CreateVertex(4);
	Vertex* v5 = CreateVertex(5);

	AddVertex(graph, v1);
	AddVertex(graph, v2);
	AddVertex(graph, v3);
	AddVertex(graph, v4);
	AddVertex(graph, v5);

	AddEdge(v1, v2, 10);
	AddEdge(v1, v4, 40);
	AddEdge(v2, v5, 100);
	AddEdge(v3, v4, 120);
	AddEdge(v3, v2, 60);
	AddEdge(v3, v1, 30);
	AddEdge(v5, v2, 100);
	AddEdge(v5, v3, 150);

	PrintGraph(graph);

	DestroyGraph(graph);

	return 0;
}