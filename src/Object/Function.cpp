#include "..\include\Function.h"

namespace amalt {
	Function::Function(std::string n) : name(n) {};

	RTFunction::RTFunction(std::string n = "<Lambda>") : Function(n) {}

	Value RTFunction::fcall(Mark<Tuple> args)
	{
		return Value(BOOLT, false);
	}

	NativeInterface::
		NativeInterface(std::string n = "<Unknown>", std::function<Value(Mark<Tuple>)> fp = nullptr):
		Function(n), f(fp) {}

	Value NativeInterface::fcall(Mark<Tuple> args)
	{
		return f(args);
	}
}

