
#include "get_test_data.h"
#include "FuncForTreeStr.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <algorithm>
#include <concepts>
#include <config.h>
#include <numeric>
#include <random>
namespace {
// 打乱数组
template <class T> void shuffle_vector(_SPC vector<T> &arr) {
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(arr.begin(), arr.end(), g);
}
_SPC vector<int> get_vector(int _min, int _max) {

  _SPC vector<int> arr(_max - _min + 1);
  std::iota(arr.begin(), arr.end(), _min);
  return arr;
}
} // namespace

// 获得不重复int 数组
_SPC vector<int> get_vector_norepeat(size_t sz, int _min, int _max) {
  if (sz == 0 || _max - _min > sz)
    return {};
  auto arr = get_vector(_min, _max);
  shuffle_vector(arr);
  _SPC vector<int> re(arr.begin(), arr.begin() + sz);
  return re;
}

template <> _SPC vector<QString> get_vector<QString>(size_t sz) {
  if (sz > 50)
    sz = 50;
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("somedata.db");
  QSqlQuery query;
  if (!db.open()) {
    return {};
  }
  QString order =
      QString("select * from string order by random() limit %1;").arg(sz);
  if (!query.exec(order)) {
    return {};
  }
  _SPC vector<QString> arr(sz);
  size_t i = 0;
  while (query.next() && i < sz) {
    arr[i++] = query.value("name").toString();
  }
  return arr;
}

template <> _SPC vector<int> get_vector<int>(size_t sz) {
  _SPC vector<int> arr(sz, 0);
  std::iota(arr.begin(), arr.end(), 0);
  shuffle_vector(arr);
  return arr;
}
template <> _SPC vector<char> get_vector<char>(size_t sz) {
  size_t i = 0;
  char c = 'A';
  _SPC vector<char> arr(sz, 0);
  while (i < sz) {
    arr[i] = c++;
    if (c == 'Z') {
      c = 'A';
    }
  }
  shuffle_vector(arr);
  return arr;
}
template <> _SPC vector<QPointF> get_vector<QPointF>(size_t sz)
{
  auto poss = get_vector_norepeat(100,100,0);
  return {};

}
template <> _SPC vector<NodePtr> get_vector<NodePtr>(size_t sz) {
  auto c_arr = get_vector<char>(sz);
  
  return {};
}
