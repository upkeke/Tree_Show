
#include <compare>
#include <config.h>
#include <container.hpp>
#include <ctime>
#include <gtest/gtest.h>
#include <queue>
#include <stack>
using std::clock_t;
using std::strong_ordering;

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
  bool operator==(const Obj &other) const {
    return a == other.a && *p == *other.p;
  }
  strong_ordering operator<=>(const Obj &other) const {
    if (a < other.a) {
      return strong_ordering::less;
    } else if (a == other.a) {
      if (*p < *other.p)
        return strong_ordering::less;
      else if (*p == *other.p)
        return strong_ordering::equal;
    } else
      return strong_ordering::greater;
  }
  ~Obj() { delete p; }
  int a;
  int *p;
};
// struct Obj {
//   int a{};
//   Obj(int a):a(a){}
//   auto operator<=>(const Obj &other) const = default;
// };
class deque_test : public testing::Test {
protected:
  // 初始化数据
  void SetUp() override {
    start_time_ = std::clock(); // 开始时间
    std::vector<int> arr{1, 2, 3};
  }
  void TearDown() override {
    clock_t end_time = std::clock(); // 结束时间
  }

  _SPC queue<Obj> mq1;
  std::queue<Obj> sq1;
  _SPC stack<Obj> ms1;
  std::stack<Obj> ss1;

  clock_t start_time_;
};

TEST_F(deque_test, push_left_value) {
  auto t1 = std::clock();
  for (int i = 0; i < 100000; ++i) {
    Obj obj{i, i + 1};
    mq1.push(obj);
  }
  auto t2 = std::clock();
  for (int i = 0; i < 100000; ++i) {
    Obj obj{i, i + 1};
    sq1.push(obj);
  }
  auto t3 = std::clock();
  int d1 = t2 - t1;
  int d2 = t3 - t2;
  printf("push(Obj &) >> %d\n", d1 - d2);

  bool f = true;
  while (!sq1.empty()) {
    if (mq1.front() != sq1.front() || mq1.back() != sq1.back()) {
      f = false;
      break;
    }
    mq1.pop();
    sq1.pop();
  }
  if (!mq1.empty())
    f = false;
  EXPECT_TRUE(f);
}
TEST_F(deque_test, push_right_value) {
  auto t1 = std::clock();
  for (int i = 0; i < 100000; ++i) {
    Obj obj{i, i + 1};
    mq1.push(std::move(obj));
  }
  auto t2 = std::clock();
  for (int i = 0; i < 100000; ++i) {
    Obj obj{i, i + 1};
    sq1.push(std::move(obj));
  }
  auto t3 = std::clock();
  int d1 = t2 - t1;
  int d2 = t3 - t2;
  printf("push(Obj &&) >> %d\n", d1 - d2);

  bool f = true;
  while (!sq1.empty()) {
    if (mq1.front() != sq1.front() || mq1.back() != sq1.back()) {
      f = false;
      break;
    }
    mq1.pop();
    sq1.pop();
  }
  if (!mq1.empty())
    f = false;
  EXPECT_TRUE(f);
}
TEST_F(deque_test, emplace) {
  auto t1 = std::clock();
  for (int i = 0; i < 100000; ++i) {
    mq1.emplace(i, i + 1);
  }
  auto t2 = std::clock();
  for (int i = 0; i < 100000; ++i) {
    sq1.emplace(i, i + 1);
  }
  auto t3 = std::clock();
  int d1 = t2 - t1;
  int d2 = t3 - t2;
  printf("push(Obj &&) >> %d\n", d1 - d2);

  bool f = true;
  while (!sq1.empty()) {
    if (mq1.front() != sq1.front() || mq1.back() != sq1.back()) {
      f = false;
      break;
    }
    mq1.pop();
    sq1.pop();
  }
  if (!mq1.empty())
    f = false;
  EXPECT_TRUE(f);
}
int main(int argc, char **argv) {
  //::testing::GTEST_FLAG(filter) = "x1.x1_1";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}