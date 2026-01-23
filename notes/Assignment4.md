实验指导：https://github.com/cs106l/cs106l-assignments/blob/main/assignment4/README.md

该实验要求实现一个程序，其功能类似Unix中的Ispell，用于拼写的检查并推荐可能的替代。首先会提供一个字典文件，其中包含了全部的正确拼写的单词，用户输入的单词存在拼写错误意味着这个词在字典文件不存在，推荐词的依据来自Damerau-Levenshtein距离（衡量的是需要多少次编辑才能使两个词相同）。启动代码中提供了大部分的实现，需要我们实现的只有`tokenize`和`spellcheck`这两个函数，要求不能在代码中使用for/while循环，`tokenize`要使用传统的STL算法实现，而`spellcheck`要使用新的range库实现。