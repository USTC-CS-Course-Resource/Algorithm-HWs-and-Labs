#include <iostream>

using namespace std;

constexpr int MAX_N = 1000;

template<class T>
class Number {
public:
    T value;
    int count;
    
    Number() {};
    Number(T value, int count) : value(value), count(count) {};
    bool operator<= (const Number& n) {
        if (this->count > n.count) {
            return true;
        }
        else if (this->count == n.count && this->value <= n.value) {
            return true;
        }
        return false;
    }
};

template<class T>
void quick_sort(T *array, int start, int end) {
    // partition
    if (start >= end) return;
    T pivot = array[end];
    int i = start - 1;
    for (int j = start; j < end; j++) {
        if (array[j] <= pivot) {
            i++;
            swap<T>(array[i], array[j]);
        }
    }
    i++; // now i refers to pivot element
    swap<T>(array[i], array[end]);
    
    // recurse
    quick_sort(array, start, i-1);
    quick_sort(array, i+1, end);
}

template void quick_sort<int>(int *array, int start, int end);
template void quick_sort<Number<int>>(Number<int> *array, int start, int end);

int main() {
    int n;
    cin >> n;
    int *raw_data = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> raw_data[i];
    }
    // sort first
    quick_sort<int>(raw_data, 0, n-1);

    // count numbers
    Number<int> *numbers = new Number<int>[MAX_N];
    int cur = 0;
    int count = 1;
    int last = raw_data[0];
    for (int i = 1; i < n; i++) {
        if (raw_data[i] != last) {
            numbers[cur].value = last;
            numbers[cur].count = count;
            cur++;
            last = raw_data[i];
            count = 1;
        }
        else count++;
    }
    if (count > 0) {
        numbers[cur].value = last;
        numbers[cur].count = count;
    }

    quick_sort(numbers, 0, cur);

    for (int i = 0; i < cur+1; i++) cout << numbers[i].value << ' ' << numbers[i].count << endl;
}
