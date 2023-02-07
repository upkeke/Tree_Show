
#include "BinaryTreeStr.hpp"
#include "get_test_data.h"
#include <compare>
#include <container.hpp>
#include <iostream>
#include <queue>
#include <stack>


using std::strong_ordering;

std::ostream &operator<<(std::ostream &out, const strong_ordering &obj) {
  if (obj == strong_ordering::less) {
    out << "strong_ordering::less";
  } else if (obj == strong_ordering::greater) {
    out << "strong_ordering::greater";
  } else {
    out << "strong_ordering::eque";
  }
  return out;
}
struct Obj {
  Obj(const int &a, const int &val_p) : a(a), p(new int(val_p)) {}
  Obj(const Obj &other) {
    a = other.a;
    p = new int(*other.p);
  }
  Obj(Obj &&other) {
    a = other.a;
    p = other.p;
    other.p = nullptr;
  }
  Obj &operator=(const Obj &) = delete;
  Obj &operator=(Obj &&) = delete;
  void set(int x, int y) {
    a = x;
    *p = y;
  }
  ~Obj() { delete p; }
  friend std::ostream &operator<<(std::ostream &out, const Obj &obj) {
    out << '(' << obj.a << "," << *obj.p << ')';
    return out;
  }
  bool operator==(const Obj &other) const {
    return a == other.a && *p == *other.p;
  }
  strong_ordering operator<=>(const Obj &other) const {
    if (a != other.a) {
      return a <=> other.a;
    } else {
      return *p <=> *other.p;
    }
  }
  int a;
  int *p;
};
template <class T>
  requires requires(T obj) { std::cout << obj; }
void comp(const T &a, const T &b) {
  static int index = 0;
  std::cout << typeid(T).name() << " index " << index << " start\n"
            << "a = " << a << ' ' << "b = " << b << '\n'
            << std::boolalpha;
  std::cout << "(a <=> b) >> " << (a <=> b) << '\n';
  std::cout << "(a < b) >> " << (a < b) << '\n';
  std::cout << "(a <= b) >> " << (a <= b) << '\n';
  std::cout << "(a == b) >> " << (a == b) << '\n';
  std::cout << "(a != b) >> " << (a != b) << '\n';
  std::cout << "(a > b) >> " << (a > b) << '\n';
  std::cout << "(a >= b) >> " << (a >= b) << '\n';

  std::cout << typeid(T).name() << " index " << index << " end\n";
  index++;
}
void func1() {
  Obj obj1{13, 15};
  Obj obj2{12, 12};
  comp(obj1, obj2);
  obj1.set(12, 12);
  comp(obj1, obj2);
}

#include <QDebug>
#include <vector>
struct xxk {
  int a;
};
void func2() {
  // ok
  auto f1 = [x = xxk{1}](int n) { return x.a + n; };
  std::cout << f1(12); // 13
}
void func3() {
  auto arr = get_vector<QString>(12);
  for (auto x : arr)
    qDebug() << x;
}
int main(int argc, char *argv[]) {
  func3();
  return 0;
}

// 定义了三路运算 在定义等于运算，
//  == 和!=运算调用 ==函数
// 其他的调用 三路运算，结果和== 合并
// 严格弱序 2个对象相等返回false