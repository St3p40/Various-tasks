#include <iostream>
#include <vector>
#include <utility>

void swap(int* a, int* b) {
	int* c = b;
	b = a;
	a = c;
}

void shakerSort(std::vector<std::pair<int, int>>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    bool swapped = true;

    while (swapped) {
        swapped = false;

        for (int i = left; i < right; ++i) {
            if (arr[i].first > arr[i + 1].first) {
                temp = arr[i + 1];
				arr[i + 1] = arr[i];
				arr[i] = temp;
                swapped = true;
            }
        }
        --right;


        if (!swapped) break;

        swapped = false;

        for (int i = right; i > left; --i) {
            if (arr[i - 1].first > arr[i].first) {
                std::swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        ++left;
    }
}

void printArray(const std::vector<std::pair<int, int>>& arr) {
    for (const auto& p : arr) {
        std::cout << "(" << p.first << ", " << p.second << ") ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<std::pair<int, int>> arr = {
        {5, 1}, {2, 2}, {9, 3}, {1, 4}, {7, 5}
    };

    std::cout << "Before: ";
    printArray(arr);

    shakerSort(arr);

    std::cout << "After: ";
    printArray(arr);

    return 0;
}
