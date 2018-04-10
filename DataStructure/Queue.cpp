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

	if (front == NULL) //큐가 없는 경우
	{
		front = newnode;
		rear = newnode;
	}
	else //큐가 있는 경우
	{
		rear->nextnode = newnode;
		rear = newnode;
	}
}

void Queue::Dequeue()
{
	if (front == NULL) //큐가 없을 경우
	{
		cout << "Queue is Empty" << endl;
		return;
	}
	else if (front->nextnode == NULL) //front만 있을 경우
	{
		delete(front);
		front = NULL;
		rear = NULL;
	}
	else //일반적인 경우
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