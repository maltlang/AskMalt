#pragma once


#include <functional>
#include <memory>
//#include "Objects.h"
#include "Mark.h"
#include "Parser/AST.h"
//#include "Function.h"

namespace amalt {
	class Value;

	class Function {
	public:
		std::string name;

		explicit Function(std::string n);
	};

	class Module;

	class RTFunction : Function {
	public:
		std::weak_ptr<Module> mod;
		std::shared_ptr<RTFunction> env;
		AST expr;
		explicit RTFunction(std::string n, AST e);	//TODO:env
	};

	using NativeInterface = std::function<Value(RTuple)>;

	class NativeFunction : Function {
	public:
		NativeInterface f;

		NativeFunction(std::string n, NativeInterface f);
		Value fcall(RTuple);
	};
}