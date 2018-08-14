#include "Function.h"
#include "Value.h"

namespace amalt {
	Function::Function(std::string n) : name(std::move(n)) {};

	RTFunction::RTFunction(std::string n = "<Lambda>", AST e = AST(AST::NIL_, 0ll, 0, 0)) : Function(std::move(n)), expr(e) {}

	NativeFunction::
		NativeFunction(std::string n = "<Unknown>", NativeInterface fp = nullptr):
		Function(std::move(n)), f(std::move(fp)) {}

	Value NativeFunction::fcall(RTuple args)
	{
		return f(args);
	}
}

