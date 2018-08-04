#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "Predefined.h"
#include "Mark.h"

namespace amalt {

	class Value;

	using String = std::wstring;
	using Tuple = std::vector<Value>;
	using Dict = std::unordered_map<String, Value>;
	//class String : public std::wstring {};
	//class Tuple : public std::vector<Value> {};
	//class Dict : public std::unordered_map<String, Value> {};

	class List {
	public:
		const ui64 len;
		const Mark<Value> car, cdr;

		List(Mark<Value> a, Mark<Value> d);
	};

	class UserDatas {
	public:
		std::string type;
		virtual ~UserDatas() = 0;
	};
}