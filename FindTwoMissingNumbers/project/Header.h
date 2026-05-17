#pragma once
#include <iostream>
#include <algorithm> 
using namespace std;

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void LLN_by_sum(int arr[], int size, int* result) {
	long sum = ((size * (1 + size)) / 2);
	for (int k = 0; k < size - 2; k++) {
		sum -= arr[k];
	}
	long r1 = sum / 2;
	result[0] = r1;
	result[1] = r1 + 1;
}

void LLN_by_sort(int arr[], int size, int* result) {
	result[0] = 0; result[1] = 0;
	std:sort(&arr[0],&arr[size - 2]);
	for (int i = 0; i < size - 3; i++) {
		if (arr[i + 1] - arr[i] > 1) {
				result[0] = arr[i] + 1;
				result[1] = arr[i] + 2;
		}
	}
}

void LLN_by_selection(int arr[], int size, int* result) {
	result[0] = 0; result[1] = 0;
	int checked = 0;
	for (int i = 1; i < size + 1; i++) {
		bool isNumMiss = 1;
		for (int j = 0; j < size - 2 - checked; j++) {
			if (i == arr[j]) {
				isNumMiss = 0;
				swap(arr[j], arr[size - 3 - checked]);
				checked++;
				break;
			}
		}
		if (isNumMiss) {
			if (result[0]) {
				result[1] = i;
				break;
			}
			else
				result[0] = i;
		}
	}
}

void LLN_by_throwing(int arr[], int size, int* result) {
	result[0] = 0; result[1] = 0;
	bool* a = new bool[size];
	memset(a, 0, size);
	for (int j = 0; j < size - 2; j++) {
		a[arr[j] - 1] = 1;
	}
	for (int i = 0; i < size; i++) {
		if (!a[i]) {
			if (result[0]) {
				result[1] = i + 1;
				break;
			}
			else
				result[0] = i + 1;
		}
	}
	delete[] a;
}