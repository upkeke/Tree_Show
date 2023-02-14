
#pragma once
#ifndef __NODE_TEMP__
#define __NODE_TEMP__
#include <concepts>
#include <config.h>
#include <type_traits>
#include<string>
#if HAS_QSTRING
// 约束保证T是基本类型，或者能够隐式转换为string，QString的自定义类型
template <class T>
concept str_able =
    std::is_arithmetic_v<T> || std::is_convertible_v<T, std::string> ||
    std::is_same_v<T, QString>;
#else
template <class T>
concept str_able =
    std::is_arithmetic_v<T> || std::is_convertible_v<T, std::string>;
#endif
template <class T> struct _baseNode {
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

// 约束Node必须是Node或者Node的子类，
// template <class T>
// concept node_able =
//     requires { requires std::derived_from<T, _baseNode<typename T::tp>>; };

template <class T>
concept node_able =
    requires(T obj) {
      { obj.left } -> std::same_as<T *&>;
      { obj.right } -> std::same_as<T *&>;
      requires str_able<decltype(obj.val)>;
    } ;

#endif
/*|| requires {
           // 这个为了适配前期我前期不合理的设计，全部修改有点麻烦，内部测试
           requires std::derived_from<T, _baseNode<typename T::tp>>;
         }*/