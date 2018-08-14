#include "Parser/AST.h"
#include "Value.h"

namespace amalt {
	inline Value quote_eval(AST expr) {
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
			return Value(SYMBOLT, std::get<RString>(expr.expr));
		case AST::TUPLE: {
			auto tp = std::get<std::shared_ptr<TupleAst>>(expr.expr);
			auto t = std::make_shared<Tuple>(tp.get()->size());
			for (size_t i = 0; i < t.get()->size(); i++) {
				t.get()->operator[](i) = quote_eval(tp.get()->operator[](i));
			}
			return Value(TUPLET, t);
		}
		default:
			// 我估计这个throw永远不会触发——除非改AST的人作死
			throw;
		}
	}

	Value eval(AST expr) {
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
		case AST::QUOTE: {
			return quote_eval(std::get<std::shared_ptr<QuoteAst>>(expr.expr).get()->expr);
		}
		default:
			// 我估计这个throw永远不会触发——除非改AST的人作死
			throw;
		}
	}
}