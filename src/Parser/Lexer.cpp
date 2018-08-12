#include <vector>
#include <regex>
#include "Parser/Token.h"

namespace amalt {

	static Token::Type Fk(const String& s) {
		std::wregex nr(L"(-|\\+)?[0-9]+(\\.)[0-9]+");
		if (std::regex_match(s, nr)) {
			return Token::FLOAT;
		}
		std::wregex ir(L"(-|\\+)?[0-9]+");
		if (std::regex_match(s, ir)) {
			if (s[0] == L'-' || s[0] == L'+') {
				return Token::INT;
			} else {
				return Token::UINT;
			}
		}
		return Token::SYM;
	}

	#define Uimmm					\
		if (buffer.length() != 0) {	\
			ts.push_back(Token(Fk(buffer), buffer, line, pos-buffer.size()));	\
			buffer.clear();			\
			pos++;					\
		}

	std::vector<Token> Lexer(const String &src, const bool is_clear_index = false) {
		std::vector<Token> ts;
		const auto slen = src.length();
		String buffer;
		static size_t line = 1, pos = 1;
		if (is_clear_index) {
			line = 1;
			pos = 1;
		}
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
				pos = 1;
				break;
			case '"':
				Uimmm
				index++;
				for (size_t o = index;; index++) {
					if (src[index] == L'\"' && src[index - 1] != L'\\') {
						pos++;
						break;
					} else if (src[index] == L'\n') {
						line++;
						pos = 1;
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
				Uimmm
				ts.push_back(Token(static_cast<Token::Type>(src[index]), L"",line,pos));
				pos++;
				break;
			case '\n':
				Uimmm
				line++;
				pos = 1;
				break;
			case '\0':
			case '\t':
			case ' ':
			case EOF:
				Uimmm
				break;
			default:
				buffer += src[index];
				pos++;
				break;
			}
		}
		if (buffer.length() != 0) {
			ts.push_back(Token(Fk(buffer), buffer, line, pos));
		}
		return ts;
	}
}
