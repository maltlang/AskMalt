#pragma once

#include <vector>
#include "Parser/Token.h"

namespace amalt {
	std::vector<Token> Lexer(const String &src, const bool is_clear_index = false);
}
