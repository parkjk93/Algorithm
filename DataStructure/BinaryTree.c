#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	int data;
	_Node* left;
	_Node* right;
}Node;

typedef struct _Tree {
	_Node* root;
}Tree;

Node* CreateNode(int data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

void InsertTree(int data, Tree* tree)
{
	Node* newnode = CreateNode(data);
	Node* temp = tree->root;

	if (tree->root == NULL)
		tree->root = newnode;
	else
	{
		while (1)
		{
			if (data < temp->data)
			{
				if (temp->left == NULL)
				{
					temp->left = newnode;
					break;
				}
				else
					temp = temp->left;
			}
			else
			{
				if (temp->right == NULL)
				{
					temp->right = newnode;
					break;
				}
				else
					temp = temp->right;
			}
		}
	}
}

Node* SearchNode(Node* root, int data)
{
	Node* temp = root;
	if (root == NULL)
	{ 
		printf("tree is empty\n");
		return NULL;
	}		

	while (temp != NULL)
	{
		if (temp->data == data)
		{
			printf("Search success!\n");
			return temp;
		}
		else
		{
			if (data < temp->data)
				temp = temp->left;
			else
				temp = temp->right;
		}
	}

	printf("data is not in the tree\n");
	return NULL;
}

void PrintTree(Node* node)
{
	if (node == NULL)
		return;
	
	printf("%d ", node->data);

	PrintTree(node->left);
	PrintTree(node->right);
}

int main()
{
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	tree->root = NULL;
	int select = 0;
	int data = 0;

	while (1)
	{
		printf("1.insert 2.search 3.print : ");
		scanf_s("%d", &select);

		if (1 == select)
		{
			printf("input data : ");
			scanf_s("%d", &data);
			InsertTree(data, tree);
		}
		else if (2 == select)
		{
			printf("search data : ");
			scanf_s("%d", &data);
			SearchNode(tree->root, data);
		}
		else if (3 == select)
		{
			PrintTree(tree->root);
			printf("\n");
		}
		else
			printf("Unknown command\n");
	}

	return 0;
}