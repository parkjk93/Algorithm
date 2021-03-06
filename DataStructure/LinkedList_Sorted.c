#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE {
	int data;
	_NODE* nextnode;
}Node;

Node* head = NULL;

Node* CreateNode(int data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->nextnode = NULL;

	return newnode;
}

void InsertNode(int data)
{
	Node* newnode = CreateNode(data);

	if (head == NULL) //1.헤드가 업는 경우
		head = newnode;
	else //2.헤드가 있는 경우
	{
		Node* temp = head;
		Node* pre = NULL;
		bool flag = true;

		if (head->data > data)	//1)헤드를 바꿔야 하는 경우
		{
			newnode->nextnode = head;
			head = newnode;
		}
		else
		{
			while (temp->data <= data)
			{
				pre = temp;
				temp = temp->nextnode;
				if (temp == NULL)
				{
					flag = false;
					break;
				}					
			}

			if (flag == true) //2)중간에 삽입하는 경우
			{
				newnode->nextnode = pre->nextnode;
				pre->nextnode = newnode;
			}
			else //3)마지막에 삽입하는 경우
				pre->nextnode = newnode;
		}
	}
}

void DeleteNode(int data)
{
	bool flag = false;
	Node* temp = head;
	Node* pre = NULL;

	while (temp != NULL)
	{
		if (temp->data == data)
		{
			flag = true;

			if (temp == head) //헤드를 삭제하는 경우
				head = head->nextnode;
			else if (temp->nextnode == NULL) //마지막노드를 삭제하는 경우
				pre->nextnode = NULL;
			else //중간노드를 삭제하는 경우
				pre->nextnode = temp->nextnode;
			free(temp);

			break;
		}
		pre = temp;
		temp = temp->nextnode;
	}

	if (flag == true)
		printf("%d 데이터 삭제.\n", data);
	else
		printf("데이터가 없습니다.\n");
}

void SearchNode(int data)
{
	int length = 0;
	bool flag = false;
	Node* temp = head;
	while (temp != NULL)
	{
		if (temp->data == data)
		{
			flag = true;
			break;
		}
		length++;
		temp = temp->nextnode;
	}

	if (flag == true)
		printf("%d 번째 데이터입니다.\n",length);
	else
		printf("데이터가 없습니다.\n");
}

void ShowNode()
{
	Node* temp = head;
	while (temp->nextnode != NULL)
	{
		printf("%d -> ", temp->data);
		temp = temp->nextnode;
	}
	printf("%d\n", temp->data);
}

int main()
{
	int num;
	int data;

	while (1)
	{
		printf("1.insert 2.delete 3.search 4.show : ");
		scanf_s("%d", &num);
		if (1 == num)
		{
			printf("input number : ");
			scanf_s("%d", &data);
			InsertNode(data);
		}
		else if (2 == num)
		{
			printf("delete number : ");
			scanf_s("%d", &data);
			DeleteNode(data);
		}
		else if (3 == num)
		{
			printf("search number : ");
			scanf_s("%d", &data);
			SearchNode(data);
		}
		else if (4 == num)
			ShowNode();
		else
			printf("unknown command ! \n");
	}

    return 0;
}

