#include "Parser/AST.h"

namespace amalt {
	Token::Token(int t, std::wstring v, size_t l, size_t p) :
		tp(t), exvalue(std::move(v)), line(l), pos(p) {}

	bool Token::operator==(const Token & o)
	{
		return tp == o.tp;
	}
	bool Token::operator!=(const Token & o)
	{
		return tp != o.tp;
	}
	std::wstring Token::toString() const
	{
		std::wstring s = L"<";
		switch (tp)
		{
		case '(':
		case ')':
		case '[':
		case ']':
		case '\'':
			s += tp;
			s += L'>';
			break;
		case STR:
			s += L"String '";
			s += exvalue;
			s += L"'>";
			break;
		case NUM:
			s += L"Number '";
			s += exvalue;
			s += L"'>";
			break;
		case SYM:
			s += L"Symbol '";
			s += exvalue;
			s += L"'>";
			break;
		default:
			break;
		}
		return s;
	}
}