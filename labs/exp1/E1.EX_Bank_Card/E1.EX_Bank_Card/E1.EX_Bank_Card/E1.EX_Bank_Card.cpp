#include <iostream>

using namespace std;

int get_max(const int* array, const int size) {
	int m_max = array[0];
	for (int i = 1; i < size; i++) {
		if (array[i] > m_max) m_max = array[i];
	}
	return m_max;
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	int* money_window = new int[k];
	int m_max = 0;
	for (int i = 0; i < k; i++) {
		scanf("%d", money_window + i);
		if (money_window[i] > m_max) m_max = money_window[i];
	}
	printf("%d ", m_max);
	size_t cur = 0;
	for (int i = k; i < n; i++, cur = (cur + 1) % k) {
		int tmp;
		scanf("%d", &tmp);
		int last = money_window[cur];
		money_window[cur] = tmp;
		if (tmp > m_max) {
			m_max = tmp;
		}
		else if (last == m_max) {
			if (last < tmp) m_max = tmp;
			else m_max = get_max(money_window, k);
			
		}
		printf("%d ", m_max);
	}
	printf("\n");
}
