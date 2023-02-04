

// #include <BinaryTree.hpp>
//  #include <QDebug>
//  #include <TreeHead.hpp>
//  #include <common_func.hpp>
//  #include <data_source.h>
#include <iostream>

#include <config.h>
#include <ctime>
#include <gtest/gtest.h>
#include <vector>
#include <queue>

// #include <format>
using std::clock_t;

class vector_test : public testing::Test {
protected:
  // 初始化数据
  void SetUp() override {
    start_time_ = std::clock(); // 开始时间
    std::vector<int> arr{1, 2, 3};

    // tsdata.size()
  }
  void TearDown() override {
    clock_t end_time = std::clock(); // 结束时间
    // std::cout<<std::asctime_r(std::localtime(&end_time)) <<'\n';
    // 如果开始时间和结束时间间隔小于5秒，则测试通过
    // EXPECT_TRUE(end_time - start_time_ <= 5) << "The test took too long.";
  }

  _SPC vector<int> marr1;
  std::vector<int> arr1;
  _SPC vector<int> marr2{1, 2, 3};
  std::vector<int> arr2{1, 2, 3};
  std::vector<int> arr{1, 2, 3};
  clock_t start_time_;
};
TEST_F(vector_test, push_speed) {
  auto start = std::clock();
  int t1 = 0;
  int t2 = 0;
  for (size_t i = 0; i < 100000; ++i) {
    marr1.push_back(i);
  }
  auto mid = std::clock();
  t1 = mid - start;
  for (size_t i = 0; i < 100000; ++i) {
    arr1.push_back(i);
  }
  t2 = std::clock() - mid;
  printf("t1 = %d\nt2 = %d\n t1-t2 = %d\n", t1, t2, t1 - t2);
  bool f = true;
  for (size_t i = 0; i < 100000; ++i) {
    if (marr1[i] != arr1[i]) {
      f = false;
      break;
    }
  }
  EXPECT_TRUE(f);
}
bool test_con_vector(_SPC vector<int> &arr1, std::vector<int> &arr2) {
  bool f = false;
  if (arr1.size() != arr2.size())
    return f;
  for (size_t i = 0; i < arr1.size(); ++i) {
    if (arr1[i] != arr2[i])
      return f;
  }
  return true;
}
TEST(vector_init, xx) {
  std::vector<int> arr{1, 2, 3};
  std::vector<int> arr1(arr.begin(), arr.end());
  _SPC vector<int> marr1(arr.begin(), arr.end());
  EXPECT_TRUE(test_con_vector(marr1, arr1));
  std::vector<int> arr2;
  _SPC vector<int> marr2;
  EXPECT_TRUE(test_con_vector(marr2, arr2));

  std::vector<int> arr3(10);
  _SPC vector<int> marr3(10);
  EXPECT_TRUE(test_con_vector(marr3, arr3));
  std::vector<int> arr4(10, 5);
  _SPC vector<int> marr4(10, 5);
  EXPECT_TRUE(test_con_vector(marr3, arr3));
}
TEST_F(vector_test, insert) {
  marr1.push_back(12);
  arr1.push_back(12);
  EXPECT_TRUE(test_con_vector(marr1, arr1));
  arr1.emplace_back(12);
  marr1.emplace_back(12);
  EXPECT_TRUE(test_con_vector(marr1, arr1));
  arr1.insert(arr1.end(), 2, 5);
  marr1.insert(marr1.end(), 2, 5);
  EXPECT_TRUE(test_con_vector(marr1, arr1));

  arr1.insert(arr1.end(), arr.begin(), arr.end());
  marr1.insert(marr1.end(), arr.begin(), arr.end());
  EXPECT_TRUE(test_con_vector(marr1, arr1));
}
TEST_F(vector_test, insert1) {
  std::queue<int> q;
  q.push(10);

  marr2.push_back(12);
  arr2.push_back(12);
  EXPECT_TRUE(test_con_vector(marr2, arr2));
  arr2.emplace_back(12);
  marr2.emplace_back(12);
  EXPECT_TRUE(test_con_vector(marr2, arr2));
  arr2.insert(arr2.end(), 2, 5);
  marr2.insert(marr2.end(), 2, 5);
  EXPECT_TRUE(test_con_vector(marr2, arr2));
}
struct xxx1 {
  int a;
  int b;
  xxx1(int a, int b) : a(a), b(b) {}
};
struct xx2 {
  xxx1 x;
  xx2(int a, int b) : x(a, b) {}
};
TEST(vector_init, xx1) {
  xx2 x(12, 45);
  EXPECT_EQ(12, x.x.a);
  EXPECT_EQ(45, x.x.b);
  std::queue<int> x1;
  decltype(auto) t1 = x1.back();

  std::queue<int> x2 = x1;
}

int main(int argc, char **argv) {
  //::testing::GTEST_FLAG(filter) ="";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}