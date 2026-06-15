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

	static void quick(std::vector<int>& arr) {
		if (arr.empty()) return;
		quick_sort(arr, 0, arr.size() - 1);
	}

	static void merge(std::vector<int>& arr) {
		if (arr.empty()) return;
		merge_sort(arr, 0, arr.size() - 1);
	}

private:
	static void quick_sort(std::vector<int>& arr, int left, int right) {
		int l = left, r = right;
		if (r<=l) return;
		while (l<r) {
			while (arr[r] >= arr[left] && r>l) r--;
			while (arr[l] <= arr[left] && l<r) l++;
			if (l<r) std::swap(arr[r], arr[l]);
		}
		std::swap(arr[left], arr[r]);
		quick_sort(arr, left, l-1);
		quick_sort(arr, l+1, right);
	}

	static void merge_sort(std::vector<int>& arr, int left, int right) {
		if (left >= right) return;
		int mid = left + ((right - left) >> 1);
		merge_sort(arr, left, mid);
		merge_sort(arr, mid+1, right);
		std::vector<int> tmp(right - left + 1);
		int i = left;
		int j = mid + 1;
		int k = 0;
		while (i <= mid && j <= right) {
			if (arr[i] > arr[j]) {
				tmp[k++] = arr[j++];
			} else {
				tmp[k++] = arr[i++];
			}
		}
		while (j <= right) tmp[k++] = arr[j++];
		while (i <= mid) tmp[k++] = arr[i++];
		for (int m = left; m <= right; m++) {
			arr[m] = tmp[m - left];
		}
	}
};

#endif //MY_STL_SORTING_H
