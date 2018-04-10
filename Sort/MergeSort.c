#include <stdio.h>

#define SIZE 10

void Merge(int *data, int left, int mid, int right)
{
	int i = left;
	int j = mid + 1;
	int k = left;

	int temp[SIZE];

	while (i <= mid && j <= right)
	{
		if (data[i] < data[j])
		{
			temp[k] = data[i];
			i++;
		}
		else
		{
			temp[k] = data[j];
			j++;
		}
		k++;
	}

	if (i > mid)
	{
		for (int m = j; m <= right; m++)
		{
			temp[k] = data[m];
			k++;
		}
	}
	else
	{
		for (int m = i; m <= mid; m++)
		{
			temp[k] = data[m];
			k++;
		}
	}

	for (int m = left; m <= right; m++)
		data[m] = temp[m];
}

void MergeSort(int *data, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;

		MergeSort(data, left, mid); //왼쪽 블록 분할
		MergeSort(data, mid + 1, right); //오른쪽 블록 분할
		Merge(data, left, +mid, right);
	}
}

int main()
{
	int data[10] = { 10,3,8,2,30,9,6,1,7,15 };

	for (int i = 0; i<SIZE; i++)
	{
		printf("%d ", data[i]);
	}
	printf("\n");

	MergeSort(data, 0, SIZE - 1);

	for (int i = 0; i<SIZE; i++)
	{
		printf("%d ", data[i]);
	}
	printf("\n");
	return 0;
}