//author : keke
//date : 2023/01/30 
#pragma once
#ifndef __DATA_SOURCE__
#define __DATA_SOURCE__

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

#include <algorithm>
#include <concepts>
#include <numeric>
#include <random>
#include <vector>


using std::vector;
// 打乱数组
template <class T> void shuffle_vector(vector<T> &arr) {
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(arr.begin(), arr.end(), g);
}
// template <>
// vector<int> get_vector_norepeat<int>(size_t sz, int _min = 0, int _max =
// 100); template <class T> vector<int> get_vector_order(int _min, int _max);

template <class T> vector<T> get_vector(size_t sz) { return {}; }
template <> inline vector<QString> get_vector<QString>(size_t sz) {
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
  vector<QString> arr(sz);
  size_t i = 0;
  while (query.next() && i < sz) {
    arr[i++] = query.value("name").toString();
  }
  return arr;
}

inline vector<int> get_vector_order(int _min, int _max) {

  vector<int> arr(_max - _min + 1);
  std::iota(arr.begin(), arr.end(), _min);
  return arr;
}
// 获得不重复int 数组
inline vector<int> get_vector_norepeat(size_t sz, int _min, int _max) {
  if (sz == 0 || _max - _min > sz)
    return {};
  auto arr = get_vector_order(_min, _max);
  shuffle_vector(arr);
  vector<int> re(arr.begin(), arr.begin() + sz);
  return re;
}


#endif