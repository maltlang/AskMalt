#pragma once
#include "Parser/AST.h"
#include "Function.h"
#include "FunctionContext.h"
#include <stack>

namespace amalt {
	class InterpreterContext {
	public:
		String path;
		std::unordered_map<String, std::shared_ptr<Module>> modtable;
		std::stack<FunctionContext> framestack;
		/// Module &main; //modtable[L"--main--"]
		std::shared_ptr<Module> rmod;

		InterpreterContext() = default;
		InterpreterContext(int argc, char **argv);
		~InterpreterContext() = default;
		Value eval(AST expr);
		//void run();
	};
}