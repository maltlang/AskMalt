#pragma once
#include <exception>
#include "Objects.h"

namespace amalt {

	class ParserException : std::exception {
	public:
		const String info;
		const ui64 line, pos;

		ParserException(const String i, const ui64 l, const ui64 p);
		const String toString() const;
	};

	class RuntimeException : std::exception {
	public:
		const String name;
		const String info;

		RuntimeException(const String n, const String i);
		bool operator==(const RuntimeException &re) const;
		bool operator!=(const RuntimeException &re) const;
		const String toString() const;
	};
}