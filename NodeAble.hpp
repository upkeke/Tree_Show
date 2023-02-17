
#pragma once
#ifndef __NODEABLE__
#define __NODEABLE__

#include <concepts>
#include <config.h>
#include <string>
#include <type_traits>

template <class T>
concept str_able =
    std::is_arithmetic_v<T> || std::is_convertible_v<T, std::string>;
template <class T>
concept node_able = requires(T obj) {
                      { obj.left } -> std::same_as<T *&>;
                      { obj.right } -> std::same_as<T *&>;
                      requires str_able<decltype(obj.val)>;
                    };

template <str_able T> struct _baseNode {
  _baseNode(const T &val, _baseNode *left = nullptr, _baseNode *right = nullptr)
      : val(val), left(left), right(right) {}
  _baseNode(T &&val, _baseNode *left = nullptr, _baseNode *right = nullptr)
      : val(std::move(val)), left(left), right(right) {}
  _baseNode() = default;
  T val;
  _baseNode *left;
  _baseNode *right;
  using tp = T;
};
#endif
