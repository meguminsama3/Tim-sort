#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>

using namespace std;

// Source: https://www.geeksforgeeks.org/merge-sort/
// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(vector<int>& arr, int left,
           int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Source: https://www.geeksforgeeks.org/insertion-sort-algorithm/
/* Function to sort array using insertion sort */
void insertionSort(vector<int> & arr, int left, int right)
{
    for (int i = left + 1; i < right + 1; ++i) {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
/**
 * Generate a random vector
 * @param size size of the vector
 * @return a random vector
 */
vector<int> RandomVector(int size)
{
    // Source: https://en.cppreference.com/w/cpp/numeric/random/random_device
    random_device rd;
    vector<int> vec {};
    std::uniform_int_distribution<int> dist(0, 9999);
    for (auto i = 0; i < size; i++)
    {
        vec.push_back(dist(rd));
    }
    return vec;
}

void TimSort(vector<int> & arr, int left, int right, int size)
{
    if (left >= right)
        return;

    int vecSize = right - left + 1;
    if (vecSize <= size)
    {
        insertionSort(arr, left, right);
        return;
    }

    int mid = left + (right - left) / 2;
    TimSort(arr, left, mid, size);
    TimSort(arr, mid + 1, right, size);
    merge(arr, left, mid, right);
}

double GetTime(vector<int> vec, int k)
{
    std::clock_t  start_time = std::clock();
    TimSort(vec, 0, vec.size() - 1, k);
    std::clock_t  tot_time = std::clock() - start_time;
    double time = ((double) tot_time) / (double) CLOCKS_PER_SEC;
    return time;
}

double GetAverageTime(int size, int k)
{
    double timeTotal = 0;

    int count = 100;
    for (auto i = 0; i < count; i++)
    {
        vector<int> vec = RandomVector(size);
        timeTotal += GetTime(vec, k);
    }

    double time = timeTotal / count;

    return time;
}

void WriteToFile(string filename, int size, int inc)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Can't open file" << endl;
    }

    file << "time, k\n";

    for (auto k = 0; k < size; k+=inc)
    {
        double time = GetAverageTime(500, k);
        file << time << ", " << k << '\n';
    }
    file.close();
}

int main()
{
    string filename = "sortingTimes1.csv";
    WriteToFile(filename, 500, 20);

    string filename2 = "sortingTimes2.csv";
    WriteToFile(filename2, 1000, 40);

    string filename3 = "sortingTimes3.csv";
    WriteToFile(filename3, 1500, 80);

    string filename4 = "sortingTimes4.csv";
    WriteToFile(filename4, 2000, 160);

    return 0;
}
