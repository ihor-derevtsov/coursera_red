#include <iostream>
#include <vector>
#include <stdexcept>
// #include "test_runner.h"

using namespace std;

template <typename T>
class Deque {
public:
    Deque(size_t num=0) {
        if (num!=0) { Resize(num); };
    }

    void Resize(size_t num) {
        vec1.resize(0);
        vec2.resize(num);
    }
    bool Empty() const {
        return (vec1.empty() && vec2.empty());
    }

    int Size() const {
        return (vec1.size() + vec2.size());
    }

    T& operator[](size_t index) {
        if (index < vec1.size()) { return vec1[vec1.size() - 1 - index]; }
        else { return vec2[index - vec1.size()]; }
    }

    const T& operator[](size_t index) const {
        if (index < vec1.size()) { return vec1[vec1.size() - 1 - index]; }
        else { return vec2[index - vec1.size()]; }
    }

    T& At(size_t index) {
        if (index >= Size()) { throw out_of_range("Bad index"); }
        if (index < vec1.size()) { return vec1[vec1.size() - 1 - index]; }
        else { return vec2[index - vec1.size()]; }
    }

    const T& At(size_t index) const {
        if (index >= Size()) { throw out_of_range("Bad index"); }
        if (index < vec1.size()) { return vec1[vec1.size() - 1 - index]; }
        else { return vec2[index - vec1.size()]; }
    }


    T& Front() { return vec1.empty() ? vec2.front() : vec1.back(); }
    const T& Front() const { return vec1.empty() ? vec2.front() : vec1.back(); }

    T& Back() { return vec2.empty() ? vec1.front() : vec2.back(); }
    const T& Back() const { return vec2.empty() ? vec1.front() : vec2.back(); }
    
    void PushFront(const T& value) {
        vec1.push_back(value);
    }

    void PushBack(const T& value) {
        vec2.push_back(value);
    }
private:
    vector<T> vec1;
    vector<T> vec2;

};



int main() {
    return 0;
}