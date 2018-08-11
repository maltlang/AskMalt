#include "Exception.h"
#include <cstdlib>

namespace amalt {
	ParserException::
		ParserException(const String i, const ui64 l, const ui64 p)
		: info(i), line(l), pos(p) {}
	const String ParserException::toString() const
	{
		return info + String(std::to_wstring(line)) + String(L":") + String(std::to_wstring(pos));
	}
	RuntimeException::RuntimeException(String n, String i) : name(n), info(i) {}
	bool RuntimeException::operator==(const RuntimeException &re) const {
		return name == re.name;
	}
	bool RuntimeException::operator!=(const RuntimeException &re) const {
		return name != re.name;
	}
	const String RuntimeException::toString() const
	{
		return name + String(L":") + info;
	}
}