#include <concepts>
#include <iostream>
#include <memory>

using std::make_shared;
using std::shared_ptr;

template <class T>
concept sharePtr =
    requires {
      requires std::same_as<shared_ptr<typename T::element_type>, T>;
    };
template <class T, class U> struct xx1 {
  constexpr static bool val = false;
};
template <class T> struct xx1<T, typename T::element_type> {
  using tp = typename T::element_type;
  constexpr static bool val = std::is_same_v<shared_ptr<tp>, T>;
};
void func1() {
  std::shared_ptr<int> p = make_shared<int>(10);
  int *p1 = p.get();
  constexpr bool f = sharePtr<decltype(p)>;
  constexpr bool f1 = sharePtr<decltype(p1)>;
  std::cout << std::boolalpha;
  std::cout << f << '\n';
  std::cout << f1;
}
template <class T>  constexpr bool xx2 = xx1<T, void>::val;

void func2() {
  // std::shared_ptr<int> p = make_shared<int>(10);
  // int *p1 = p.get();
  // constexpr bool f = xx1<decltype(p)>::val;
  // constexpr bool f1 = xx1<decltype(p1)>::val;
  // std::cout << std::boolalpha;
  // std::cout << f << '\n';
  // std::cout << f1;
}
int main(int argc, char *argv[]) {
  func1();
  return 0;
}