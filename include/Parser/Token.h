#pragma once

//#include <string>
#include <vector>
#include <memory>
#include "Objects.h"

namespace amalt {
	class Token {
	public:
		enum Type {
			LP = '(',
			RP = ')',
			LMP = '[',
			RMP = ']',
			QUO = '\'',

			//NUM = 'N',
			FLOAT = 'f',
			UINT = 'U',
			INT = 'I',
			STR = 'S',
			SYM = 's',
		};
		const Type tp;
		std::wstring exvalue;
		const size_t line, pos;

		Token(const Type t, std::wstring v, const size_t line, const size_t pos);

		bool typeEq(const Token &) const;
		bool operator==(const Token &) const;
		bool operator!=(const Token &) const;

		std::wstring toString() const;
	};
}