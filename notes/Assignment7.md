实验指导：https://github.com/cs106l/cs106l-assignments/blob/main/assignment7/README.md

这个作业给出了一定的框架代码，要求实现一个简单的智能指针`unique_ptr`，拥有RAII的基本功能。

## Part 1: Implementing `unique_ptr`

实现`cs106l::unique_ptr`中定义好的接口：

```c++
#pragma once

#include <cstddef>
#include <utility>

namespace cs106l {

/**
 * @brief A smart pointer that owns an object and deletes it when it goes out of scope.
 * @tparam T The type of the object to manage.
 * @note This class is a simpler version of `std::unique_ptr`.
 */
template <typename T> class unique_ptr {
private:
  /* STUDENT TODO: What data must a unique_ptr keep track of? */
  T* ptr_;
public:
  /**
   * @brief Constructs a new `unique_ptr` from the given pointer.
   * @param ptr The pointer to manage.
   * @note You should avoid using this constructor directly and instead use `make_unique()`.
   */
  unique_ptr(T* ptr) : ptr_(ptr) {
    /* STUDENT TODO: Implement the constructor */
  }

  /**
   * @brief Constructs a new `unique_ptr` from `nullptr`.
   */
  unique_ptr(std::nullptr_t) : ptr_(nullptr) {
    /* STUDENT TODO: Implement the nullptr constructor */
  }

  /**
   * @brief Constructs an empty `unique_ptr`.
   * @note By default, a `unique_ptr` points to `nullptr`.
   */
  unique_ptr() : unique_ptr(nullptr) {}

  /**
   * @brief Dereferences a `unique_ptr` and returns a reference to the object.
   * @return A reference to the object.
   */
  T& operator*() {
    /* STUDENT TODO: Implement the dereference operator */
    return *ptr_;
  }

  /**
   * @brief Dereferences a `unique_ptr` and returns a const reference to the object.
   * @return A const reference to the object.
   */
  const T& operator*() const {
    /* STUDENT TODO: Implement the dereference operator (const) */
    return *ptr_;
  }

  /**
   * @brief Returns a pointer to the object managed by the `unique_ptr`.
   * @note This allows for accessing the members of the managed object through the `->` operator.
   * @return A pointer to the object.
   */
  T* operator->() {
    /* STUDENT TODO: Implement the arrow operator */
    return ptr_;
  }

  /**
   * @brief Returns a const pointer to the object managed by the `unique_ptr`.
   * @note This allows for accessing the members of the managed object through the `->` operator.
   * @return A const pointer to the object.
   */
  const T* operator->() const {
    /* STUDENT TODO: Implement the arrow operator */
    return ptr_;
  }

  /**
   * @brief Returns whether or not the `unique_ptr` is non-null.
   * @note This allows us to use a `unique_ptr` inside an if-statement.
   * @return `true` if the `unique_ptr` is non-null, `false` otherwise.
   */
  operator bool() const {
    /* STUDENT TODO: Implement the boolean conversion operator */
    return ptr_ != nullptr;
  }

  /** STUDENT TODO: In the space below, do the following:
   * - Implement a destructor
   * - Delete the copy constructor
   * - Delete the copy assignment operator
   * - Implement the move constructor
   * - Implement the move assignment operator
   */

  ~unique_ptr() {
    delete ptr_;
  }

  unique_ptr(const unique_ptr& other) = delete;
  unique_ptr& operator=(const unique_ptr& other) = delete;

  unique_ptr(unique_ptr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  unique_ptr& operator=(unique_ptr&& other) noexcept {
    if (this != &other) { 
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  } 
};

/**
 * @brief Creates a new unique_ptr for a type with the given arguments.
 * @example auto ptr = make_unique<int>(5);
 * @tparam T The type to create a unique_ptr for.
 * @tparam Args The types of the arguments to pass to the constructor of T.
 * @param args The arguments to pass to the constructor of T.
 */
template <typename T, typename... Args> 
unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}
```

- 智能指针需要管理裸指针，因此需要有一个类型为 `T*` 的私有成员
- 要实现RAII的特性和`unique_ptr`的独占资源的功能，需要delete掉拷贝构造函数和拷贝赋值运算符，实现移动构造函数和移动赋值运算符，实现析构函数
- 智能指针需要有普通指针相同的行为，即 `*` 和 `->` 运算符，并且要重载非const和const两个版本
- 如果需要管理数组的裸指针，可以重新定义一个模版类 `class unique_ptr<T[]>`，在实现析构函数时使用`delete[]`释放资源
- 注意`make_unique`的实现，使用 `&&` +`std::forward` 实现了完美转发

  - 如果用户传入的参数为临时变量，T会调用移动构造函数
  - 如果用户传入的参数为普通变量，T会调用拷贝构造函数
  - 之所以需要完美转发，是为了防止用户通过 `make_unique` 传入的参数由于经过了 `make_unique` 这层包装后改变其 “左值” 和 “右值” 的特性，因为即使使用右值引用作为参数的类型，能够接收右值，但右值引用本身是一个左值，将其作为`unique_ptr` 的构造函数的参数时，会考虑调用拷贝构造函数，然而拷贝构造函数被删除了，因此会报错
  - 而使用 `&&` + `std::forward` 会保留传入参数的原有特性，避免这个问题

## Part 2: Using `unique_ptr`



```c++
/*
 * CS106L Assignment 7: Unique Pointer
 * Created by Jacob Roberts-Baca.
 */

#include <functional>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "unique_ptr.h"

/**
 * @brief A singly-linked list node that deallocates itself automatically
 * by using a `unique_ptr` to manage the pointer to the next node.
 * @tparam T The type of the value stored in the node.
 *
 * @note No modifications are necessary to this struct in order to complete the assignment!
 */
template <typename T> struct ListNode {

  /** @brief The value stored inside this node. */
  T value;

  /** @brief The smart pointer to the next node. May be null. */
  cs106l::unique_ptr<ListNode<T>> next;

  /**
   * @brief Constructs a single element linked list, setting `next` to `nullptr`.
   * @param value The value to store in the node.
   */
  ListNode(T value) : value(value), next(nullptr) {
    /* This line is just here for logging purposes so we can see when the
     * constructor runs!
     */
    std::cout << "Constructing node with value '" << value << "'\n";
  }

  ~ListNode() {
    /* This line is just here for logging purposes so we can see when the
     * destructor runs!
     */
    std::cout << "Destructing node with value '" << value << "'\n";
  }
};

/**
 * @brief Creates a singly-linked list from a vector of values.
 * @param values The values to store in the list.
 * @return A `unique_ptr` to the head of the list.
 */
template <typename T> cs106l::unique_ptr<ListNode<T>> create_list(const std::vector<T>& values) {
  /* STUDENT TODO: Implement this method */
  if (values.empty()) {
    return cs106l::unique_ptr<ListNode<T>>(nullptr);
  }

  size_t idx = values.size() - 1;
  auto head = cs106l::make_unique<ListNode<T>>(values[idx]);
  while (idx-- > 0) {
    auto new_node = cs106l::make_unique<ListNode<T>>(values[idx]);
    new_node->next = std::move(head);
    head = std::move(new_node);
  }
  return head;
}

/**
 * @brief Applies a function to each element in the linked list.
 * @tparam T The type of the value stored in the list.
 * @tparam Func The type of the function to apply.
 * @param head The head of the linked list.
 * @paragraph func The function to apply to each element.
 */
template <typename T, typename Func>
void map_list(const cs106l::unique_ptr<ListNode<T>>& head, const Func& func) {
  if (!head)
    return;
  func(head->value);
  map_list(head->next, func);
}

/**
 * @brief An example of using a singly-linked list with `unique_ptr`.
 */
void linked_list_example() {
  std::vector<std::string> names{"Jacob", "Fabio", "Keith", "Chris", "Sean"};
  auto head = create_list(names);
  map_list(head, [](const std::string& name) { std::cout << name << "\n"; });
}

#include "autograder/utils.hpp"
```

- 注意在实现 `create_list` 时，使用`std::move`来将node转换为右值，避免调用拷贝赋值运算符

## 测试结果

```shell
~/minghan/courses/CS106L/cs106l-assignments/assignment7 % clang++ -std=c++20 main.cpp -o main
^[[A%                                                                                                                            
~/minghan/courses/CS106L/cs106l-assignments/assignment7 % ./main                             
⏳ Installing autograder packages (this may take a few minutes)...
✅ Autograder packages installed.

Running test: Part 1: Destructor... 🧪                                           
✅ Part 1: Destructor passed! 🚀 

Running test: Part 1: Deleted copy constructor and assignment... 🧪              
✅ Part 1: Deleted copy constructor and assignment passed! 🚀 

Running test: Part 1: Move constructor... 🧪                                     
✅ Part 1: Move constructor passed! 🚀 

Running test: Part 1: Move assignment... 🧪                                      
✅ Part 1: Move assignment passed! 🚀 

Running test: Part 1: Move assignment (self-assignment)... 🧪                    
✅ Part 1: Move assignment (self-assignment) passed! 🚀 

Running test: Part 2: Linked List... 🧪                                          
✅ Part 2: Linked List passed! 🚀 

🚀🚀🚀 Congratulations, your code passed all the autograder tests! 🚀🚀🚀       
```

