#include <iostream>
#include "Parser/Lexer.h"
#include "Parser/Parser.h"
#include "Exception.h"

using namespace std;
using namespace amalt;

String exithelp(L"Please use Ctrl-c to exit repl.");

int main(int argc, char **argv) {
	setlocale(LC_CTYPE, "C");
	wcout.imbue(locale("chs"));
	for (;;) {
		String src;
		size_t i = 0;
		getline(wcin, src);
		src += L'\n';
		auto ts = Lexer(src);
		try
		{
			for (; i < ts.size();) {
				auto rast = Parser(ts, i);
				if (std::get_if<AST>(&rast)) {
					wcout << std::get<AST>(rast).toString() << endl;
					i++;
				}
				else {
					throw ParserException(L"表达式不完整", std::get<Token>(rast).line, std::get<Token>(rast).pos);
				}
			}
		}
		catch (std::out_of_range&) {
			wcout << "表达式不完整" << endl;
		}
		catch (ParserException&e) {
			wcout << e.toString() << endl;
		}
	}
//		for (;;);
	return 0;
}