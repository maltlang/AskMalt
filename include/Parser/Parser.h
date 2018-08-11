#pragma once

#include "Parser/AST.h"

namespace amalt {
	using ResAST = std::variant<Token, AST>;	// err, ok

	ResAST Parser(std::vector<Token> &tf, const size_t idx = 0);
	inline ResAST TupleParser(std::vector<Token> &tf, const size_t idx);
	inline ResAST ListParser(std::vector<Token> &tf, const size_t idx);
}