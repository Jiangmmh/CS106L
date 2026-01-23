#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>
#include <regex>
#include <ranges>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

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

std::set<Misspelling> spellcheck(const Corpus &source, const Dictionary &dictionary)
{
  namespace rv = std::ranges::views;
  std::set<Misspelling> results;

  // tokens that are not empty and not in the dictionary
  auto misspelled_tokens = source | rv::filter([&](const Token &t) {
    return !t.content.empty() && dictionary.find(t.content) == dictionary.end();
  });

  // for each misspelled token, collect one-edit-away suggestions
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
    // drop those with no suggestions
    | rv::filter([](const Misspelling &m) { return !m.suggestions.empty(); });
  
  results = std::set<Misspelling>(with_suggestions.begin(), with_suggestions.end());
  return results;
}

#include "utils.cpp"