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
		Type tp;
		std::wstring exvalue;
		size_t line, pos;

		Token(Type t, std::wstring v, size_t line, size_t pos);

		bool typeEq(const Token &) const;
		bool operator==(const Token &) const;
		bool operator!=(const Token &) const;

		std::wstring toString() const;
	};


	class AST {
	public:
		enum Type {
			//OBJ,
			LET,
			IF_,
			COND,
			MATCH,
			DEFUN,
			QUOTE,
			FCALL,
			LAMBDA,
		} type;

		const ui64 line, pos;

		AST(Type t, const ui64 l, const ui64 p) : type(t), line(l), pos(p) {}
		AST(AST &) = default;
		AST(AST &&) = default;
		//virtual Value eval() = 0;
	};

	class FCallAST : public AST {
	public:
		std::vector<AST> args;

		FCallAST(const ui64 l, const ui64 p, std::vector<AST> a):
			AST(FCALL, l, p), args(std::move(a)) {}
	};

	class DefunAST : public AST {
	public:
		String fname;
		std::vector<String> args;

	};
}