#include <iostream>
#include <string>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    string sub, full;

    for (int i = 0; i < n; i++) {
        cin >> sub >> full;
        int counter = 0;
        int idx = -1;
        while (true) {
            idx = full.find(sub, idx + 1);
            if (idx == -1) break;
            counter++;
        }
        cout << counter << endl;
    }
}
