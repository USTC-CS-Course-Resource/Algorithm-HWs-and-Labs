#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n, r;
    scanf("%d %d", &n, &r);

    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }

    // sort(x.begin(), x.end(), less<int>());
    sort(x.begin(), x.end(), [](const int &x, const int &y){ return x < y; });

    int count = 0;
    int first_x = x[0];
    int i = 1;
    while (i < n) {
        while (x[i] - first_x <= r && i < n) i++;
        count++;
        int middle_x = x[i-1];
        if (i >= n) {
            break;
        }
        while (x[i] - middle_x <= r && i < n) i++;
        first_x = x[i];
    }

    printf("%d\n", count);
    
}