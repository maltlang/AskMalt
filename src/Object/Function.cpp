#include "Function.h"
#include "Value.h"

namespace amalt {
	Function::Function(std::string n) : name(std::move(n)) {};

	RTFunction::RTFunction(std::string n = "<Lambda>") : Function(std::move(n)) {}

	Value RTFunction::fcall(Mark<Tuple> args)
	{
		return Value(BOOLT, false);
	}

	NativeInterface::
		NativeInterface(std::string n = "<Unknown>", NativeFunction fp = nullptr):
		Function(std::move(n)), f(fp) {}

	Value NativeInterface::fcall(Mark<Tuple> args)
	{
		return f(args);
	}
}

