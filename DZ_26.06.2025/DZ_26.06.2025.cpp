#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Custom Array class
class Array {
private:
    int* data;
    size_t size;

public:
    Array(size_t n = 0) : size(n) {
        data = (size > 0) ? new int[size]() : nullptr;
    }

    Array(const Array& other) : size(other.size) {
        data = (size > 0) ? new int[size]() : nullptr;
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    Array(const string& str) {
        vector<int> nums;
        string temp = "";
        for (char ch : str) {
            if (ch == ' ') {
                if (!temp.empty()) {
                    nums.push_back(stoi(temp));
                    temp.clear();
                }
            }
            else {
                temp += ch;
            }
        }
        if (!temp.empty()) nums.push_back(stoi(temp));

        size = nums.size();
        data = (size > 0) ? new int[size] : nullptr;
        for (size_t i = 0; i < size; i++) {
            data[i] = nums[i];
        }
    }

    ~Array() {
        delete[] data;
    }

    Array& operator=(const Array& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        data = (size > 0) ? new int[size] : nullptr;
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }

    int& operator[](size_t index) { return data[index]; }
    const int& operator[](size_t index) const { return data[index]; }

    size_t getSize() const { return size; }

    friend ostream& operator<<(ostream& os, const Array& arr) {
        for (size_t i = 0; i < arr.size; i++) {
            os << arr.data[i] << " ";
        }
        return os;
    }
};

// Priority Queue class
class PriorityQueue {
private:
    Array data;
    size_t count;
    size_t capacity;

    void ensureCapacity(size_t minCapacity) {
        if (capacity >= minCapacity) return;
        size_t newCapacity = max(minCapacity, capacity * 2 + 1);
        Array newData(newCapacity);
        for (size_t i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        data = newData;
        capacity = newCapacity;
    }

public:
    PriorityQueue() : data(0), count(0), capacity(0) {}

    void push(int value) {
        ensureCapacity(count + 1);

        size_t i = count;
        while (i > 0 && data[i - 1] < value) {
            data[i] = data[i - 1]; // shift elements right
            i--;
        }
        data[i] = value;
        count++;
    }

    int pop() {
        if (count == 0) throw runtime_error("Queue is empty!");
        int top = data[0];
        for (size_t i = 1; i < count; i++) {
            data[i - 1] = data[i]; // shift elements left
        }
        count--;
        return top;
    }

    bool empty() const { return count == 0; }

    void print() const {
        for (size_t i = 0; i < count; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

// Test
int main() {
    PriorityQueue pq;

    pq.push(10);
    pq.push(5);
    pq.push(20);
    pq.push(15);

    cout << "Priority Queue: ";
    pq.print();

    cout << "Popping elements: ";
    while (!pq.empty()) {
        cout << pq.pop() << " ";
    }
    cout << endl;

    return 0;
}
