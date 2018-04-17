#include <stdio.h>
#include <string.h>
#include <math.h>

#define SIZE 7

void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void InsertHeap(int* heap, int data)
{
	int i = 0;
	bool flag = false;

	for (i=1 ; i<SIZE+1 ; i++)
	{
		if (heap[i] == -1)
		{
			heap[i] = data;
			flag = true;
			break;
		}
	}
	// i - 데이터 입력한 값이 들어가있다.
	if (flag == true) //삽입 성공
	{
		while (0 < i)
		{
			int parent = i / 2;
			if (heap[parent] > heap[i])
			{
				Swap(&heap[parent], &heap[i]);
				i = parent;
			}
			else
				break;
		}
	}
	else //데이터가 꽉찬거
		printf("Heap is full\n");
}

void SearchHeap(int *heap, int data)
{
	bool flag = false;
	for (int i=1 ; i<SIZE+1 ; i++)
	{
		if (heap[i] == data)
		{
			printf("find data\n");
			flag = true;
			break;
		}
	}

	if (flag == false)
		printf("data is not in the tree");
}

void DeleteHeap(int* heap) //최소값(루트) 삭제
{
	int i = 1;
	for (i=1 ; i<SIZE+1 ; i++)
	{
		if (heap[i] == -1)
		{
			i--;
			break;
		}
	}
	
	if (SIZE + 1 == i)
		i--;

	heap[1] = heap[i]; //힙의 마지막 노드를 최상위 노드로 올린다.
	heap[i] = -1;
	for (i=1 ; i<SIZE+1 ; i++) //힙이 어디까지 차있는지 판단한다.
	{
		if (heap[i] == -1)
		{
			i -= 1;
			break;
		}
	}

	int index = 1;
	while (index <= i/2) // i/2 트리의 잎노드 바로 위 노드까지
	{
		int left = index * 2;
		int right = index * 2 + 1;
		int min;

		if (heap[right] == -1)
		{
			min = left;
		}
		else if (heap[left] < heap[right])
			min = left;
		else
			min = right;

		if (heap[min] < heap[index])
		{
			Swap(&heap[min], &heap[index]);
			index = min;
		}
		else
			break;		
	}
}

void PrintHeap(int* heap)
{
	int n = 1;
	for (int i = 1; i < SIZE + 1; i++)
	{
		if (heap[i] == -1)
			break;

		printf("%d ", heap[i]);
		if (i == (1 << n) -1)
		{
			printf("\n");
			n++;
		}
	}
	printf("\n");
}

int main()
{
	int heap[SIZE+1];
	memset(heap, -1, sizeof(heap[0])*(SIZE+1)); //-1이 있으면 힙이 비어있는것
	
	int data;
	while (1)
	{
		int select;
		printf("1.insert 2.search 3.delete 4.show : ");
		scanf_s("%d", &select);

		if (1 == select)
		{
			printf("input data : ");
			scanf_s("%d", &data);
			InsertHeap(heap, data);
		}
		else if (2 == select)
		{
			printf("search data : ");
			scanf_s("%d", &data);
			SearchHeap(heap, data);
		}
		else if (3 == select)
			DeleteHeap(heap);
		else if (4 == select)
			PrintHeap(heap);
		else
			printf("Unknown Command\n");
	}

	return 0;
}