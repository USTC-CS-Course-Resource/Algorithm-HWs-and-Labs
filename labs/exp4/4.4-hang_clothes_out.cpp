#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>

using namespace std;

class Cloth {
public:
    int x;
    int next_idx;
    int prev_idx;
    Cloth() {}
    Cloth(int x): x(x) {}
};

using ClothPair = pair<int, int>;



int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    vector<Cloth> clothes(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &clothes[i].x);
    }

    sort(clothes.begin(), clothes.end(), [](const Cloth &x, const Cloth &y){ return x.x < y.x; });

    auto cmp = [&](const ClothPair &x, const ClothPair &y) {
        return clothes[x.second].x - clothes[x.first].x > clothes[y.second].x - clothes[y.first].x;
    };
    priority_queue<ClothPair, vector<ClothPair>, decltype(cmp)> distances(cmp);
    

    for (int i = 0; i < n-1; i++) {
        clothes[i].next_idx = i + 1;
        clothes[i].prev_idx = i - 1;
        distances.push(ClothPair(i, i+1));
    }
    clothes[n-1].next_idx = -1;
    clothes[n-1].prev_idx = n-1;
    
    for (int i = 0; i < m; i++) {
        auto nearest = distances.top();
        distances.pop();
        while (true) {
            auto left = nearest.first;
            auto right = nearest.second;
            if (clothes[left].x == -1) {
                nearest = distances.top();
                distances.pop();
            }
            else if (clothes[right].x == -1) {
                nearest = distances.top();
                distances.pop();
            }
            else break;
        }
        auto left = nearest.first;
        auto right = nearest.second;

        auto to_remove = left;
        if (clothes[left].prev_idx != -1) {
            if (clothes[right].next_idx == -1) to_remove = left;
            else {
                // if left isn't begin and right isn't last
                auto leftleft = clothes[left].prev_idx;
                auto rightright = clothes[right].next_idx;
                if (clothes[right].x - clothes[leftleft].x < clothes[rightright].x - clothes[left].x) {
                    // remove right
                    to_remove = right;
                }
                else {
                    // remove left
                    to_remove = left;
                }
            }
        }
        else to_remove = right;


        distances.push(ClothPair(clothes[to_remove].prev_idx, clothes[to_remove].next_idx));

        clothes[clothes[to_remove].prev_idx].next_idx = clothes[to_remove].next_idx;
        clothes[clothes[to_remove].next_idx].prev_idx = clothes[to_remove].prev_idx;
        clothes[to_remove].x = -1;
    }

    auto nearest = distances.top();
    distances.pop();
    while (true) {
        auto left = nearest.first;
        auto right = nearest.second;
        if (clothes[left].x == -1) {
            nearest = distances.top();
            distances.pop();
        }
        else if (clothes[right].x == -1) {
            nearest = distances.top();
            distances.pop();
        }
        else break;
    }

    printf("%d\n", clothes[nearest.second].x - clothes[nearest.first].x);

}

// #include <iostream>
// #include <algorithm>
// #include <vector>
// #include <list>
// #include <queue>
// #include <unordered_set>

// using namespace std;

// class Cloth {
// public:
//     int x;
//     int next_idx;
//     int prev_idx;
//     Cloth(int x): x(x) {}
// };

// using It = list<int>::iterator;
// using RIt = list<int>::reverse_iterator;
// using ClothPair = pair<It, It>;

// int main() {
//     int n, m;
//     scanf("%d %d", &n, &m);

//     vector<int> clothes;

//     for (int i = 0; i < n; i++) {
//         int x;
//         scanf("%d", &x);
//         clothes.push_back(x);
//     }

//     sort(clothes.begin(), clothes.end(), [](const int &x, const int &y){ return x < y; });

//     list<int> clothes_list;
//     auto cmp = [](const ClothPair &x, const ClothPair &y) {
//         return *x.first - *x.first > *y.second - *y.first;
//     };
//     priority_queue<ClothPair, vector<ClothPair>, decltype(cmp)> distances(cmp);
//     set<It> remains;

//     clothes_list.push_back(clothes[0]);
//     for (int i = 1; i < n; i++) {
//         clothes_list.push_back(clothes[i]);
//         distances.push(ClothPair(prev(prev(clothes_list.end())), prev(clothes_list.end())));
//         remains.insert(prev(clothes_list.end()));
//     }
    
//     for (int i = 0; i < m; i++) {
//         auto nearest = distances.top();
//         distances.pop();
//         while (true) {
//             auto left = nearest.first;
//             auto right = nearest.second;
//             if (remains.find(left) == remains.end()) {
//                 nearest = distances.top();
//                 distances.pop();
//             }
//             else if (remains.find(right) == remains.end()) {
//                 nearest = distances.top();
//                 distances.pop();
//             }
//             else break;
//         }
//         auto left = nearest.first;
//         auto right = nearest.second;

//         auto to_remove = left;
//         if (left != clothes_list.begin()) {
//             // if left isn't begin
//             if (right == prev(clothes_list.end())) {
//                 // if right is the last
//                 to_remove = right;
//             }
//             else {
//                 // if left isn't begin and right isn't last
//                 auto leftleft = prev(left);
//                 auto rightright = next(right);
//                 if (*right - *leftleft < *rightright - *left) {
//                     to_remove = right;
//                 }
//                 else to_remove = left;
//             }
//         }
        
//         remains.erase(to_remove);
//         clothes_list.erase(to_remove);
//     }

//     auto nearest = distances.top();
//     distances.pop();
//     while (true) {
//         auto left = nearest.first;
//         auto right = nearest.second;
//         if (remains.find(left) == remains.end()) {
//             nearest = distances.top();
//             distances.pop();
//         }
//         else if (remains.find(right) == remains.end()) {
//             nearest = distances.top();
//             distances.pop();
//         }
//         else break;
//     }

//     printf("%d\n", *nearest.second - *nearest.first);

// }