#include <iostream>
#include "./Parser/Lexer.h"

using namespace std;
using namespace amalt;

String copys(L"Please use Ctrl-c to quit repl.");

int main(int argc, char **argv) {
	String src;
	for (;;) {
		wcin >> src;
		//src += L'\n';
		auto ts = Lexer(src);
		for (auto &i : ts) {
			wcout << i.toString() << endl;
		}
	}
	//for (;;)
	return 0;
}