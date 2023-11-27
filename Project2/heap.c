/********************************************
	Class: Data Structure and Algorithms
	Project 2: Heap and Sort

	heap.c

	Name: Ahn Jin mo
	StudentID: 2017160111

**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "heap.h"

/*
	@Function name: createHeap
	@Parameters: none
	@Returns: h
	@Descriptions: createHeap function creates HEAP h.
	@Error cases: none
*/
HEAP createHeap()
{
	HEAP h = (HEAP)malloc(sizeof(heap));
	h->size = 0;
	h->heapData = (int*)malloc(sizeof(int)*100);
	return h;
}

/*
	@Function name: buildHeap
	@Parameters: h, array, arraySize
	@Returns: none
	@Descriptions: buildHeap function is implementd by using makeHeap function. 
	@Error cases: If heap doesn't exist, function prints error message.
*/

void makeHeap(int arr[], int arrSize) // makeHeap makes input arr[] to have max-heap property
{
	int left, right, largest, temp;

	for (int i=(floor(arrSize/2)-1); i >= 0; i--)
	{
	    left = (2*i+1); // left child 
	    right = (2*i+2); // right child
	    temp = arr[i]; // parent node's value

	    if (left < arrSize && arr[left] > arr[i]) // left child > parent
	    {
            largest = left;
	    }
	    else
	    {
		    largest = i;
	    }

	    if (right < arrSize && arr[right] > arr[largest]) // right child > parent or left child
	    {
		    largest = right;
	    }

        if (left >= arrSize)
	    {
		    return;
	    }

	    if (largest != i)
	    {
		    arr[i] = arr[largest]; 
		    arr[largest] = temp; // swap parent and largest
		    makeHeap(arr, arrSize); // recursive function
	    }
	}
}

void buildHeap(HEAP h, int* array, int arraySize)
{
	if (h == NULL) // error condition
	{
		printf("Error: No heap exists.\n");
	}

	else
	{
		makeHeap(array, arraySize); // make array to have max-heap property

		for (int j=0; j < arraySize; j++)
		{
			h->heapData[j] = array[j]; // assign array to h->heapData
			h->size ++;
		}

	}
}

/*
	@Function name: deleteHeap
	@Parameters: h
	@Returns: none
	@Descriptions: deleteHeap function deletes HEAP h using dequeueHeap function.
	@Error cases: If heap doesn't exist or heap size is zero, funtion prints error message.
*/
void deleteHeap(HEAP h)
{
	if (h == NULL || h->size == 0) // error condition
	{
		printf("Error: No heap exists.\n");
	}

	else
	{
		for (int i = 0; i < h->size; i++) // repeat dequeueHeap function
		{
			dequeueHeap(h);
		}
		printf("Successfully deleted.\n");
	}

}


/*
	@Function name: findDepth
	@Parameters: h
	@Returns: d
	@Descriptions: findDepth function returns heap's depth. Heap's depth is calculated using log2(arraySize).
	@Error cases: If heap doesn't exist or heap size is zero, function prints error message.
*/
int findDepth(HEAP h)
{
    if (h == NULL) // error condition
	{
		printf("Error: No heap exists.\n");
		exit(0);
	}

	else
	{
		int number, d;
	    number = h->size;

	    if (number == 0) // error condition
	    {
		    printf("Error: No heap exists.\n");
			exit(0);
	    }
	    d = (floor(log2(number)))+1; // calculate depth
		return d;
	}
}


/*
	@Function name: insertNode
	@Parameters: h, value
	@Returns: none
	@Descriptions: insertNode function inserts new value in HEAP h. After inserting new node, function implements heap property using makeHeap function.
	@Error cases: If heap doesn't exist or heap size is zero, function prints error message.
*/

void insertNode(HEAP h, int value)
{
	if (h == NULL || h->size == 0) // error condition
	{
		printf("Error: No heap exists.\n");
	}

	else
	{
		h->size += 1;
		h->heapData[h->size-1] = value; // insert value in h->heapData
		makeHeap(h->heapData, h->size); // make new h->heapData to maintain max-heap property
	}
}


/*
	@Function name: dequeueHeap
	@Parameters: h
	@Returns: output(== h->heapData[0])
	@Descriptions: dequeueHeap function exchanges first value and last value in HEAP h, and returns first value in originial HEAP h.
	               After returning, function implements heap property using makeHeap function.
	@Error cases: If heap doesn't exist or heap size is zero, function prints error message.
*/
int dequeueHeap(HEAP h)
{
	if (h == NULL) // error condition
	{
		printf("Error: No heap exists.\n");
		exit(0);
	}

	else
	{
		int output;
	    output = h->heapData[0];

		if (h->size != 0)
	    {
			if (h->size != 1)
			{
				h->heapData[0] = h->heapData[h->size-1]; // change root node's value to last node's value
	            h->heapData[h->size-1] = 0; // remove last node
	            h->size -= 1;
                makeHeap(h->heapData, h->size); // make new h->heapData to maintain max-heap property
			    return output; // return the largest value
			}

			else // If h->size == 1, there is no heap after dequeueHeap. So make h free. 
			{
				h->heapData[0] = 0;
				h->size -= 1;
				free(h); // h is freed
				return output;
			}
	    }

		else // error condition.
		{
			printf("Error: No heap exists.\n");
			exit(0);
		}
	}
}


/*
	@Function name: heapSort
	@Parameters: h, heapsort, count
	@Returns: none
	@Descriptions: heapSort function is implemented by using make_min_Heap function.
	@Error cases: none
*/
void make_min_Heap(int arr[], int arrSize) // This function implements array having min-heap property
{
	int left, right, smallest, temp;
	
	for (int i=(floor(arrSize/2)-1); i >= 0; i--)
	{
	    left = (2*i+1); // left child
	    right = (2*i+2); // right child
	    temp = arr[i]; // parent node's value

	    if (left < arrSize && arr[left] < arr[i]) // left child < parent
	    {
            smallest = left; 
	    }
	    else
	    {
		    smallest = i;
	    }

	    if (right < arrSize && arr[right] < arr[smallest]) // right child < left child or parent
	    {
		    smallest = right;
	    }

        if (left >= arrSize)
	    {
		    return;
	    }

	    if (smallest != i) // parent isn't smallest value
	    {
		    arr[i] = arr[smallest]; 
		    arr[smallest] = temp; // swap parent and smallest value
		    make_min_Heap(arr, arrSize); // recursive function
	    }
	}
}

void heapSort(HEAP h, int *heapsort, int count)
{
	make_min_Heap(heapsort, count); // make heapsort to have min-heap property
	int j = count;

	for (int i=0; i < j; i++)
	{
		h->heapData[i] = heapsort[0]; // assign (i+1)th small value in heapsort to heapData[i]
		h->size++;
		heapsort[0] = heapsort[count-1]; //dequeueHeap 
		count -= 1;
		make_min_Heap(heapsort, count); // push root down
	}	
}


/*
	@Function name: swap
	@Parameters: n1, n2
	@Returns: none
	@Descriptions: Function swaps n1 and n2.
	@Error cases: none
*/
void swap(int*n1, int*n2)
{
	int temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}


/*
	@Function name: printHeap
	@Parameters: h
	@Returns: none
	@Descriptions: Function prints HEAP h.
	@Error cases: none
*/
void printHeap(HEAP h)
{
	int* d;
	int size;			//buffer size

	d = h->heapData;
	size = h->size;

	int level = findDepth(h);

	printf("Depth = %d, Size = %d\n",level,size);

	int l,w;
	int btw = 4*(int)pow(2,level);
	for(l = 0; l<level; l++)
	{
		printf("%*c",btw/2+1,' ');
		for(w = (int)pow(2,l)-1; w < (int)pow(2,l+1)-1; w++)
		{
			if(w>=size) break;
			int p = *(d+w);
			if(p==0) printf("*");
			else printf("%d",p);
			printf("%*c",btw-1,' ');
		}
		btw/=2;
		printf("\n");
	}
}
