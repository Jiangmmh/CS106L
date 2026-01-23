实验指导地址：https://github.com/cs106l/cs106l-assignments/blob/main/assignment5/README.md

## Part 1: Viewing Profiles

为User类实现 `<<` 运算符：

```c++
// user.h
class User
{
public:
	......
  friend std::ostream& operator<<(std::ostream& os, const User& user);
	......
};
```

```c++
// user.cpp
std::ostream& operator<<(std::ostream& os, const User& user)
{
  os << "User(name=" << user._name << ", friends=[";
  for (size_t i = 0; i < user._size; ++i) {
    os << user._friends[i];
    if (i < user._size - 1) {
      os << ", ";
    }
  }
  os << "])";
  return os;
}
```

- `operator<<`属于外部函数，因为要获取User对象的私有成员，所以需要将其设置为User的友元函数
- 在实现 `operator<<` 时注意返回类型为 `std::ostream&`，目的是可以在一行中多次使用 `<<` 输出

## Part 2: Unfriendly Behaviour

使用Rule of three实现SMF：

```c++
class User
{
public:
  User(const std::string& name);
  void add_friend(const std::string& name);
  std::string get_name() const;
  size_t size() const;
  void set_friend(size_t index, const std::string& name);

  /** 
   * STUDENT TODO:
   * Your custom operators and special member functions will go here!
   */
  User(const User& other); // Copy constructor
  User& operator=(const User& other); // Copy assignment operator
  User(User&& other) = delete; // Move constructor
  User& operator=(User&& other) = delete; // Move assignment operator
  ~User(); // Destructor

private:
  std::string _name;
  std::string* _friends;
  size_t _size;
  size_t _capacity;
};
```

```c++
User::~User()
{
  if (_friends != nullptr)
    delete[] _friends;
}

User::User(const User& other)
{
  _name = other._name;
  _size = other._size;
  _capacity = other._capacity;
  _friends = new std::string[_capacity];
  for (size_t i = 0; i < _size; ++i) {
    _friends[i] = other._friends[i];
  }
}

User& User::operator=(const User& other)
{
  if (this != &other) {
    delete[] _friends;

    _name = other._name;
    _size = other._size;
    _capacity = other._capacity;
    _friends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      _friends[i] = other._friends[i];
    }
  }
  return *this;
}
```

- 对于包含外部资源的类，需要使用Rule of three，实现析构函数、拷贝构造函数和拷贝赋值运算符
- 在实现拷贝赋值运算符时需要判断等号左右是否为同一个对象，否则可能出现误删的情况，导致资源的丢失

## Part 3: Always Be Friending

实现两个运算符 `+=` 和 `<` 的重载：

```c++
// user.h
class User
{
public:
	...
  User& operator+=(User& other);
  bool operator<(const User& other) const;
  ...
};
```

```c++
User& User::operator+=(User&other)
{
  // 避免自我添加
  if (this == &other) {
    return *this; 
  }

  // 如果_friends容量不足，则先扩容
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  // 添加other为this的朋友
  _friends[_size++] = other._name;

  if (other._size == other._capacity) {
    // 扩容other的_friends
    size_t newCapacity = 2 * other._capacity + 1;
    std::string* newFriends = new std::string[newCapacity];
    for (size_t i = 0; i < other._size; ++i) {
      newFriends[i] = other._friends[i];
    }
    delete[] other._friends;
    other._friends = newFriends;
    other._capacity = newCapacity;
  }
  
  other._friends[other._size++] = _name;

  return *this;
}


bool User::operator<(const User& other) const
{
  return _name < other._name;
}
```

- 在实现 `+=` 时需要考虑扩容的问题
- 朋友是相互的，A将B作为自己的朋友，那么对于B来说，A也是B的朋友（当然，现实中可能不一定）

## 测试结果

```shell
~/minghan/courses/CS106L/cs106l-assignments/assignment5 % clang++ -std=c++20 main.cpp user.cpp -o main
~/minghan/courses/CS106L/cs106l-assignments/assignment5 % ./main                                      
⏳ Installing autograder packages (this may take a few minutes)...
✅ Autograder packages installed.

Running test: Part 1: operator<<... 🧪                                           
✅ Part 1: operator<< passed! 🚀 

Running test: Part 2: Destructor... 🧪                                           
✅ Part 2: Destructor passed! 🚀 

Running test: Part 2: Copy Constructor... 🧪                                     
✅ Part 2: Copy Constructor passed! 🚀 

Running test: Part 2: Copy Assignment Operator... 🧪                             
✅ Part 2: Copy Assignment Operator passed! 🚀 

Running test: Part 2: Move Constructor... 🧪                                     
✅ Part 2: Move Constructor passed! 🚀 

Running test: Part 2: Move Assignment Operator... 🧪                             
✅ Part 2: Move Assignment Operator passed! 🚀 

Running test: Part 3: operator+=... 🧪                                           
✅ Part 3: operator+= passed! 🚀 

Running test: Part 3: operator<... 🧪                                            
✅ Part 3: operator< passed! 🚀 

🚀🚀🚀 Congratulations, your code passed all the autograder tests! 🚀🚀🚀        
```



