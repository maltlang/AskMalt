#pragma once

//#include <string>
#include <vector>
#include <memory>
#include "Objects.h"

namespace amalt {
	class Token {
		enum Type {
			LP = '(',
			RP = ')',
			LMP = '[',
			RMP = ']',
			QUO = '&',

			NUM = 'N',
			STR = 'S',
			SYM = 's',
		};
		std::string exvalue;

		Token(Type t, std::string v);
	};

	class AST {
	public:
		// 可能还会拓展
		enum Type {
			COND,
			QUOTE,
			FCALL,
			DEFUN,
		} type;

		const ui64 line, pos;

		AST(Type t, const ui64 l, const ui64 p) : type(t), line(l), pos(p) {}
		AST(AST &) = default;
		AST(AST &&) = default;
		//virtual Value eval() = 0;
	};

	class FCallAST : public AST {
	public:
		String fname;
		std::vector<AST> args;

		FCallAST(String n, const ui64 l, const ui64 p, std::vector<AST> a):
			AST(FCALL, l, p), fname(std::move(n)), args(std::move(a)) {}
	};

	class DefunAST : public AST {
	public:
		String fname;
		std::vector<String> args;

	};
}