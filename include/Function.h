#pragma once


#include <functional>
#include "Objects.h"
//#include "Function.h"

namespace amalt {
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
		virtual Value fcall(Mark<Tuple>);
	};

	typedef std::function<Value(Mark<Tuple>)> NativeFunction;

	class NativeInterface : Function {
	public:
		NativeFunction f;

		NativeInterface(std::string n, NativeFunction f);
		virtual Value fcall(Mark<Tuple>);
	};
}