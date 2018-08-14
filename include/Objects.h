#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "Predefined.h"
//#include "Mark.h"
#include "Value.h"

namespace amalt {

	class Value;
	//class String : public std::wstring {};
	//class Tuple : public std::vector<Value> {};
	//class Dict : public std::unordered_map<String, Value> {};

	class UserDatas {
	public:
		std::string type;
		virtual ~UserDatas() = 0;
	};
}