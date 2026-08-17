#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <utility>

using namespace std;
using namespace std::chrono;

// Iterative Max-Heapify to eliminate recursion overhead
void siftDownMax(vector<int>& data, int heapSize, int rootIdx) {
    while (true) {
        int target = rootIdx;
        int left = (rootIdx << 1) + 1;
        int right = left + 1;

        if (left < heapSize && data[left] > data[target])
            target = left;
        if (right < heapSize && data[right] > data[target])
            target = right;

        if (target == rootIdx) break;

        swap(data[rootIdx], data[target]);
        rootIdx = target;
    }
}

// In-place Max-Heap Sort (yields ascending order)
void runMaxHeapSort(vector<int>& data) {
    int totalElements = data.size();

    for (int i = (totalElements / 2) - 1; i >= 0; --i) {
        siftDownMax(data, totalElements, i);
    }

    for (int boundary = totalElements - 1; boundary > 0; --boundary) {
        swap(data[0], data[boundary]);
        siftDownMax(data, boundary, 0);
    }
}

// Iterative Min-Heapify
void siftDownMin(vector<int>& data, int heapSize, int rootIdx) {
    while (true) {
        int target = rootIdx;
        int left = (rootIdx << 1) + 1;
        int right = left + 1;

        if (left < heapSize && data[left] < data[target])
            target = left;
        if (right < heapSize && data[right] < data[target])
            target = right;

        if (target == rootIdx) break;

        swap(data[rootIdx], data[target]);
        rootIdx = target;
    }
}

// Min-Heap Sort (yields descending order, inverted to ascending)
void runMinHeapSort(vector<int>& data) {
    int totalElements = data.size();

    for (int i = (totalElements / 2) - 1; i >= 0; --i) {
        siftDownMin(data, totalElements, i);
    }

    for (int boundary = totalElements - 1; boundary > 0; --boundary) {
        swap(data[0], data[boundary]);
        siftDownMin(data, boundary, 0);
    }

    // In-place reversal for standard ascending output
    int left = 0, right = totalElements - 1;
    while (left < right) {
        swap(data[left++], data[right--]);
    }
}

int main() {
    int elementCount;
    cout << "Enter number of elements: ";
    if (!(cin >> elementCount) || elementCount <= 0) {
        cout << "Invalid array size.\n";
        return 1;
    }

    // Modern C++ Mersenne Twister random engine
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(1, 100000);

    vector<int> dataset(elementCount);
    for (int i = 0; i < elementCount; ++i) {
        dataset[i] = dist(rng);
    }

    vector<int> maxHeapDataset = dataset;
    vector<int> minHeapDataset = dataset;

    // --- Benchmark Max Heap ---
    auto t1_max = high_resolution_clock::now();
    runMaxHeapSort(maxHeapDataset);
    auto t2_max = high_resolution_clock::now();

    // --- Benchmark Min Heap ---
    auto t1_min = high_resolution_clock::now();
    runMinHeapSort(minHeapDataset);
    auto t2_min = high_resolution_clock::now();

    // --- Display Benchmarks ---
    auto durationMax_ns = duration_cast<nanoseconds>(t2_max - t1_max).count();
    auto durationMax_us = duration_cast<microseconds>(t2_max - t1_max).count();

    auto durationMin_ns = duration_cast<nanoseconds>(t2_min - t1_min).count();
    auto durationMin_us = duration_cast<microseconds>(t2_min - t1_min).count();

    cout << "\n---------------- MAX HEAP SORT ----------------\n";
    cout << "Time (ns) : " << durationMax_ns << " ns\n";
    cout << "Time (us) : " << durationMax_us << " us\n";

    cout << "\n---------------- MIN HEAP SORT ----------------\n";
    cout << "Time (ns) : " << durationMin_ns << " ns\n";
    cout << "Time (us) : " << durationMin_us << " us\n";

    return 0;
}
