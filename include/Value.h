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
		//Mark<String>,
		//Mark<Tuple>,
		//Mark<List>,
		//Mark<Dict>,
		// function
		//Mark<RTFunction>,
		std::shared_ptr<String>,
		std::shared_ptr<Tuple>,
		std::shared_ptr<List>,
		std::shared_ptr<Dict>,
		std::shared_ptr<RTFunction>,
		std::shared_ptr<NativeInterface>,
		// userdata
		std::shared_ptr<UserDatas>
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