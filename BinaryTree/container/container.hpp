
#pragma once
#ifndef __CON_LIST__
#define __CON_LIST__

// #include "BinaryTree.hpp"
#include <functional>
#include <initializer_list>
#include <memory>
#include <type_traits>

namespace con {
template <class _Iter>
concept _iter_able = requires(_Iter obj) {
                       requires(!std::is_integral_v<_Iter>);
                       obj - obj;
                       *obj;
                       obj++;
                       obj != obj;
                     };
template <typename T> class vector {
public:
  using Iter = T *;
  vector() : _arr(nullptr), _size(0), _capacity(0) {}
  vector(vector &other) : vector() {
    insert(end(), other.begin(), other.end());
  }
  vector(vector &&other) : _size(other.size()), _capacity(other.max_size()) {
    _arr = other._arr;
    _capacity = other._capacity;
    _size = other._size;

    other._capacity = 0;
    other._size = 0;
    other._arr = nullptr;
  }
  vector &operator=(const vector &) = delete;
  vector &operator=(vector &&) = delete;
  template <_iter_able _Iter> vector(_Iter First, _Iter Last) : vector() {
    insert(end(), First, Last);
  }
  vector(const std::initializer_list<T> &data) : _size(data.size()) {
    _capacity = 2 * _size;
    _arr = alloc.allocate(_capacity);
    memcpy(_arr, data.begin(), sizeof(T) * _size);
  }
  vector(size_t count, const T &val = T{}) : vector() {
    insert(end(), count, val);
  }

  Iter begin() { return {_arr}; }
  Iter end() { return {_arr + _size}; }

  void push_back(const T &val) {
    check_alloc(1);
    new (_arr + _size++) T(val);
  }
  void insert(Iter pos, size_t count, const T &val) {
    check_alloc(count);
    auto temp = _arr + _size;
    for (size_t i = _size; i < _size + count; ++i) {
      new (temp++) T(val);
    }
    _size += count;
  }
  template <_iter_able _Iter> void insert(Iter pos, _Iter First, _Iter Last) {
    check_alloc(Last - First);
    pos = _arr + _size;
    while (First != Last) {
      new (pos++) T(*First);
      First++;
      _size++;
    }
  }
  template <typename... Args> void emplace_back(Args &&...rest) {
    check_alloc(1);
    new (_arr + _size++) T(std::forward<Args>(rest)...);
  }
  size_t size() const { return _size; }
  size_t max_size() const { return _capacity; }
  T &operator[](int index) { return _arr[index]; }
  void clear() { _size = 0; }
  bool empty() { return _size == 0; }
  ~vector() {
    if constexpr (std::is_class_v<T>) {
      T *temp = _arr;
      for (size_t i = 0; i < _size; ++i)
        temp->~T();
      temp++;
    } else
      ;
    alloc.deallocate(_arr, _capacity);
  }

private:
  void check_alloc(size_t add_size) {
    if (_size + add_size > _capacity) {
      _capacity = 2 * _size;
      auto temp = alloc.allocate(_capacity);
      memcpy(temp, _arr, sizeof(T) * _size);
      alloc.deallocate(_arr, _size);
      _arr = temp;
    }
  }
  inline static std::allocator<T> alloc = std::allocator<T>();
  T *_arr;
  size_t _size;
  size_t _capacity;
  size_t _curIndex = 0;
};

/*------------------------------------------------------------
--------------------------------------------------------------
--------------------------------------------------------------
*/
// template <class T> struct listNode {
//   T val = T{};
//   listNode *next = nullptr;
//   listNode() = default;
//   listNode(T _val, listNode *_next = nullptr) : val(_val), next(_next) {}
// };

// 指针容器
template <class T> class deque_list {
private:
  struct listNode {
    T val;
    listNode *next = nullptr;
    listNode() = default;
    listNode(const T &_val, listNode *_next = nullptr)
        : val(_val), next(_next) {}
    listNode(T &&_val, listNode *_next = nullptr)
        : val(std::move(_val)), next(_next) {}
    template <class... Args>
    listNode(listNode *_next, Args &&...val)
        : val(std::forward<Args>(val)...), next(_next) {}
  };
  using type_list = std::initializer_list<T>;
  using size_type = size_t;

public:
  // list(type_list arr);
  deque_list() {
    first = std::allocator<listNode>().allocate(1);
    // last = std::allocator<listNode>().allocate(1);
    last = first;
  }
  deque_list(deque_list &other) {
    listNode *start = other.first;
    listNode *end = other.last;
    sz = other.sz;
    while (start != end) {
      push_back(start->val);
      start = start->next;
    }
  }
  deque_list(deque_list &&other) {
    first = other.first;
    last = other.last;
    sz = other.sz;
    other.first = nullptr;
    other.last = nullptr;
    other.sz = 0;
  }
  void push_back(const T &val) {
    ++sz;
    if (first == last && sz == 1) {
      new (last) listNode(val);
      return;
    }
    last->next = new listNode(val);
    last = last->next;
  }
  void push_back(T &&val) {
    ++sz;
    if (first == last && sz == 1) {
      new (last) listNode(std::move(val));
      return;
    }
    last->next = new listNode(std::move(val));
    last = last->next;
  }
  T &back() { return last->val; }
  template <class... Args> void emplace_back(Args &&...val) {
    ++sz;
    if (first == last && sz == 1) {
      new (last) listNode(nullptr, std::forward<Args>(val)...);
      return;
    }
    last->next = new listNode(nullptr, std::forward<Args>(val)...);
    last = last->next;
  }

  void push_front(const T &val) {
    ++sz;
    if (first == last && sz == 1) {
      new (last) listNode(val);
      return;
    }
    first = new listNode(val, first);
  }
  void push_front(T &&val) {
    ++sz;
    if (first == last && sz == 1) {
      new (last) listNode(std::move(val));
      return;
    }
    first = new listNode(std::move(val), first);
  }
  T &front() { return first->val; }
  template <class... Args> void emplace_front(Args &&...val) {
    ++sz;
    if (first == last && sz == 1) {
      new (last) listNode(nullptr, std::forward<Args>(val)...);
      return;
    }
    first = new listNode(first, std::forward<Args>(val)...);
  }
  void pop_front() {
    if (sz == 0) {
      return;
    }
    --sz;
    auto tp = first->next;
    delete first;
    first = tp;
  }

  size_t size() const { return sz; }
  bool empty() const { return sz == 0; }

private:
  listNode *first = nullptr;
  listNode *last = nullptr;
  size_t sz = 0;
  inline static std::allocator<T> alloc = std::allocator<T>{};
  void insert_init() {

    // last->next = new listNode(forward<Args>(val)...);
    // last = last->next;
  }

public:
  bool operator==(const deque_list &other) const;
  bool operator<(const deque_list &other) const;
  bool operator<=(const deque_list &other) const;
  bool operator>(const deque_list &other) const;
  bool operator>=(const deque_list &other) const;
};
template <class T>
typename deque_list<T>::Iter next(typename deque_list<T>::Iter first, int off);

template <class _Ty> class queue {
public:
  using value_type = _Ty;
  using reference = _Ty &;
  using size_type = size_t;
  using container_type = deque_list<_Ty>;
  queue() = default;
  explicit queue(container_type &_Cont) : c(_Cont) {}
  explicit queue(container_type &&_Cont) : c(std::move(_Cont)) {}
  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  reference front() { return c.front(); }
  reference back() { return c.back(); }

  void push(const value_type &_Val) { c.push_back(_Val); }
  void push(value_type &&_Val) { c.push_back(std::move(_Val)); }
  template <class... _Valty> decltype(auto) emplace(_Valty &&..._Val) {
    return c.emplace_back(std::forward<_Valty>(_Val)...);
  }
  void pop() { c.pop_front(); }
  // void swap(queue &_Right) { _Swap_adl(c, _Right.c); }
  // const container_type &_Get_container() const  { return c; }

protected:
  container_type c{};
};

template <class _Ty> class stack {
public:
  using value_type = _Ty;
  using reference = _Ty &;
  using size_type = size_t;
  using container_type = deque_list<_Ty>;
  stack() = default;
  explicit stack(container_type &_Cont) : c(_Cont) {}
  explicit stack(container_type &&_Cont) : c(std::move(_Cont)) {}
  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  reference top() { return c.front(); }
  void push(const value_type &_Val) { c.push_front(_Val); }
  void push(value_type &&_Val) { c.push_front(std::move(_Val)); }
  template <class... _Valty> decltype(auto) emplace(_Valty &&..._Val) {
    return c.emplace_front(std::forward<_Valty>(_Val)...);
  }
  void pop() { c.pop_front(); }
  // void swap(stack &_Right) { _Swap_adl(c, _Right.c); }
  // const container_type &_Get_container() const { return c; }

protected:
  container_type c{};
};

} // namespace con

#endif
