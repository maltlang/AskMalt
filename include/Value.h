#pragma once

#include <variant>
#include <memory>
#include "Predefined.h"
#include "Mark.h"
#include "Objects.h"
#include "Function.h"

namespace amalt {
	/*
	class String;
	class Tuple;
	class Dict;
	class List;
	class Function;
	class RTFunction;
	class NativeFunction;
	class UserDatas;
	*/

	using RValue = std::variant<
		// atom
		bool,
		//wchar_t,	// 只有娘炮才用wchar_t，真男人只用wString
		ui64, i64, f64,
		// ref object
		RString,
		RTuple,
		RList,
		RDict,
		RRTFunction,
		RNativeInterface,
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

		Value(Type t, RValue v) : tp(t), val(std::move(v)) {}
		Value(Value &) = default;
	};
}