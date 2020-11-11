#include <iostream>
#include <map>

using namespace std;

typedef pair<int, int> KV;

int main()
{
	map<int, int> kvmap;
	while (true) {
		char op[32];
		scanf("%s", op);
		int id, a;
		if (op[0] == 'I') {
			scanf("%d %d", &id, &a);
			kvmap.insert(KV(a, id));
		}
		else if (op[0] == 'F') {
			scanf("%d", &a);
			bool done = false;
			map<int, int>::iterator it = kvmap.find(a);
			//if (it == kvmap.end()) cout << "-1" << endl;
			//if (it == kvmap.end()) cout << -1 << endl;
			if (it == kvmap.end()) printf("-1\n");
			else cout << it->second << endl;
		}
		else if (op[0] == 'E') {
			break;
		}
	}
}
