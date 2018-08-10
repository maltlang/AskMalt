#pragma once


#include <functional>
#include <memory>
#include "Objects.h"
#include "Mark.h"
//#include "Function.h"

namespace amalt {
	class Value;

	class Function {
	public:
		std::string name;

		explicit Function(std::string n);
		virtual Value fcall(RTuple) = 0;
	};

	class Module;

	class RTFunction : Function {
	public:
		std::weak_ptr<Module> mod;

		explicit RTFunction(std::string n);	//TODO:env
		Value fcall(RTuple) override;
	};

	using NativeInterface = std::function<Value(RTuple)>;

	class NativeFunction : Function {
	public:
		NativeInterface f;

		NativeFunction(std::string n, NativeInterface f);
		Value fcall(RTuple) override;
	};

	using RRTFunction = std::shared_ptr<RTFunction>;
	using RNativeInterface = std::shared_ptr<NativeInterface>;
}