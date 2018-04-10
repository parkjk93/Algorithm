#include <iostream>

using namespace std;

class Node {
public:
	int data;
	Node* nextnode;
};

class Queue {
public:
	Node* front;
	Node* rear;
	Queue();
	~Queue();

	void Enqueue(int data);
	void Dequeue();
	void PrintQueue();
};

Queue::Queue() {
	front = NULL;
	rear = NULL;
}
Queue::~Queue() {}

void Queue::Enqueue(int data)
{
	Node* newnode = new Node();
	newnode->data = data;
	newnode->nextnode = NULL;

	if (front == NULL) //ť�� ���� ���
	{
		front = newnode;
		rear = newnode;
	}
	else //ť�� �ִ� ���
	{
		rear->nextnode = newnode;
		rear = newnode;
	}
}

void Queue::Dequeue()
{
	if (front == NULL) //ť�� ���� ���
	{
		cout << "Queue is Empty" << endl;
		return;
	}
	else if (front->nextnode == NULL) //front�� ���� ���
	{
		delete(front);
		front = NULL;
		rear = NULL;
	}
	else //�Ϲ����� ���
	{
		Node* temp = front;
		front = front->nextnode;
		delete(temp);
	}
}

void Queue::PrintQueue()
{
	Node* temp = front;

	if (front == NULL)
		cout << "Queue is Empty" << endl;
	else
	{
		while (temp->nextnode != NULL)
		{
			cout << temp->data << " -> ";
			temp = temp->nextnode;
		}
		cout << temp->data << endl;
	}
}

int main()
{
	int select;
	Queue s;

	while (1)
	{
		cout << "1. Enqueue 2.Dequeue 3.show : ";
		cin >> select;

		if (1 == select)
		{
			int data;
			cout << "input data : ";
			cin >> data;
			s.Enqueue(data);
		}
		else if (2 == select)
			s.Dequeue();
		else if (3 == select)
			s.PrintQueue();
		else
			cout << "Unknown Comman" << endl;
	}

	return 0;
}