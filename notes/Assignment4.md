实验指导：https://github.com/cs106l/cs106l-assignments/blob/main/assignment4/README.md

该实验要求实现一个程序，其功能类似Unix中的Ispell，用于拼写的检查并推荐可能的替代。首先会提供一个字典文件，其中包含了全部的正确拼写的单词，用户输入的单词存在拼写错误意味着这个词在字典文件不存在，推荐词的依据来自Damerau-Levenshtein距离（衡量的是需要多少次编辑才能使两个词相同）。启动代码中提供了大部分的实现，需要我们实现的只有`tokenize`和`spellcheck`这两个函数，要求：

- 不能在代码中使用for/while循环
- `tokenize`要使用传统的STL算法实现
- `spellcheck`要使用新的range库实现

## tokenize

```c++
Corpus tokenize(std::string &source)
{
  // 1. 找到字符串的边界和所有空白字符的迭代器位置
  auto space_its = find_all(source.begin(), source.end(), [](char c) {
    return std::isspace(c);
  });

  // 2. 使用std::transform将每一对(begin, end)转换为Token对象，并插入到tokens集合中
  Corpus tokens;
  std::transform(
      space_its.begin(), 
      std::prev(space_its.end()), 
      std::next(space_its.begin()), 
      std::inserter(tokens, tokens.end()),
      [&source](auto begin, auto end) { 
        return Token(source, begin, end); 
      });
  
  // 3. 删除content为空的Token对象
  std::erase_if(tokens, [](const Token &t) { 
    return t.content.empty(); 
  });
  
  return tokens;
}
```

- 首先使用框架代码提供的find_all函数，找出开始、结束和空白字符在字符串中的迭代器
  - 空白字符包括：space (`0x20`, ' ')、form feed (`0x0c`, '**\f**')、line feed (`0x0a`, '**\n**')、carriage return (`0x0d`, '**\r**')、horizontal tab (`0x09`, '**\t**')、vertical tab (`0x0b`, '**\v**')
  - 开始为source.begin(), 结束为source.end()
- 使用 transform + inserter，构造token并插入到集合tokens中

- 最后使用erase_if（C++20）剔除掉tokens中的内容为空的token

## spellcheck

```c++
std::set<Misspelling> spellcheck(const Corpus &source, const Dictionary &dictionary)
{
  namespace rv = std::ranges::views;
  std::set<Misspelling> results;

  // 筛选出存在错误拼写的token
  auto misspelled_tokens = source | rv::filter([&](const Token &t) {
    return !t.content.empty() && dictionary.find(t.content) == dictionary.end();
  });

  // 对所有错误拼写的token，构建Misspelling，并找出levenshtein距离为1的字符串作为建议
  auto with_suggestions = misspelled_tokens
    | rv::transform([&](const Token &t) {
        std::set<std::string> suggestions;
        std::ranges::copy_if(dictionary, std::inserter(suggestions, suggestions.end()),
          [&](const auto &word) {
            return levenshtein(t.content, word) == 1;
          });
        Misspelling m{t};
        m.suggestions = suggestions;
        return m;
      })
    // 过滤掉所有没有建议的Misspelling
    | rv::filter([](const Misspelling &m) { return !m.suggestions.empty(); });
  
  results = std::set<Misspelling>(with_suggestions.begin(), with_suggestions.end());
  return results;
}
```

- 注意使用`namespace rv = std::ranges::views;`来简化代码的编写

## 测试结果

```shell
~/minghan/courses/CS106L/cs106l-assignments/assignment4 % clang++ -std=c++20 main.cpp spellcheck.cpp -o main

~/minghan/courses/CS106L/cs106l-assignments/assignment4 % ./main                                            
⏳ Installing autograder packages (this may take a few minutes)...
✅ Autograder packages installed.

Running test: Autograder Setup... 🧪                                             

Running test: tokenize... 🧪                                                     
🔎 tokenize called method find_all
🔎 tokenize called method std::transform
🔎 tokenize called method std::inserter
🔎 tokenize called method std::erase_if
🔎 tokenize has no for/while loops!
✅ tokenize passed! 🚀 

Running test: spellcheck... 🧪                                                   
🔎 spellcheck called method rv::filter
🔎 spellcheck called method rv::transform
🔎 spellcheck called method levenshtein
🔎 spellcheck has no for/while loops!
✅ spellcheck passed! 🚀 

Running test: Check submission has no helper functions... 🧪                     
✅ Check submission has no helper functions passed! 🚀 

Running test: Spellcheck... 🧪                                                   
🔎 (morrison).txt spellcheck matched solution!
🔎 tolstoy.txt spellcheck matched solution!
🔎 melville.txt spellcheck matched solution!
🔎 (kafka).txt spellcheck matched solution!
🔎 (marquez).txt spellcheck matched solution!
🔎 orwell.txt spellcheck matched solution!
🔎 gibberish.txt spellcheck matched solution!
✅ Spellcheck passed! 🚀 

🚀🚀🚀 Congratulations, your code passed all the autograder tests! 🚀🚀🚀        
```

