// MergeSortedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include "omp.h"
#include <math.h>
#include <time.h>
#include <iostream>
using namespace std;


void f1(void);
void f2(void);
void f3(void);
int main()
{
	f3();
    return 0;
}

//This solutio will create wrong result, because it's impossbile to parallel the merge for loop because the different
//threads share the same x, y, and change the value at the same time.
//In bellow two occissations parallel might work:
// 1. the n is small as 400,
// 2. the computing logic take really small time, and no other tasks like print a value.
//All in all, it's not safe to try to parallel the logic with shared data(like x, y in this f1()).

void f1(void) {
	//const int n = 40000000;
	const int n = 40;  //For this small data, it might work for paralization.

	int *a, *b, *c;
	a = (int *)malloc(n * sizeof(int));
	b = (int *)malloc(n * sizeof(int));
	c = (int *)malloc(2 * n * sizeof(int));

	for (int i = 0; i < n; i++) {
		a[i] = 2 * i;
		b[i] = 2 * i + 1;
	}



	int number;

	cout << "Please input the thread number...";
	cin >> number;

	int x = 0, y = 0;
	clock_t t;
	t = clock();
	omp_set_num_threads(number);
#pragma omp parallel for
	for (int i = 0; i < 2 * n; i++) {

		/*printf("I loop: %d\n", 5);*/ //This line takes time, it may cause the parallelization not work.

		if (x < n && y < n) {
			if (a[x] <= b[y]) {
				c[i] = a[x++];
			}
			else {
				c[i] = b[y++];
			}
		}
		else if (x < n) {
			c[i] = a[x++];
		}
		else {
			c[i] = b[y++];
		}
	}


	for (int i = 0; i < 2 * n; i++) {
		printf("%d\n", c[i]);
	}
	printf("Time used: %d", clock() - t);
	free(a);
	free(b);
	free(c);
}

void f2(void) {
	const int n = 100000;
	//const int n = 4000;  //For this small data, it might work for paralization.

	int *a, *b, *c;
	a = (int *)malloc(n * sizeof(int));
	b = (int *)malloc(n * sizeof(int));
	c = (int *)malloc(2 * n * sizeof(int));

	for (int i = 0; i < n; i++) {
		a[i] = 2 * i;
		b[i] = 2 * i + 1;
	}


	int number;

	cout << "Please input the thread number...";
	cin >> number;

	int x = 0, y = 0;
	clock_t t;
	t = clock();
	omp_set_num_threads(number);
	#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		int j = 0;
		while (a[i] >= b[j] && j < n) {
			j++;
		}
		
		c[i + j] = a[i];
	}

	omp_set_num_threads(number);
	#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		int j = 0;
		while (b[i] >= a[j] && j < n) {
			j++;
		}

		c[i + j] = b[i];
	}
	/*for (int i = 0; i < 2 * n; i++) {
		printf("Number %d is %d\n", i, c[i]);
	}*/
	printf("Time used: %d", clock() - t);
	free(a);
	free(b);
	free(c);
}

/*function to compare two integers*/ /* returns -1 if p < q, 0 if p = q, 1 if p > q */
int lt(const void *p, const void *q) { 
	return (*(int *)p - *(int *)q); 
}

void f3() {
//#define n 10000000 /*length of list*/ 
//#define bsize 1000000  /*size of buckets*/ 
//#define m 100  /*number of buckets*/ 

#define n 1000 /*length of list*/ 
#define bsize 100  /*size of buckets*/ 
#define m 10  /*number of buckets*/ 
#define range RAND_MAX + 1
	int list[n];  /*unsorted list of integers*/ 
	int final[n]; /*sorted list of integers*/ 
	int bucket[m][bsize]; /*buckets*/ 
	int count[m]; /*number of items stored in bucket*/ 

	//Init the list;
	for (int i = 0; i < n; i++) {
		list[i] = rand();
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < bsize; j++) {
			bucket[i][j] = 0;
		}
	}

	for (int i = 0; i < m; i++) {
		count[i] = 0;
	}


	//Distribute the number
	for (int i = 0; i < n; i++) {
		int bnum = (int)((float)m * ((float)(list[i] / range))) - 1;
		int cnum = count[bnum];
		bucket[bnum][cnum] = list[i];
		count[bnum]++;
	}

	int nn = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < bsize; j++) {
			if (bucket[i][j] != 0) {
				nn++;
			}
		}
	}

	printf("Count is : %d", nn);

	free(bucket);
	free(list);
	free(final);
	free(count);




	//Quick sort all the buckets
	/**for (int i = 0; i < m; i++) {
		qsort(bucket[i], count[i], sizeof(int), lt);
	}*/

	//Merge all the data from the buckets


}
