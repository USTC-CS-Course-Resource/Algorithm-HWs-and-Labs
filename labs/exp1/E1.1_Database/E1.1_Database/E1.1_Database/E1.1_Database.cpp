#include <iostream>
#include <list>
#include <vector>

using namespace std;

constexpr int TABLE_SIZE = 2 << 20;

typedef pair<int, int> KV;

int main()
{
	vector<list<KV>> table(TABLE_SIZE);
	char op[32];
	int id, a;
	while (true) {
	next:
		scanf("%s", op);
		if (op[0] == 'I') {
			scanf("%d %d", &id, &a);
			table[a % TABLE_SIZE].push_back(KV(id, a));
		}
		else if (op[0] == 'F') {
			scanf("%d", &a);
			bool done = false;
			for (auto &&kv : table[a % TABLE_SIZE]) {
				if (kv.second == a) {
					printf("%d\n", kv.first);
					goto next;
				}
			}
			printf("-1\n");
		}
		else {
			break;
		}
	}
}
