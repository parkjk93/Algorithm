#include <stdio.h>
#define SIZE 100

void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(int *data)
{
	for (int i=0 ; i<SIZE-1 ; i++)
	{
		for (int j=0 ; j<SIZE-1-i ; j++)
		{
			if (data[j] > data[j + 1])
				Swap(&data[j], &data[j + 1]);
		}
	}
}

int main()
{
	int data[SIZE];
	for (int i=0 ; i<SIZE ; i++)
		data[i] = SIZE - i;

	BubbleSort(data);

	for (int i = 0; i < SIZE; i++)
		printf("%d ", data[i]);

    return 0;
}

