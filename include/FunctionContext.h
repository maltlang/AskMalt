#pragma once

#include "Value.h"
#include "Function.h"
#include "Exception.h"

namespace amalt {
	class FunctionContext {
	public:
		RRTFunction funptr;
		RDict vartable;

		FunctionContext(RRTFunction fp, RTuple args) : funptr(fp), vartable(std::make_shared<Dict>()) {
			// non args nullptr assert
			if (args->size() != funptr->argstable.size()) {
				throw RuntimeException(L"ArgsLengthError", L"Function call Args length error");
			}
			for (size_t i = 0; i < args->size(); i++) {
				vartable->operator[](funptr->argstable[i]) = args->operator[](i);
			}
		};
	};
}