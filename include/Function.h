#pragma once


#include <functional>
#include "Objects.h"
#include "Mark.h"
//#include "Function.h"

namespace amalt {
	class Value;

	class Function {
	public:
		std::string name;

		Function(std::string n);
		virtual Value fcall(Mark<Tuple>) = 0;
	};

	class Module;

	class RTFunction : Function {
	public:
		std::weak_ptr<Module> mod;

		RTFunction(std::string n);	//TODO:env
		Value fcall(Mark<Tuple>) override;
	};

	using NativeFunction = std::function<Value(Mark<Tuple>)>;

	class NativeInterface : Function {
	public:
		NativeFunction f;

		NativeInterface(std::string n, NativeFunction f);
		Value fcall(Mark<Tuple>) override;
	};
}