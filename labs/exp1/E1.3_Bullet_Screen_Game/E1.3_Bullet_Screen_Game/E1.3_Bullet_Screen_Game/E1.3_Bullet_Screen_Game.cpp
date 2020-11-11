// 即求最近两点间距

#include <iostream>

using namespace std;

void quick_sort(int* array, int start, int end) {
	if (start >= end) return;

	// partition
	int pivot = array[end];
	int i = start - 1;
	for (int j = start; j < end; j++) {
		if (array[j] <= pivot) {
			i = i + 1;
			swap(array[i], array[j]);
		}
	}
	swap(array[++i], array[end]);

	// recurse
	quick_sort(array, start, i - 1);
	quick_sort(array, i + 1, end);
}

int main() {
	int n;
	scanf("%d", &n);
	int* enemies = new int[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", enemies + i);
	}
	quick_sort(enemies, 0, n-1);
	int max = 0;
	for (int i = 0; i < n - 1; i++) {
		if (enemies[i + 1] - enemies[i] > max) {
			max = enemies[i + 1] - enemies[i];
		}
	}

	printf("%d\n", max);
}
