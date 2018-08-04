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

	typedef std::variant<
		// atom
		bool,
		//char,
		ui64, i64, f64,
		// ref object
		Mark<String>,
		Mark<Tuple>,
		Mark<List>,
		Mark<Dict>,
		// function
		Mark<RTFunction>,
		std::shared_ptr<NativeFunction>,
		// userdata
		std::shared_ptr<UserDatas>
	> RValue;

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

		USERDATA,

		FUNCTIONT,
		NATIVE,
	};

	class Value {
	public:
		Type tp;
		RValue val;

		Value(Type t, RValue v) : tp(t), val(v) {}
		Value(Value &) = default;
	};
}