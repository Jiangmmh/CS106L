实验指导地址：https://github.com/cs106l/cs106l-assignments/blob/main/assignment2/README.md

## get_applicants



```c++
/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::unordered_set<std::string> get_applicants(std::string filename) {
  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    std::cerr << "Error: Could not open file '" << filename << "'." << std::endl;
    exit(1);
  }

  std::unordered_set<std::string> applicants;

  std::string line;
  while (std::getline(input_file, line)) {
    applicants.insert(line);
  }

  return applicants;
}
```

- 需要读取文件中的内容，使用fstream实现
- 使用`std::unordered_set`按行存储从文件中读取出来的内容
- 使用`std::getline`来进行按行读取非常方便

## find_matches

给定一个`name`和unordered_set `students`，将students中firstname和lastname首字母与name相同的人名全部存入一个queue中并返回。

```c++
/**
 * Takes in a name and returns the initials of that name.
 * For example, "Haven Whitney" would return "HW".
 * 
 * @param name  The name to fetch initials from.
 * @returns     A string containing the initials of the name.
 */
std::string fetch_initials(const std::string& name) {
  std::string initials;

  std::stringstream ss(name);
  std::string token;
  while (std::getline(ss, token, ' ')) {
    if (!token.empty()) {
      initials += token[0];
    }
  }

  return initials;
}

std::queue<const std::string*> find_matches(std::string name, std::unordered_set<std::string>& students) {
  std::queue<const std::string*> matches;
  std::string target_initials = fetch_initials(name);

  for (const std::string& student_name : students) {
    if (fetch_initials(student_name) == target_initials) {
      matches.push(&student_name);
    }
  }

  return matches;
}
```

- 我自定义了一个函数`fetch_initials`来从全名中提取大写首字母串

## get_match

可以任意地自定义规则从matches队列中选择出最终的匹配结果，这里我就直接返回队头元素作为匹配对象了。

```c++
std::string get_match(std::queue<const std::string*>& matches) {
  if (matches.empty()) {
    return "NO MATCHES FOUND.";
  }

  // Example implementation: Return the first match in the queue.
  const std::string* match = matches.front();
  matches.pop();
  return *match;
}
```

## 测试结果：

```shell
~/minghan/courses/CS106L/cs106l-assignments/assignment2 % clang++ -std=c++20 main.cpp -o main
~/minghan/courses/CS106L/cs106l-assignments/assignment2 % ./main
⏳ Installing autograder packages (this may take a few minutes)...
✅ Autograder packages installed.

Running test: test_applicants_set... 🧪
✅ test_applicants_set passed! 🚀

Running test: test_match... 🧪
✅ Matched student 'Memphis Juarez'
✅ test_match passed! 🚀

🚀🚀🚀 Congratulations, your code passed all the autograder tests! 🚀🚀🚀
```

