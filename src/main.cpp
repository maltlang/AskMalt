#include "Value.h"
using namespace amalt;
#include <variant>

#include "./Parser/AST.h"

int main(int argc, char **argv) {
	auto m = Value(BOOLT, false);
	std::variant<int, float> w, v;
	v = 12;
	w = v;
	return 0;
}