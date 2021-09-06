#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <deque>
#include <stdexcept>
#include <set>

using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
    if(released.empty()) {
      T* ptr = new T;
      dedicated.insert(ptr);
      return ptr;
    } else {
      T* ptr = released.front();
      dedicated.insert(ptr);
      released.pop_front();
      return ptr;
    }
  }

  T* TryAllocate() {
    if(released.empty()) {
      return nullptr;
    } else {
      T* ptr = released.front();
      dedicated.insert(ptr);
      released.pop_front();
      return ptr;
    }
  }

  void Deallocate(T* object) {
    if (dedicated.find(object) == dedicated.end()) { throw invalid_argument(""); }
    released.push_back(object);
    dedicated.erase(dedicated.find(object));
  }

  ~ObjectPool() {
    for (auto& item : released) { delete item; }
    for (auto& item : dedicated) { delete item; }
  }

private:
  // Добавьте сюда поля
  deque<T*> released;
  set<T*> dedicated;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
