/* Assignment 3: Question 2
 * Fares Issa
 * issaf - 0925274
 * November 5th, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Compares the nodes of the tree using down heap algorithm
 * taught in class to turn it into a true heap.*/
void downHeapAlg(int* heap, int start);

/*Driver program*/
int main()
{
	FILE * file;
	char source[201];
	char* input;
	int i;
	int j;
	int k;
	int data[20][10];
	int temp;
	int key[21];
	i = 0;
	j = 0;
	k = 0;
	temp = 0;

	file = fopen("f.dat", "r");
	if (file == NULL) //safety net if file is null
	{
		printf("Unable to open file. Exiting.");
		exit(0);
	}
	else
	{
		j = 0;
		/*Program loops until file ends*/
		while((fgets(source, 201, file) != NULL))
		{
			i = 0;
			input = strtok(source, " "); //delimiter for first key
			data[j][i] = atoi(input);
			for (i = 1; i <10; i++)
			{
				input = strtok(NULL, " "); //delimiter for remaining keys/values
				data[j][i] = atoi(input);
			}
			j++;
		}
	}
	fclose(file);

	i = 1;
	/*creating a second array based on keys in order to downheap.*/
	for (i = 1; i < 21; i++)
	{
		key[i] = data[(i-1)][0] + data[(i-1)][1] + data[(i-1)][2];
	}

	i = 10;
	/*Downheap the list until sorted.*/
	while (i != 10)
	{
		downHeapAlg(key, i);
		i--;
	}
	i = 1;

	/*Print the 20x10 array. Downheaped*/
	for (i = 1; i < 21; i++)
	{
		k = 0;
		while (k <20)
		{
			if (key[i] == (data[k][0] + data[k][1] + data[k][2]))
			{
				temp = k;
			}
			k++;
		}
		j = 0;
		while (j < 10)
		{
			printf("%d ", data[temp][j]);
			j++;
		}
		printf("\n");
	}

	return 0;
}

void downHeapAlg(int *heap, int s)
{
	int parent;
	int left;
	int right;
	int temp;
	left = 0;
	right = 0;
	temp = 0;
	parent = heap[s];

	if (s != 10)
	{
		left = heap[(s*2)];
		right = heap[((s*2)+1)];
	}
	else
	{
		left = heap[(s*2)];
		right = 500;
	}

	if (((left < right) && (right < parent)) || ((left < parent) && (parent < right)))
	{
		temp = parent;
		heap[s] = left;
		heap[(s*2)] = temp;

		if (s < 6)
		{
			temp = s*2;
			downHeapAlg(heap,temp); //recursively call
		}
	}
	else if (((right < left) && (left < parent)) || ((right < parent) && (parent < left)))
	{
		temp = parent;
		heap[s] = right;
		heap[((s*2)+1)] = temp;

		if (s < 6)
		{
			temp = s*2+1;
			downHeapAlg(heap,temp); //recursively call
		}
	}
}
