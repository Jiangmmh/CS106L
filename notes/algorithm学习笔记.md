在写Assignment4时发现自己对于`<algorithm>`中的很多算法不熟悉，在此复习一下cppreference中`<algorithm>`中的重要函数模版。

参考地址：https://en.cppreference.com/w/cpp/algorithm.html

## 简介

在 C++ 中，`<algorithm>` 是标准模板库（STL）的灵魂。它提供了一组**不属于任何特定容器**的通用函数，可以作用于任何提供了迭代器接口的序列（如 `vector`, `list`, `string`, `set` 等）。它的核心哲学是：**将“数据结构”与“算法逻辑”解耦**。

要理解 `<algorithm>`，必须理解这三个概念：

1. **迭代器区间 (Iterator Ranges)**: 几乎所有算法都接受 `[first, last)` 形式的半开区间。这使得算法可以处理整个容器，也可以只处理其中的一小段。
2. **泛型 (Generics)**: 算法通过模板实现。只要你的自定义类重载了必要的运算符（如 `operator<` 用于排序，`operator==` 用于查找），就可以直接使用这些标准算法。
3. **组合性**: 算法可以配合**迭代器适配器**（如 `std::back_inserter`）来动态改变行为。

并且大多数算法都允许传入一个自定义规则（谓词），例如：

```c++
std::vector<int> nums = {1, 2, 3, 4, 5, 6};

// 使用 Lambda 表达式找到第一个偶数
auto it = std::find_if(nums.begin(), nums.end(), [](int n) {
    return n % 2 == 0;
});
```

### 1. 非修改性序列操作 (Non-modifying)

特点：只读不写，主要用于查找、计数和属性检查。

- **计数与搜索**：
  - `count` / `count_if`: 统计等于某值（或满足条件）的元素个数。
  - `find` / `find_if` / `find_if_not`: 寻找第一个匹配的元素。
  - `find_end`: 在序列 A 中寻找序列 B 最后一次出现的位置。
  - `find_first_of`: 在序列 A 中寻找序列 B 中任何一个元素第一次出现的位置。
  - `adjacent_find`: 寻找第一对相邻且相等的元素。
- **子序列与匹配**：
  - `search` / `search_n`: 寻找子序列或连续n个相同元素。
  - `mismatch`: 找到两个序列中第一个不匹配的位置。
  - `equal`: 判断两个序列是否完全相同。
- **谓词检查 (C++11)**：
  - `all_of` / `any_of` / `none_of`: 检查区间内是否 全部/至少一个/没有 元素满足条件。

## 2. 修改性序列操作 (Modifying)

**特点**：会改变容器内元素的值，或在不同容器间搬运数据。

- **复制与移动**：
  - `copy` / `copy_n` / `copy_if` / `copy_backward`: 复制元素。
  - `move` / `move_backward`: 移动元素（C++11）。
- **赋值与生成**：
  - `fill` / `fill_n`: 用固定值填充。
  - `generate` / `generate_n`: 用函数/生成器的返回值填充。
- **变换与替换**：
  - `transform`: **核心算法**，对每个元素应用函数并将结果存入目标位置（类似于 Map）。
    - foreach将函数作用于本容器，而transform在作用完后将其存入目标位置
  - `replace` / `replace_if`: 将匹配的元素替换为新值。
  - `replace_copy` / `replace_copy_if`: 不改原序列，生成替换后的副本。
- **删除与去重**：
  - `remove` / `remove_if`: 将符合条件的元素删除。
  - `unique`: 相邻去重（通常先 sort 再 unique）。
  - `remove_copy` / `unique_copy`: 对应的副本操作。

## 3. 排序及相关操作 (Sorting & Related)

**特点**：改变元素的物理顺序。通常要求**随机访问迭代器**。

- **基础排序**：

  - `sort`: 快速排序变体（内省排序），O(nlogn)。
  - `stable_sort`: 稳定排序，保证相等元素的相对顺序。
  - `partial_sort`: 这个函数并不是对数组的部分进行排序，而是将总排序的结果作用于部分分区
  - `nth_element`: 找到排在第 n 位的元素，且左边都比它小，右边都比它大。

- **分区 (Partitioning)**：

  - `partition`: 按条件把元素分成两组（满足条件在前）。
  - `stable_partition`: 保持相对顺序的分区。
  - `partition_point`: 找到分区的分界点，

  ```c++
  #include <algorithm>
  #include <array>
  #include <functional>
  #include <iostream>
   
  void print(const auto& s, int middle)
  {
      for (int a : s)
          std::cout << a << ' ';
      std::cout << '\n';
      if (middle > 0)
      {
          while (middle-- > 0)
              std::cout << "--";
          std::cout << '^';
      }
      else if (middle < 0)
      {
          for (auto i = s.size() + middle; --i; std::cout << "  ")
          {}
   
          for (std::cout << '^'; middle++ < 0; std::cout << "--")
          {}
      }
      std::cout << '\n';
  };
   
  int main()
  {
      std::array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
      print(s, 0);
      std::partial_sort(s.begin(), s.begin() + 3, s.end());
      print(s, 3);
      std::partial_sort(s.rbegin(), s.rbegin() + 4, s.rend());
      print(s, -4);
      std::partial_sort(s.rbegin(), s.rbegin() + 5, s.rend(), std::greater{});
      print(s, -5);
  }
  
  
  5 7 4 2 8 6 1 9 0 3
   
  0 1 2 7 8 6 5 9 4 3
  ------^
  4 5 6 7 8 9 3 2 1 0
            ^--------
  4 3 2 1 0 5 6 7 8 9
          ^----------
  ```

## 4. 二分搜索操作 (Binary Search)

**特点**：作用于**已排序**的区间，复杂度均为 O(log N)。

- `lower_bound`: 寻找第一个 **大于等于** x 的位置（插入点）。
- `upper_bound`: 寻找第一个 **大于** x 的位置。
- `equal_range`: 返回一个 pair，包含 `lower_bound` 和 `upper_bound` 的区间。
- `binary_search`: 仅返回 `bool`，判断值是否存在。

## 5. 集合操作 (Set Operations)

**特点**：通常作用于**已排序**的区间，执行数学意义上的集合运算。

- `set_union`: 创建一个已排序的union，放到目的迭代器位置。
- `set_intersection`: 交集。
- `set_difference`: 差集。
- `set_symmetric_difference`: 对称差集。
- `includes`: 判断 A 是否包含 B 的所有元素。
- `merge`: 合并两个有序序列。

## 6. 堆操作 (Heap Operations)

**特点**：将序列维护成堆结构（通常默认为最大堆）。

- `make_heap`: 把区间变成堆。
- `push_heap` / `pop_heap`: 向堆添加/弹出元素。
- `sort_heap`: 将堆变成有序序列。
- `is_heap` / `is_heap_until`: 检查堆属性。

