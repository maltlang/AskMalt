# AskMalt
The Ask Malt Programming Language

### Compiled：
Please use MSVC to compile core and extension on Windows.

Not compiled successfully in linux (怀疑因为g++不是最新的导致的问题，但不知道具体为啥，有知道的大佬麻烦帮我下（背锅

### Warnings:
- 一切不被认定为float/int/uint类型的atom字面量都会被认定为symbol
- 所有有副作用的函数或关键字都会在后边加上!，函数的定义是手动标记的，不排除以后加入强制检查，请谨记
- 还没有实现loop相关的谓词和函数（因为现在只需要一个最小的，能跑的东西）以后会加上

### FA&Q:
- When building with VisualStudio, Project Can only be an English Path (Because nijia only supports ASCII)
- Beta Version use std::shared_ptr<T> as memory manager （所以可能有循环引用的问题，在使用Mark<T>替换之前请务必不要造成大量循环引用）
