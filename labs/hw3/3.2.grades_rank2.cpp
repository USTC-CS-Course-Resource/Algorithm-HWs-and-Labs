#include <iostream>

using namespace std;

typedef struct Student {
    uint32_t id;
    uint8_t english;
    uint8_t math;
    uint16_t sum;
} Student;

void quick_sort(Student *array, int start, int end) {
    // partition
    if (start >= end) return;
    uint64_t pivot = *(uint64_t*)&(array[end].id);
    int i = start - 1;
    for (int j = start; j < end; j++) {
        if (*(uint64_t*)&(array[j].id) >= pivot) {
            i++;
            swap<Student>(array[i], array[j]);
        }
    }
    i++; // now i refers to pivot element
    swap<Student>(array[i], array[end]);
    
    // recurse
    quick_sort(array, start, i-1);
    quick_sort(array, i+1, end);
}

int main() {
    int n;
    scanf("%d", &n);
    Student *students = new Student[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %hhd %hhd", &students[i].id, &students[i].math, &students[i].english);
        students[i].sum = students[i].math + students[i].english;
    }

    quick_sort(students, 0, n-1);
    for (int i = 0; i < n; i++) printf("%d ", students[i].id);
}