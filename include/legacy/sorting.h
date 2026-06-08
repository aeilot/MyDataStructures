//
// Created by Chenluo Deng on 6/8/26.
//

#ifndef MY_STL_SORTING_H
#define MY_STL_SORTING_H

#include <vector>

class Sorting {
public:
	static void insertion(std::vector<int>& arr) {
		for (int i = 1; i < arr.size(); i++) {
			int tmp = arr[i];

			int j = i - 1;
			// Stability
			for (; j >= 0 && arr[j] > tmp; j--) {
				arr[j + 1] = arr[j];
			}

			// arr[j] <= tmp
			// arr[j] = arr[j + 1]
			arr[j + 1] = tmp;
		}
	}

	static void selection(std::vector<int>& arr) {
		int n = arr.size();

		for (int i = 0; i < n - 1; i++) {
			int rec = i;

			for (int j = i + 1; j < n; j++) {
				if (arr[j] < arr[rec]) {
					rec = j;
				}
			}

			std::swap(arr[i], arr[rec]);
		}
	}

	static void bubble(std::vector<int>& arr) {
		int n = arr.size();
		bool flag = true;

		while (flag) {
			flag = false;
			for (int i = 0; i<n-1; i++) {
				int j = i+1;
				if (arr[i] > arr[j]) {
					std::swap(arr[i], arr[j]);
					flag = true;
				}
			}
		}
	}
};

#endif //MY_STL_SORTING_H
