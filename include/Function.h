#pragma once


#include <functional>
#include <memory>
//#include "Objects.h"
#include "Mark.h"
#include "Parser/AST.h"
//#include "Function.h"

namespace amalt {
	class Value;
	// class Module;
	// class Dict;
	//using String = std::wstring;
	//using Dict = std::unordered_map<String, Value>;

	class Function {
	public:
		std::string name;
		
		explicit Function(std::string n);
	};

	class Module {
	public:
		String path;
		std::shared_ptr<Dict> vartable;
		AST expr;

		Module(String p, AST e);
	};

	class RTFunction : Function {
	public:
		std::weak_ptr<Module> mod;
		std::shared_ptr<Dict> env;
		std::vector<String> argstable;
		AST expr;
		RTFunction(std::weak_ptr<Module> m,
			std::string n, AST a, std::shared_ptr<Dict> e, std::vector<String> at);	//TODO:env
	};

	using NativeInterface = std::function<Value(RTuple)>;

	class NativeFunction : Function {
	public:
		NativeInterface f;

		NativeFunction(std::string n, NativeInterface f);
		Value fcall(RTuple);
	};
}