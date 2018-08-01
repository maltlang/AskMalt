#include <iostream>
#include "./Parser/Lexer.h"

using namespace std;
using namespace amalt;

int main(int argc, char **argv) {
	String src;
	for (;;) {
		wcin >> src;
		auto ts = Lexer(src);
		for (auto &i : ts) {
			wcout << i.toString() << endl;
		}
	}
	//for (;;)
	return 0;
}