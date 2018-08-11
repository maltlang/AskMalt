#include <iostream>
#include "Parser/Lexer.h"

using namespace std;
using namespace amalt;

String exithelp(L"Please use Ctrl-c to exit repl.");

int main(int argc, char **argv) {
	String src;
	for (;;) {
		getline(wcin, src);
		src += L'\n';
		auto ts = Lexer(src);
		for (auto &i : ts) {
			wcout << i.toString() << i.line << ":" << i.pos << endl;
		}
	}
	return 0;
}