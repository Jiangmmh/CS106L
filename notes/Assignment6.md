

实验指导：https://github.com/cs106l/cs106l-assignments/blob/main/assignment6/README.md

## Part 0: Include `<optional>`

包含头文件`<optional>`：

```c++
#include <optional>
```

## Part 1: Write the `find_course` function

实现`find_course`函数，用于从courses中找到目标课程，需要使用`std::optinal`：

```c++
std::optional<FillMeIn> find_course(std::string course_title)
{
    /* STUDENT_TODO: Implement this method! You will need to change the return
     * type. */
    for (size_t i = 0; i < courses.size(); ++i) {
      if (courses[i].title == course_title) {
        return &courses[i];
      }
    }

    return std::nullopt;
}
```

## Part 2: Modifying the `main` function

修改main函数，使用optional函数：

```c++
int
main(int argc, char* argv[])
{
  static_assert(
    !std::is_same_v<std::invoke_result_t<decltype (&CourseDatabase::find_course), 
                      CourseDatabase, std::string>,
                    FillMeIn>,
    "You must change the return type of CourseDatabase::find_course to "
    "something other than FillMeIn.");

  if (argc == 2) {
    CourseDatabase db("autograder/courses.csv");
    auto course = db.find_course(argv[1]);
    
    /******************************************************** 
    STUDENT_TODO: Populate the output string with the right information to print
    Please pay special attention to the README here
    ********************************************************/

    std::string output = course.has_value()
                           ? "Found course: " + course.value()->title + "," +
                               course.value()->number_of_units + "," + course.value()->quarter
                               + "\n"
                           : "Course not found.";

    /********************************************************
     DO NOT MODIFY ANYTHING BELOW THIS LINE PLEASE
    ********************************************************/

    std::cout << output << std::endl;
    return 0;
  }
  
  return run_autograder();
}
```

`std::optional`的方法

- `.value() `：返回有效值或抛出`bad_optional_access`错误
- `*optional`：效果和`value()`一样
- `.value_or(valueType val)`：返回有效值或者默认值val
- `.has_value() `：如果有效值存在返回true，否则返回false

## 测试结果

```shell
~/minghan/courses/CS106L/cs106l-assignments/assignment6 % clang++ -std=c++23 main.cpp -o main
~/minghan/courses/CS106L/cs106l-assignments/assignment6 % ./main                             
⏳ Installing autograder packages (this may take a few minutes)...
✅ Autograder packages installed.

Running test: Present Courses... 🧪                                              
✅ Present Courses passed! 🚀 

Running test: Missing Courses... 🧪                                              
✅ Missing Courses passed! 🚀 

🚀🚀🚀 Congratulations, your code passed all the autograder tests! 🚀🚀🚀        
```

