#include <iostream>

using namespace std;

class Heap {
public:
	int* values;

	Heap(size_t size) {

	}
};

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
		if (tmp > m_max || money_window[cur] < tmp) {
			money_window[cur] = tmp;
			m_max = tmp;
		}
		else if (money_window[cur] == m_max) {
			money_window[cur] = tmp;
			m_max = get_max(money_window, k);
		}
		printf("%d ", m_max);
	}
	printf("\n");
}
