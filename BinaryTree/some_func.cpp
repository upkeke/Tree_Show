#include <algorithm>
#include <numeric>
#include <random>
#include <some_func.h>
#include<QSql>

vector<int> get_vector_norepeat(size_t sz, int _min, int _max) {

  if (sz == 0)
    return {};
  vector<int> arr(_max - _min + 1);
  std::iota(arr.begin(), arr.end(), _min);
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(arr.begin(), arr.end(), g);
  vector<int> re(arr.begin(), arr.begin() + sz);

  return re;
}
vector<int> get_vector_order(int _min, int _max) {

  vector<int> arr(_max - _min + 1);
  std::iota(arr.begin(), arr.end(), _min);
  return arr;
}


