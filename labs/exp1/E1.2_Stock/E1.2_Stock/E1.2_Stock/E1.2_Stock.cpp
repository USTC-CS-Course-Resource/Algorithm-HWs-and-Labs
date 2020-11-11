#include <iostream>
#include <sstream>

using namespace std;

long long counter = 0;
int* tmp_array = new int[1000000];

void merge_sort(int* array, int start, int end) {
	if (start >= end) return;
	int middle = (start + end) / 2;
	merge_sort(array, start, middle);
	merge_sort(array, middle + 1, end);

	// merge
	int i = start, j = middle + 1;
	int k = start;
	while (i <= middle && j <= end) {
		if (array[i] <= array[j]) tmp_array[k++] = array[i++];
		else {
			counter += middle - i + 1;
			tmp_array[k++] = array[j++];
		}
	}
	while (i <= middle) tmp_array[k++] = array[i++];
	while (j <= end) tmp_array[k++] = array[j++];
	for (int i = start; i <= end; i++) {
		array[i] = tmp_array[i];
	}
}

int main() {
	int n;
	scanf("%d", &n);
	int* A = new int[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", A + i);
	}
	merge_sort(A, 0, n - 1);
	printf("%lld\n", counter % 10000019);
}
