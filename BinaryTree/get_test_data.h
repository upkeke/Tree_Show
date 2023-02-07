

#pragma once
#ifndef __GET_TEST_DATA__
#define __GET_TEST_DATA__
#include <BinaryTree.hpp>
#include <QString>
#include <config.h>

_SPC vector<int> get_vector_norepeat(size_t sz, int _min, int _max);

template <class T> _SPC vector<T> get_vector(size_t sz) { return {}; }

template <> _SPC vector<QString> get_vector<QString>(size_t sz);
template <> _SPC vector<int> get_vector<int>(size_t sz);
template <> _SPC vector<char> get_vector<char>(size_t sz);
template <> _SPC vector<QPointF> get_vector<QPointF>(size_t sz);

template <> _SPC vector<NodePtr> get_vector<NodePtr>(size_t sz);
#endif