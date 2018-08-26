#include "InterpreterContext.h"
#include <iostream>

namespace amalt {
	InterpreterContext::InterpreterContext(int argc, char ** argv) {
		// 暂时的。。。暂时的
		if (argc != 2) {
			throw RuntimeException(L"OptionError", L"Option error");
		}
	}

	Value InterpreterContext::eval(AST expr) {
		switch (expr.type)
		{
		case AST::NIL_:
			return Value(NIL, false);
		case AST::INT:
			return Value(INTT, std::get<i64>(expr.expr));
		case AST::UINT:
			return Value(UINTT, std::get<ui64>(expr.expr));
		case AST::FLOAT:
			return Value(FLOATT, std::get<f64>(expr.expr));
		case AST::STRING:
			return Value(STRINGT, std::get<RString>(expr.expr));
		case AST::SYMBOL:
			// load_name
			break;
		case AST::TUPLE: {
			auto tp = std::get<std::shared_ptr<TupleAst>>(expr.expr);
			auto t = std::make_shared<Tuple>(tp.get()->size());
			for (size_t i = 0; i < t.get()->size(); i++) {
				t.get()->operator[](i) = eval(tp.get()->operator[](i));
			}
			return Value(TUPLET, t);
		}
		/*
		case AST::QUOTE: {

			//return quote_eval(std::get<std::shared_ptr<QuoteAst>>(expr.expr).get()->expr);
		}
		*/
		case AST::LET: {
			// 还不支持元组匹配，因为这玩意已经把我脑袋弄晕了，能跑就行，mmp
			auto lt = std::get<std::shared_ptr<LetAst>>(expr.expr);
			RString name;
			if (lt->nexpr.type != AST::SYMBOL) {
				name = std::get<RString>(lt->nexpr.expr);
			}
			else {
				throw RuntimeException(L"EvalError", L"Let args non symbol");
			}
			// 对value处求值
			auto r = eval(lt->vexpr);
			// 如果栈大小为零，就表示处于模块顶层，直接赋值local，如果不是，就在函数上下文里边操作
			if (framestack.size() == 0) {
				rmod->vartable->operator[](*name) = r;
			}
			else {
				framestack.top().vartable->operator[](*name) = r;
			}
			return r;
		}
		default:
			// 我估计这个throw永远不会触发——除非改AST的人作死
			throw;
		}
	}
}