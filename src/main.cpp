#include <iostream>
#include <fstream>
#include "Parser/Lexer.h"
#include "Parser/Parser.h"
#include "Exception.h"
#include "FunctionContext.h"

using namespace std;
using namespace amalt;

String exithelp(L"Please use Ctrl-c to exit repl.");

int main(int argc, char **argv) {
	//setlocale(LC_CTYPE, "C");
	//wcout.imbue(locale("chs"));
	wifstream ff(L"H:\\fuck.txt", ios::in);// , ios::in);
	String src;
	for (;!ff.eof();) {
		String buf;
		getline(ff, buf);
		src += buf;
		src += L'\n';
	}
	wcout << L"src:\n" << src << endl;
	size_t i = 0;
	auto ts = Lexer(src);
	wcout << L"tokenFlow:" << endl;
	for (auto &i : ts) {
		wcout << i.toString() << i.line << ":" << i.pos << endl;
	}
	wcout << L"AST:" << endl;
	try
	{
		for (; i < ts.size();) {
			auto rast = Parser(ts, i);
			if (std::get_if<AST>(&rast)) {
				wcout << std::get<AST>(rast).toString() << endl;
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
	for (;;);
	return 0;
}