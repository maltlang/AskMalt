# AskMalt
The Ask Malt Programming Language

## Compiled：
Use Visual Studio (2017) Build

Not compiled successfully in linux (怀疑因为g++不是最新的导致的问题，但不知道具体为啥，有知道的大佬麻烦帮我下（背锅

## Warnings:
- 一切不被认定为float/int/uint类型的atom字面量都会被认定为symbol
- 有时候UInt(unsigned long long)会用作很脏的功能——储存地址

### FA&Q:
- When building with VisualStudio, Project Can only be an English Path (Because nijia only supports ASCII)
- Beta Version use std::shared_ptr<T> as memory manager （所以可能有循环引用的问题，在使用Mark<T>替换之前请务必不要造成大量循环引用）
