## 配置开发环境

Python：

```shell
~/minghan/courses/CS106L % python3
Python 3.13.3 (main, Apr  8 2025, 13:54:08) [Clang 16.0.0 (clang-1600.0.26.6)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>>
```

g++：

```shell
~/minghan/courses/CS106L/cs106l-assignments/assignment0 % clang++ -v
Apple clang version 16.0.0 (clang-1600.0.26.6)
Target: arm64-apple-darwin24.1.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
```

git：

```shell
~/minghan/courses/CS106L % git -v
git version 2.39.5 (Apple Git-154)
```

## 获取代码并运行

```shell
git clone https://github.com/cs106l/cs106l-assignments.git
```

进入`assignment0`目录，编译并运行`main.cpp`：

```shell
~/minghan/courses/CS106L/cs106l-assignments/assignment0 % clang++ -std=c++23 main.cpp -o main
~/minghan/courses/CS106L/cs106l-assignments/assignment0 % ./main
🔍 Virtual environment not found. Creating one in 'autograder/'...
✅ Virtual environment created.
⏳ Installing autograder packages (this may take a few minutes)...
✅ Autograder packages installed.

Running test: Check C++ Compiler... 🧪
✅ Check C++ Compiler passed! 🚀

Running test: Check Git Installation... 🧪
✅ Check Git Installation passed! 🚀

Running test: Check Python Installation... 🧪
python version: sys.version_info(major=3, minor=13, micro=3, releaselevel='final', serial=0)
✅ Check Python Installation passed! 🚀

🚀🚀🚀 Congratulations, your code passed all the autograder tests! 🚀🚀🚀
```



