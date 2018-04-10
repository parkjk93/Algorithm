#include <stdio.h>
#define SIZE 100

void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void SelectionSort(int* data)
{
	for (int i=0 ; i<SIZE-1 ; i++)
	{
		int index = i;
		for (int j=i ; j<SIZE ; j++)
		{
			if (data[j] < data[index])
				index = j;
		}
		Swap(&data[i], &data[index]);
	}
}

int main()
{
	int data[SIZE];
	for (int i = 0; i<SIZE; i++)
		data[i] = SIZE - i;

	SelectionSort(data);

	for (int i = 0; i < SIZE; i++)
		printf("%d ", data[i]);

    return 0;
}

