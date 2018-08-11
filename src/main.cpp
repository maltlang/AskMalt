#include <iostream>
#include "Parser/Lexer.h"
#include "Parser/Parser.h"
#include "Exception.h"

using namespace std;
using namespace amalt;

String exithelp(L"Please use Ctrl-c to exit repl.");

int main(int argc, char **argv) {
	String src;
	for (;;) {
	try
	{
		getline(wcin, src);
		src += L'\n';
		auto ts = Lexer(src);
		auto rast = Parser(ts);
		if (std::get_if<AST>(&rast)) {
			wcout << std::get<AST>(rast).toString() << endl;
		}
		else {
			wcerr << L"***ParserError " << std::get<Token>(rast).line << L":" << std::get<Token>(rast).pos << endl;
		}
	} catch (const std::out_of_range&) {
		wcerr << L"表达式不完整" << endl;
	} catch (const ParserException&e) {
		wcerr << e.toString() << endl;
	}
	}
	return 0;
}