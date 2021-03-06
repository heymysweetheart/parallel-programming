// ConsoleApplication1.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "omp.h"
#include <math.h>
#include <time.h>
#include <iostream>

using namespace std;
//int a[n];
//double b[n];

int main()
{
	const int n = 100000000;
	double* a;
	a = (double *)malloc(n * sizeof(double));
	clock_t t;
	
	int number;

	for (int i = 0; i < n; i++) {
		a[i] = i + 1;
	}

	cout << "Please input the thread number...";
	cin >> number;

	t = clock();
	omp_set_num_threads(number);
	#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		double d = log10(a[i]);
	}

	printf("Elapsed Time : %d\n", clock() - t);
	free(a);
    return 0;
}

