#include <iostream>

using namespace std;

class Node {
public:
	int data;
	Node* nextnode;
};

class Stack {
public:
	Node* stack;
	Stack();
	~Stack();

	void Push(int data);
	void Pop();
	void PrintStack();
};

Stack::Stack() {
	stack = NULL;
}
Stack::~Stack() {}

void Stack::Push(int data)
{
	Node* newnode = new Node();
	newnode->data = data;
	newnode->nextnode = NULL;

	if (stack == NULL) //스택이 없는 경우
		stack = newnode;
	else //스택이 있는 경우
	{
		Node* temp = stack;
		while (temp->nextnode != NULL)
			temp = temp->nextnode;
		temp->nextnode = newnode;
	}	
}

void Stack::Pop()
{
	if (stack == NULL) //스택이 없을 경우
	{
		cout << "Stack is Empty" << endl;
		return;
	}
	else if (stack->nextnode == NULL) //헤드만 있을 경우
	{
		delete(stack);
		stack = NULL;
	}
	else //일반적인 경우
	{
		Node* temp = stack;
		while (temp->nextnode->nextnode != NULL)
			temp = temp->nextnode;
		delete(temp->nextnode);
		temp->nextnode = NULL;
	}
}

void Stack::PrintStack()
{
	Node* temp = stack;

	if (stack == NULL)
		cout << "Stack is Empty" << endl;
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
	Stack s;

	while (1)
	{
		cout << "1. push 2.pop 3.show : ";
		cin >> select;

		if (1 == select)
		{
			int data;
			cout << "input data : ";
			cin >> data;
			s.Push(data);
		}
		else if (2 == select)
			s.Pop();
		else if (3 == select)
			s.PrintStack();
		else
			cout << "Unknown Comman" << endl;
	}

	return 0;
}