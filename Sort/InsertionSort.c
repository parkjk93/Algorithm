#include <stdio.h>
#define SIZE 100

void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void InsertionSort(int *data)
{
	for (int i=1 ; i<SIZE ; i++)
	{
		for (int j=i ; j>0 ; j--)
		{
			if (data[j] < data[j - 1])
				Swap(&data[j], &data[j - 1]);
		}
	}
}

int main()
{
	int data[SIZE];
	for (int i = 0; i<SIZE; i++)
		data[i] = SIZE - i;

	InsertionSort(data);

	for (int i = 0; i < SIZE; i++)
		printf("%d ", data[i]);

    return 0;
}

