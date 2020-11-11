#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student {

    private:
    int id;
    string firstName;
    string lastName;

    public:
    int getId() { return id; }
    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }
    Student(int id, string fn, string ln): id(id), firstName(fn), lastName(ln) {}

};

class SearchingSorting {
    private:
    static int binarySearchHelper(vector<Student*> students, int key, int start, int end);
    static void mergeHalves(vector<Student*>&left, vector<Student*>& right, vector<Student*>& result);
    static void quickSortHelper(vector<Student*> &students, int left, int right);
    static int partition(vector<Student*> &values, int left, int right);

    public:
    static int linearSearch(vector<Student*> students, int key);
    static int binarySearch(vector<Student*> students, int key);

    static void selectionSort(vector<Student*> &students);
    static void insertionSort(vector<Student*> &students);
    static void mergeSort(vector<Student*> &students);
    static void quickSort(vector<Student*> &students);

};

int SearchingSorting::linearSearch(vector<Student*> students, int key) {
    for (int i=0; i<students.size(); i++) {
        if (students[i]->getId() == key) return i;
    }
    return -1;
}

int SearchingSorting::binarySearchHelper(vector<Student*> students, int key, int start, int end) {

    if (start > end) return -1;
    int mid = (start + end) / 2;
    if (students[mid]->getId() == key) {
        return mid;
    } else if (key < students[mid]->getId())  {
        return SearchingSorting::binarySearchHelper(students, key, start, mid-1);
    } else {
        return SearchingSorting::binarySearchHelper(students, key, mid+1, end);
    }

}

int SearchingSorting::binarySearch(vector<Student*> students, int key) {
    return SearchingSorting::binarySearchHelper(students, key, 0, students.size()-1);
}

void SearchingSorting::selectionSort(vector<Student*> &students) {

    for (int i = 0; i < students.size()-1; i++) {
        int min = i;
        for (int j = i+1; j < students.size(); j++) {
            if (students[j]->getId() < students[min]->getId()) {
                min = j;
            }
        }
        Student* temp = students[i];
        students[i] = students[min];
        students[min] = temp;

    }

}

void SearchingSorting::insertionSort(vector<Student*> &students) {

    for (int i = 1; i < students.size(); i++)
    {
        int j = i;
        Student* tmp = students[i];
        while (j > 0 && tmp->getId() < students[j - 1]->getId())
        {
            students[j] = students[j - 1];
            j--;
        }
        students[j] = tmp;
    }

}

void SearchingSorting::mergeSort(vector<Student*> & students) {
    if (students.size() <= 1) return;

    int mid = students.size() / 2;

    vector<Student*> leftHalf;
    for (size_t j = 0; j < mid;j++)
        leftHalf.push_back(students[j]);

    vector<Student*> rightHalf;
    for (size_t j = mid; j < (students.size()); j++)
        rightHalf.push_back(students[j]);

    mergeSort(leftHalf);
    mergeSort(rightHalf);
    mergeHalves(leftHalf, rightHalf, students);
}

void SearchingSorting::mergeHalves(vector<Student*>&left, vector<Student*>& right, vector<Student*>& result)
{
    int i = 0, j = 0, k = 0;

    while (j < left.size() && k < right.size()) 
    {
        if (left[j]->getId() < right[k]->getId()) {
            result[i] = left[j];
            j++;
        }
        else {
            result[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < left.size()) {
        result[i] = left[j];
        j++; i++;
    }
    while (k < right.size()) {
        result[i] = right[k];
        k++; i++;
    }
}

void SearchingSorting::quickSort(vector<Student*> & students) {
    quickSortHelper(students, 0, students.size()-1);
}


void SearchingSorting::quickSortHelper(vector<Student*> & students, int left, int right) {
    if(left < right) {
        int pivotIndex = partition(students, left, right);
        quickSortHelper(students, left, pivotIndex - 1);
        quickSortHelper(students, pivotIndex, right);
    }
}


int SearchingSorting::partition(vector<Student*> &students, int left, int right) {
    // Original code from: https://www.thepolyglotdeveloper.com/2019/04/sort-vector-integers-quicksort-algorithm-cpp/
    int pivotIndex = left + (right - left) / 2;
    int pivotId = students[pivotIndex]->getId();
    int i = left, j = right;
    while(i <= j) {
        while(students[i]->getId() < pivotId) {
            i++;
        }
        while(students[j]->getId() > pivotId) {
            j--;
        }
        if(i <= j) {
            Student* temp = students[i];
            students[i] = students[j];
            students[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}

bool isSorted(vector<Student*> students) {
    for (int i=1; i<students.size(); i++) {
        if (students[i]->getId() < students[i-1]->getId()) {
            return false;
        }
    }
    return true;
}

int main() {

    cout << "Hello World" << endl;

    vector<Student*> testStudents;
    testStudents.push_back(new Student(10, "Bienve", "Velez"));
    testStudents.push_back(new Student(21, "Amanda", "Vazquez"));
    testStudents.push_back(new Student(32, "Fernando", "Davis"));
    testStudents.push_back(new Student(43, "Alejandra", "Munoz"));
    testStudents.push_back(new Student(54, "Fatima", "Puig"));
    testStudents.push_back(new Student(65, "Joshua", "Cruz"));
    testStudents.push_back(new Student(76, "Rey", "Cotto"));

    cout << "Linear Search" << endl;
    cout << ((SearchingSorting::linearSearch(testStudents, 10) == 0) ? "Passed" : "Failed") << endl;
    cout << ((SearchingSorting::linearSearch(testStudents, 43) == 3) ? "Passed" : "Failed") << endl;
    cout << ((SearchingSorting::linearSearch(testStudents, 76) == 6) ? "Passed" : "Failed") << endl;
    cout << ((SearchingSorting::linearSearch(testStudents, 87) == -1) ? "Passed" : "Failed") << endl;

    cout << "Binary Search" << endl;
    cout << ((SearchingSorting::binarySearch(testStudents, 10) == 0) ? "Passed" : "Failed") << endl;
    cout << ((SearchingSorting::binarySearch(testStudents, 43) == 3) ? "Passed" : "Failed") << endl;
    cout << ((SearchingSorting::binarySearch(testStudents, 76) == 6) ? "Passed" : "Failed") << endl;
    cout << ((SearchingSorting::binarySearch(testStudents, 87) == -1) ? "Passed" : "Failed") << endl;

    vector<Student*> unsortedStudents;
    unsortedStudents.push_back(new Student(32, "Bienve", "Velez"));
    unsortedStudents.push_back(new Student(76, "Amanda", "Vazquez"));
    unsortedStudents.push_back(new Student(65, "Fernando", "Davis"));
    unsortedStudents.push_back(new Student(54, "Alejandra", "Munoz"));
    unsortedStudents.push_back(new Student(43, "Fatima", "Puig"));
    unsortedStudents.push_back(new Student(21, "Joshua", "Cruz"));
    unsortedStudents.push_back(new Student(10, "Rey", "Cotto"));

    cout << "Selection Sort" << endl;
    SearchingSorting::selectionSort(unsortedStudents);
    cout << (isSorted(unsortedStudents) ? "Passed" : "Failed") << endl;

    unsortedStudents.clear();
    unsortedStudents.push_back(new Student(32, "Bienve", "Velez"));
    unsortedStudents.push_back(new Student(76, "Amanda", "Vazquez"));
    unsortedStudents.push_back(new Student(65, "Fernando", "Davis"));
    unsortedStudents.push_back(new Student(54, "Alejandra", "Munoz"));
    unsortedStudents.push_back(new Student(43, "Fatima", "Puig"));
    unsortedStudents.push_back(new Student(21, "Joshua", "Cruz"));
    unsortedStudents.push_back(new Student(10, "Rey", "Cotto"));

    cout << "Insertion Sort" << endl;
    SearchingSorting::insertionSort(unsortedStudents);
    cout << (isSorted(unsortedStudents) ? "Passed" : "Failed") << endl;

    unsortedStudents.clear();
    unsortedStudents.push_back(new Student(32, "Bienve", "Velez"));
    unsortedStudents.push_back(new Student(76, "Amanda", "Vazquez"));
    unsortedStudents.push_back(new Student(65, "Fernando", "Davis"));
    unsortedStudents.push_back(new Student(54, "Alejandra", "Munoz"));
    unsortedStudents.push_back(new Student(43, "Fatima", "Puig"));
    unsortedStudents.push_back(new Student(21, "Joshua", "Cruz"));
    unsortedStudents.push_back(new Student(10, "Rey", "Cotto"));

    cout << "Merge Sort" << endl;
    SearchingSorting::mergeSort(unsortedStudents);
    cout << (isSorted(unsortedStudents) ? "Passed" : "Failed") << endl;

    unsortedStudents.clear();
    unsortedStudents.push_back(new Student(32, "Bienve", "Velez"));
    unsortedStudents.push_back(new Student(76, "Amanda", "Vazquez"));
    unsortedStudents.push_back(new Student(65, "Fernando", "Davis"));
    unsortedStudents.push_back(new Student(54, "Alejandra", "Munoz"));
    unsortedStudents.push_back(new Student(43, "Fatima", "Puig"));
    unsortedStudents.push_back(new Student(21, "Joshua", "Cruz"));
    unsortedStudents.push_back(new Student(10, "Rey", "Cotto"));

    cout << "Quick Sort" << endl;
    SearchingSorting::quickSort(unsortedStudents);
    cout << (isSorted(unsortedStudents) ? "Passed" : "Failed") << endl;
}




