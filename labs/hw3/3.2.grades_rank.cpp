#include <iostream>

using namespace std;

constexpr int MAX_id = 2500000;
constexpr int MAX_GRADE = 100;

class Student {
public:
    int math;
    int english;
    int sum;
    int id;

    Student() {};

    bool operator>= (const Student &s) {
        if (this->sum > s.sum) return true;
        else if (this->sum == s.sum) {
            if (this->math > s.math) return true;
            else if (this->math == s.math) {
                if (this->id >= s.id) return true;
            }
        }
        return false;
    }
};

void quick_sort(Student **array, int start, int end) {
    // partition
    if (start >= end) return;
    Student pivot = *array[end];
    int i = start - 1;
    for (int j = start; j < end; j++) {
        if (*array[j] >= pivot) {
            i++;
            swap<Student*>(array[i], array[j]);
        }
    }
    i++; // now i refers to pivot element
    swap<Student*>(array[i], array[end]);
    
    // recurse
    quick_sort(array, start, i-1);
    quick_sort(array, i+1, end);
}

int main() {
    int n;
    scanf("%d", &n);
    Student **students = new Student*[n];
    for (int i = 0; i < n; i++) {
        students[i] = new Student();
        scanf("%d %hhd %hhd", &students[i]->id, &students[i]->math, &students[i]->english);
        students[i]->sum = students[i]->math + students[i]->english;
    }
    quick_sort(students, 0, n-1);
    for (int i = 0; i < n; i++) printf("%d ", students[i]->id);
}