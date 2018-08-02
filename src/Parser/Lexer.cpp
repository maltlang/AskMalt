#include <vector>
#include "Parser/AST.h"

namespace amalt {
	std::vector<Token> Lexer(const String &src) {
		std::vector<Token> ts;
		const auto slen = src.length();
		String buffer;
		size_t line = 1, pos = 0;
		for (size_t index = 0; index < slen; index++) {
			switch (src[index]) {
			case '#':
				// 如果这里抛出字符串越界访问，就表明lexer失败了，告辞。直接抛出Runtime/LanguageException就行了
				for (index++;
					src[index] != '\n' &&
					src[index] != '\0' &&
					src[index] != EOF;
					index++);
				index++;
				line++;
				pos = 0;	
				break;
			case '"':
				if (buffer.length() != 0) {
					ts.push_back(Token(Token::SYM, buffer, line, pos));
					buffer.clear();
					line++;
				}
				index++;
				for (size_t o = index;; index++) {
					if (src[index] == L'\"' && src[index - 1] != L'\\') {
						pos++;
						break;
					} else if (src[index] == L'\n') {
						line++;
						pos = 0;
					}
					else {
						buffer += src[index];
						pos++;
					}
				}
				ts.push_back(Token(Token::STR, buffer, line, pos));
				buffer.clear();
				break;

			case '(':
			case ')':
			case '[':
			case ']':
			case '\'':
				if (buffer.length() != 0) {
					ts.push_back(Token(Token::SYM, buffer, line, pos));
					buffer.clear();
					pos++;
				}
				ts.push_back(Token((int)src[index], L"",line,pos));
				break;
			case '\n':
				line++;
				pos = 0;
			case '\0':
			case '\t':
			case EOF:
				if (buffer.length() != 0) {
					ts.push_back(Token(Token::SYM, buffer, line, pos));
					buffer.clear();
					pos++;
				}
				break;
			default:
				buffer += src[index];
				pos++;
				break;
			}
		}
		if (buffer.length() != 0) {
			ts.push_back(Token(Token::SYM, buffer, line, pos));
		}
		return ts;
	}
}
