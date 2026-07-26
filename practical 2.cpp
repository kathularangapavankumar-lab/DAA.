#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

// Linear Search Implementation
int linear_search(const vector<int>& data, int target) {
    for (size_t pos = 0; pos < data.size(); ++pos) {
        if (data[pos] == target) {
            return static_cast<int>(pos);
        }
    }
    return -1;
}

// Binary Search Implementation
int binary_search(const vector<int>& data, int target) {
    int left = 0;
    int right = static_cast<int>(data.size()) - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (data[middle] == target) {
            return middle;
        } else if (data[middle] < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
}

int main() {
    const int size = 100000;
    vector<int> numbers(size);

    // Fill array with sorted values
    for (int i = 0; i < size; ++i) {
        numbers[i] = i + 1;
    }

    int search_value;
    cout << "Enter the number to find: ";
    cin >> search_value;

    // Linear Search Timing
    auto start_time = high_resolution_clock::now();
    int result = linear_search(numbers, search_value);
    auto end_time = high_resolution_clock::now();

    cout << "\n--- Linear Search ---\n";
    if (result != -1)
        cout << "Found at index: " << result << endl;
    else
        cout << "Not found in array.\n";

    cout << "Execution Time: "
         << duration_cast<microseconds>(end_time - start_time).count()
         << " microseconds\n";

    // Binary Search Timing
    start_time = high_resolution_clock::now();
    result = binary_search(numbers, search_value);
    end_time = high_resolution_clock::now();

    cout << "\n--- Binary Search ---\n";
    if (result != -1)
        cout << "Found at index: " << result << endl;
    else
        cout << "Not found in array.\n";

    cout << "Execution Time: "
         << duration_cast<microseconds>(end_time - start_time).count()
         << " microseconds\n";

    return 0;
}
