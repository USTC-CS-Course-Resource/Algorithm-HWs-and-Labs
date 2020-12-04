#include <iostream>
#include <vector>

using namespace std;

int n;

typedef struct Point {
    int x;
    int y;
    int depth;
    vector<Point*> children;

} Point;

int compare(Point *p1, Point *p2) {
    if (p1->x <= p2->x && p1->y <= p2->y) return -1;
    else if (p1->x >= p2->x && p1->y >= p2->y) return 1;
    else return 0;
}

int set_depth(Point& point) {
    if (point.children.size() == 0) point.depth = 1;
    for (auto&& child: point.children) {
        if (child == &point) continue;
        if (child->depth == -1) {
            set_depth(*child);
        }
        if (child->depth + 1 > point.depth) {
            point.depth = child->depth + 1;
        }
    }
    return point.depth;
}

int main() {
    scanf("%d", &n);
    vector<Point> points = vector<Point>(n);
    for (auto&& point: points) {
        scanf("%d %d", &point.x, &point.y);
        point.depth = -1;
    }

    // build a DAG
    for (auto&& point: points) {
        for (auto&& child: points) {
            if (compare(&child, &point) == 1) {
                point.children.push_back(&child);
            }
        }
    }
    // find the deepest
    int max_depth = -1;
    for (auto&& point: points) {
        max_depth = max(set_depth(point), max_depth);
    }
    
    printf("%d\n", max_depth);
}
