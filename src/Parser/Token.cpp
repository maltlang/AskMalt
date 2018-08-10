#include "Parser/Token.h"

namespace amalt {
	Token::Token(const Type t, std::wstring v, const size_t l, const size_t p) :
		tp(t), exvalue(std::move(v)), line(l), pos(p) {}

	bool Token::typeEq(const Token &o) const {
		return tp == o.tp;
	}

	bool Token::operator==(const Token & o) const
	{
		if (typeEq(o)) {
			return exvalue == o.exvalue;
		} else {
			return false;
		}
	}
	bool Token::operator!=(const Token & o) const
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
			s += L"string '";
			s += exvalue;
			s += L"'>";
			break;
		case FLOAT:
			s += L"float '";
			s += exvalue;
			s += L"'>";
			break;
		case UINT:
			s += L"uint '";
			s += exvalue;
			s += L"'>";
			break;
		case INT:
			s += L"int '";
			s += exvalue;
			s += L"'>";
			break;
		case SYM:
			s += L"symbol '";
			s += exvalue;
			s += L"'>";
			break;
		default:
			break;
		}
		return s;
	}
}