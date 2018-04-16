#include <iostream>

using namespace std;

#define SIZE 8

void MakeTree(int* data, int* tree)
{
	for (int i=1 ; i<SIZE+1 ; i++)
	{
		int index = i;
		while (index <= SIZE)
		{
			tree[index] += data[i];
			index += (data[index] & -data[index]);
		}
	}
}

int Sum(int* tree, int* data, int index)
{
	int sum = 0;
	while (0 < index)
	{
		sum += tree[index];
		index -= (data[index] & -data[index]);
	}

	return sum;
}

int main()
{
	int data[SIZE + 1] = { 0, };
	int tree[SIZE + 1] = { 0, };

	cout << "input " << SIZE << " data : ";
	for (int i = 1; i < SIZE+1; i++)
		cin >> data[i];

	MakeTree(data, tree);
	
	for (int i = 1; i < SIZE + 1; i++)
		cout << tree[i] << " ";
	cout << endl;

	int start, end;
	while (1)
	{
		cout << "합을 구하고 싶은 구간의 시작과 끝을 입력하세요(1~" << SIZE << ") : ";
		cin >> start >> end;

		cout << Sum(tree, data, end) - Sum(tree,data,start-1) << endl;
	}

	return 0;
}