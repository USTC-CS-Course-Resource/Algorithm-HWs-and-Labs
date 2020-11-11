#include <iostream>

using namespace std;

constexpr int MAX_N = 10000000;

template<class T>
int select(T* array, int start, int end, int kth_min) {
	if (start == end) return array[start];
	// partition
	T pivot = array[end];
	int i = start - 1;
	for (int j = start; j < end; j++) {
		if (array[j] <= pivot) {
			++i;
			swap<int>(array[i], array[j]);
		}
	}
	swap<int>(array[i + 1], array[end]);

	// recurse
	int pivot_index = i + 1;
	if (pivot_index + 1 == kth_min) return pivot;
	else if (pivot_index + 1 > kth_min) {
		return select(array, start, pivot_index - 1, kth_min);
	}
	else {
		return select(array, pivot_index + 1, end, kth_min);
	}

}

int main()
{
	int n, k;
	scanf("%d %d", &n, &k);
	int *numbers = new int[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", numbers + i);
	}
	printf("%d\n", select(numbers, 0, n - 1, k));
}
