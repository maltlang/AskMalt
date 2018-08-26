#pragma once
#include "Parser/AST.h"
#include "Function.h"
#include "FunctionContext.h"
#include <stack>

namespace amalt {
	class InterpreterContext {
	public:
		String path;
		std::unordered_map<String, Module> modtable;
		std::stack<FunctionContext> framestack;

		InterpreterContext() = default;
		InterpreterContext(int argc, char **argv);
		InterpreterContext() = default;
		friend Value expr(AST a);
	};
}