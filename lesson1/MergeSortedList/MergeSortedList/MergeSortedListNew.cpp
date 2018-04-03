// MergeSortedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include "omp.h"
#include <math.h>
#include <time.h>
#include <iostream>
using namespace std;


int main()
{
	//const int n = 40000000;
	const int n = 400;  //For this small data, it might work for paralization.

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
	return 0;
}
