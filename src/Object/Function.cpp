#include "Function.h"
#include "Value.h"

namespace amalt {
	Function::Function(std::string n) : name(std::move(n)) {};

	RTFunction::RTFunction(std::string n = "<Lambda>") : Function(std::move(n)) {}

	Value RTFunction::fcall(RTuple args)
	{
		return Value(BOOLT, false);
	}

	NativeFunction::
		NativeFunction(std::string n = "<Unknown>", NativeInterface fp = nullptr):
		Function(std::move(n)), f(std::move(fp)) {}

	Value NativeFunction::fcall(RTuple args)
	{
		return f(args);
	}
}

