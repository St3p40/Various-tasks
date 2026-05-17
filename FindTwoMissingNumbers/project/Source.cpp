#include "C:\Users\User\source\repos\Project21\Project21\Header.h"

int main() {
	srand(1);
	int K = 20;
	int randGap = abs(rand()) % (K-3);
	int* arr = new int[K - 2];
	for (int k = 0; k < K - 2; k++) {
		arr[k] = k + 1 + ((k >= randGap) ? 2 : 0);
	}
	for (long i = 0; i < K - 2; i++) {
		int coord1 = i;
		int coord2 = abs(rand()) % (K-2);
		swap(&arr[coord1], &arr[coord2]);
	}
	for (int k = 0; k < K - 2; k++) {
		cout << arr[k] << " ";
	}
	cout << endl;
	int r[2];
	LLN_by_selection(arr, K, r);
	cout << "Result is " << r[0] << " " << r[1] << endl;
	LLN_by_sort(arr, K, r);
	cout << "Result is " << r[0] << " " << r[1] << endl;
	LLN_by_sum(arr, K, r);
	cout << "Result is " << r[0] << " " << r[1] << endl;
	LLN_by_throwing(arr, K, r);
	cout << "Result is " << r[0] << " " << r[1] << endl;
}