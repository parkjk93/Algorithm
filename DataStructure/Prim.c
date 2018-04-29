#include <stdio.h>
#include <stdlib.h>

typedef struct _Vertex {
	char data;
	int visited; //-1 no, 0 yes
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
	int index;
}Graph;

typedef struct _Node {
	Edge* edge;
	struct _Node* nextnode;
}Node;

typedef struct _Queue {
	Node* front;
}Queue;

Graph* CreateGraph()
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->vertices = NULL;
	graph->index = 0;

	return graph;
}

Vertex* CreateVertex(char data)
{
	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
	vertex->data = data;
	vertex->visited = -1;
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

	graph->index++;
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

Vertex* SearchVertex(Graph* graph, char data) //있으면 vertex return, 없으면 NULL
{
	Vertex* temp = graph->vertices;
	while (temp != NULL)
	{
		if (temp->data == data)
			return temp;
		temp = temp->nextvertex;
	}

	return NULL;
}

bool SearchEdge(Graph* graph, char from, char target) //있으면 true 없으면 false
{
	Vertex* vertex = graph->vertices;
	Edge* edge = NULL;

	while (vertex != NULL)
	{
		edge = vertex->edgelist;
		if (edge != NULL)
		{
			while (edge != NULL)
			{
				if ((edge->from->data == from && edge->target->data == target) || (edge->from->data == target && edge->target->data == from))
					return true;
				edge = edge->nextedge;
			}
		}
		vertex = vertex->nextvertex;
	}

	return false;
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
		printf("%c : ", vertex->data);

		edge = vertex->edgelist;
		if (edge != NULL)
		{
			while (edge != NULL)
			{
				printf("%c[%d] ", edge->target->data, edge->weight);
				edge = edge->nextedge;
			}
		}
		printf("\n");
		vertex = vertex->nextvertex;
	}
	printf("graph index : %d\n", graph->index);
}

Queue* CreateQueue()
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->front = NULL;

	return queue;
}

Node* CreateNode(Edge* edge)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->edge = CreateEdge(edge->from, edge->target, edge->weight);
	newnode->nextnode = NULL;

	return newnode;
}

void EnQueue(Queue* queue, Node* newnode)
{
	bool flag = true;

	if (queue->front == NULL)
		queue->front = newnode;
	else
	{
		Node* temp = queue->front;
		Node* pre = NULL;
		while (temp != NULL)
		{
			if (queue->front->edge->weight > newnode->edge->weight)
			{
				newnode->nextnode = queue->front;
				queue->front = newnode;
				flag = false;
				break;
			}
			else if (temp->edge->weight > newnode->edge->weight)
			{
				newnode->nextnode = temp;
				pre->nextnode = newnode;
				flag = false;
				break;
			}
			else
				pre = temp;

			if (temp->nextnode == NULL)
				break;
			else
				temp = temp->nextnode;
		}

		if (flag)
			temp->nextnode = newnode;
	}
}

Node* DeQueue(Queue* queue)
{
	Node* temp = queue->front;
	queue->front = queue->front->nextnode;

	return temp;
}

void PrintQueue(Queue* queue)
{
	printf("printQueue\n");
	Node* temp = queue->front;
	while (temp != NULL)
	{
		printf("%c->%c[%d] ", temp->edge->from->data, temp->edge->target->data, temp->edge->weight);
		temp = temp->nextnode;
	}
	printf("\n");
}

void Prim(Graph* graph, Graph* prim, Vertex* startvertex)
{
	Vertex* vertex = startvertex;
	Edge* edge = NULL;
	Queue* queue = CreateQueue();

	AddVertex(prim, CreateVertex(startvertex->data));

	while (prim->index < graph->index)
	{
		edge = vertex->edgelist;
		while (edge != NULL)
		{
			if (edge->target->visited == -1)
				EnQueue(queue, CreateNode(CreateEdge(edge->from, edge->target, edge->weight))); //여기서 node->edge의 vertex(from, target)는 graph의 vertex
			edge = edge->nextedge;
		}

		Node* node = NULL;
		while (1)
		{
			node = DeQueue(queue);
			if (node->edge->target->visited == -1)
			{
				if (!SearchEdge(prim, node->edge->from->data, node->edge->target->data))
					break;
			}
			else
				free(node);
		}

		Vertex* primfrom = SearchVertex(prim, node->edge->from->data);
		Vertex* primtarget = SearchVertex(prim, node->edge->target->data);

		if (primtarget == NULL)
		{
			primtarget = CreateVertex(node->edge->target->data);
			AddVertex(prim, primtarget);
		}

		AddEdge(primfrom, primtarget, node->edge->weight);
		AddEdge(primtarget, primfrom, node->edge->weight);

		node->edge->target->visited = 1;
		vertex = node->edge->target;

		PrintQueue(queue);
		printf("prim\n");
		PrintGraph(prim);
	}
}

int main()
{
	Graph* graph = CreateGraph();
	Graph* prim = CreateGraph();

	Vertex* v1 = CreateVertex('a');
	Vertex* v2 = CreateVertex('b');
	Vertex* v3 = CreateVertex('c');
	Vertex* v4 = CreateVertex('d');
	Vertex* v5 = CreateVertex('e');
	Vertex* v6 = CreateVertex('f');
	Vertex* v7 = CreateVertex('g');

	AddVertex(graph, v1);
	AddVertex(graph, v2);
	AddVertex(graph, v3);
	AddVertex(graph, v4);
	AddVertex(graph, v5);
	AddVertex(graph, v6);
	AddVertex(graph, v7);

	AddEdge(v1, v2, 7);
	AddEdge(v1, v4, 5);
	AddEdge(v2, v1, 7);
	AddEdge(v2, v3, 8);
	AddEdge(v2, v4, 9);
	AddEdge(v2, v5, 7);
	AddEdge(v3, v2, 8);
	AddEdge(v3, v5, 5);
	AddEdge(v4, v1, 5);
	AddEdge(v4, v2, 9);
	AddEdge(v4, v5, 15);
	AddEdge(v4, v6, 6);
	AddEdge(v5, v2, 7);
	AddEdge(v5, v3, 5);
	AddEdge(v5, v4, 15);
	AddEdge(v5, v6, 8);
	AddEdge(v5, v7, 9);
	AddEdge(v6, v4, 6);
	AddEdge(v6, v5, 8);
	AddEdge(v6, v7, 11);
	AddEdge(v7, v5, 9);
	AddEdge(v7, v6, 11);

	PrintGraph(graph);

	Prim(graph, prim, v1);

	DestroyGraph(graph);

	return 0;
}