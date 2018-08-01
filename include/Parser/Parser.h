#pragma once

#include <vector>
#include "Parser/AST.h"

namespace amalt {
	std::vector<Token> Lexer(const String &src);
}
