实验指导：https://github.com/cs106l/cs106l-assignments/blob/main/assignment1/README.md

首先查看要处理的CSV文件：

```shell
Title,Number of Units,Quarter
Introduction to Computing at Stanford (VPTL 1),1,null
Practical Unix,1,null
Personal Finance for Engineers,1,2023-2024 Autumn
Problem-Solving for the CS Technical Interview,1,null
How to Make VR: Introduction to Virtual Reality Design and Development,2,2023-2024 Autumn
Introduction to Mobile Augmented Reality Design and Development,1,2023-2024 Spring
Introduction to Version Control with Git,1,null
...............................................
```

一共336行，每行包含了三个元素，将它们均定义为`std::string`类型：

```c++
struct Course {
  std::string title;
  std::string number_of_units;
  std::string quarter;
};
```

然后再来看看main函数：

```c++
int main() {
  /* Makes sure you defined your Course struct correctly! */
  static_assert(is_valid_course<Course>, "Course struct is not correctly defined!");

  std::vector<Course> courses;
  parse_csv("courses.csv", courses);

  /* Uncomment for debugging... */
  // print_courses(courses);

  write_courses_offered(courses);
  write_courses_not_offered(courses);

  return run_autograder();
}
```

- 首先定义了一个vector `courses`，使用函数`parse_csv`将`course.csv`中的数据读到`courses`中。
- 将course中offered的部分写入到`student_output/courses_offered.csv`中
- 将course中not_offered的部分写入到`student_output/courses_offered.csv`中

## parse_csv

```c++
// 修改了参数 courses 的类型，从值传递改为引用传递
void parse_csv(std::string filename, std::vector<Course>& courses) {
  std::ifstream file(filename, std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  std::string line;
  // Skip the header line
  std::getline(file, line); 

  while (std::getline(file, line)) {
    std::vector<std::string> tokens = split(line, ',');
    if (tokens.size() != 3) {
      std::cerr << "Invalid line format: " << line << std::endl;
      continue;
    }

    Course course;
    course.title = tokens[0];
    course.number_of_units = std::stoi(tokens[1]);
    course.quarter = tokens[2];

    courses.push_back(course);
  }
}
```

- 读取文件filename中的内容，因此使用ifstream
- csv文件中的每一行（除第一行外）都代表一个Course对象，因此按行读取
- 调用utility中的`split`函数，提取出每行中的以`','`分隔的所有元素
- 构建Course对象并push_back到courses中

其中split函数的实现如下：

```c++
/**
 * Splits a string by a delimiter and returns a vector of the split strings.
 * @param s     The string to split.
 * @param delim The delimiter to split by.
 * @returns     A vector of the split strings.
 */
std::vector<std::string> split(const std::string& s, char delim) {
  std::vector<std::string> return_vec;
  std::stringstream ss(s);
  std::string token;
  while (std::getline(ss, token, delim)) {
    return_vec.push_back(token);
  }
  return return_vec;
}
```

发现在split中也调用了std::geline函数，该函数有多个重载版本，两个参数的版本以`'\n'`为delim，三个参数的版本可以自定义delim。

## write_courses_offered

将刚刚读取到的courses中的offered（第三列值不为`"null"`）记录写入文件`student_output/courses_offered.csv`中

```c++
void write_courses_offered(std::vector<Course>& all_courses) {
  std::ofstream file(COURSES_OFFERED_PATH, std::ios::out);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << COURSES_OFFERED_PATH << std::endl;
    return;
  }

  // Write CSV header
  file << "Title,Number of Units,Quarter\n";

  std::vector<Course> offered_courses;

  for (const Course& course : all_courses) {
    if (course.quarter != "null") {
      file << std::format("{},{},{}\n", course.title, course.number_of_units, course.quarter);
      offered_courses.push_back(course);
    }
  }

  file.close();

  // 不能在遍历时直接删除元素，不然会导致迭代器失效
  for (const Course& course : offered_courses) {
    delete_elem_from_vector(all_courses, course);
  }
}
```

- 该函数要求在将offered课程记录写入文件后将其从all_courses中删除
- 使用ofstream来完成文件输出任务
- 此外我还使用了新学的`std::format`函数，使用该函数可以构造字符串格式，避免繁琐的拼接
- 需要注意：不能简单地在一次遍历中就记录删除，不然会导致迭代器失效，出现错误

## write_courses_not_offered

```c++
void write_courses_not_offered(std::vector<Course>& unlisted_courses) {
  std::ofstream file(COURSES_NOT_OFFERED_PATH, std::ios::out);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << COURSES_NOT_OFFERED_PATH << std::endl;
    return;
  }

  // Write CSV header
  file << "Title,Number of Units,Quarter\n";

  for (const Course& course : unlisted_courses) {
    file << std::format("{},{},{}\n", course.title, course.number_of_units, course.quarter);
  }
}
```

与`write_courses_offered`的实现差不多，不需要考虑删除问题

## 测试结果

测试一下：

```c++
~/minghan/courses/CS106L/cs106l-assignments/assignment1 % clang++ -std=c++20 main.cpp -o main
~/minghan/courses/CS106L/cs106l-assignments/assignment1 % ./main
🔍 Virtual environment not found. Creating one in 'autograder/'...
✅ Virtual environment created.
⏳ Installing autograder packages (this may take a few minutes)...
✅ Autograder packages installed.

Running test: Autograder Setup... 🧪

Running test: write_course_offered... 🧪
✅ write_course_offered passed! 🚀

Running test: write_course_not_offered... 🧪
✅ write_course_not_offered passed! 🚀

Running test: Autograder Teardown... 🧪

🚀🚀🚀 Congratulations, your code passed all the autograder tests! 🚀🚀🚀
```

## 总结

- 了解了CSV文件的格式
- 复习了`ifstraem`、`ofstream`和`stringstream`的使用
- 复习了`std::getline`的使用方法，默认delim为`'\n'`，因此每次读取一行内容，也可以自定义delim，实现自己的读取方式
- 学习了使用`std::format`来构造目标格式的字符串，避免了繁琐的字符串拼接

