#include "Parser/Token.h"
#include "Parser/AST.h"

namespace amalt {
	using ResAST = std::variant<bool, AST>;

	inline ResAST TupleParser(std::vector<Token> tf, const size_t idx);

	ResAST Parser(std::vector<Token> &tf, const size_t idx = 0) {
		auto e = tf[idx];
		if (e.tp == Token::INT) {
			return AST(AST::INT, AST::ae(std::stoll(e.exvalue)), e.line, e.pos);
		}
		else if (e.tp == Token::UINT) {
			return AST(AST::UINT, AST::ae(std::stoull(e.exvalue)), e.line, e.pos);
		}
		else if (e.tp == Token::FLOAT) {
			return AST(AST::FLOAT, AST::ae(std::stod(e.exvalue)), e.line, e.pos);
		}
		else if (e.tp == Token::STR) {return AST(AST::FLOAT, AST::ae(std::stod(e.exvalue)), e.line, e.pos);
			return AST(AST::STRING, AST::ae(std::make_shared<String>(e.exvalue)), e.line, e.pos);
		} else if (e.tp == Token::SYM) {
			return AST(AST::SYMBOL, AST::ae(std::make_shared<String>(e.exvalue)), e.line, e.pos);
		} else if (e.tp == Token::QUO) {
			auto r = Parser(tf, idx + 1);
			if (std::get_if<AST>(&r)) {
				return r;
			}
			else {
				return AST(AST::QUOTE, std::move(std::get<AST>(r).expr), e.line, e.pos);
			}
		} else if (e.tp == Token::LMP) {
			// tuple
			auto r = TupleParser(tf, idx + 1);

		}
		//else if (e.tp) {

		//}
		else {

		}
	}

	inline ResAST TupleParser(std::vector<Token> tf, const size_t idx) {
		return ResAST(false);
	}

}