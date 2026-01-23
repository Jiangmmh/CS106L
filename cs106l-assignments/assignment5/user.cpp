#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

/** 
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will go here!
 */

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