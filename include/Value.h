#pragma once

#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <variant>
#include <memory>
#include "Predefined.h"
//#include "Mark.h"
//#include "Objects.h"
//#include "Function.h"

namespace amalt {
	///*
	class Value;

	using String = std::wstring;
	using Tuple = std::vector<Value>;
	using List = std::list<Value>;
	using Dict = std::unordered_map<String, Value>;
	//class String;
	//class Tuple;
	//class Dict;
	class Function;
	class RTFunction;
	class NativeFunction;
	class UserDatas;
	//*/
	typedef std::shared_ptr<String> RString;
	typedef std::shared_ptr<Tuple> RTuple;
	typedef std::shared_ptr<List> RList;
	typedef std::shared_ptr<Dict> RDict;
	typedef std::shared_ptr<UserDatas> RUserDatas;
	using RRTFunction = std::shared_ptr<RTFunction>;
	using RNativeFunction = std::shared_ptr<NativeFunction>;

	using RValue = std::variant<
		// atom
		bool,
		wchar_t,
		ui64, i64, f64,
		// ref object
		RString,
		RTuple,
		RList,
		RDict,
		RRTFunction,
		RNativeFunction,
		// userdata
		RUserDatas
	>;

	enum Type {
		NIL,

		BOOLT,
		CHART,
		INTT,
		UINTT,
		FLOATT,

		STRINGT,
		SYMBOLT,
		TUPLET,
		LISTT,
		DICTT,
		OBJECTT,

		USERDATA,

		FUNCTIONT,
		NATIVE,
	};

	class Value {
	public:
		Type tp;
		RValue val;

		Value() : tp(NIL), val(false) {}
		Value(Type t, RValue v) : tp(t), val(std::move(v)) {}
		Value(Value &) = default;
	};
}