#include "Parser/Token.h"
#include "Parser/AST.h"
#include "Parser/Parser.h"
#include "Exception.h"

namespace amalt {
	ResAST Parser(std::vector<Token> &tf, size_t &idx) {
		auto e = tf.at(idx);
		size_t rsz = idx;
		try
		{
			if (e.tp == Token::INT) {
				return AST(AST::INT, AST::ae(std::stoll(e.exvalue)), e.line, e.pos);
			}
			else if (e.tp == Token::UINT) {
				return AST(AST::UINT, AST::ae(std::stoull(e.exvalue)), e.line, e.pos);
			}
			else if (e.tp == Token::FLOAT) {
				return AST(AST::FLOAT, AST::ae(std::stod(e.exvalue)), e.line, e.pos);
			}
			else if (e.tp == Token::STR) {
				return AST(AST::STRING, AST::ae(std::make_shared<String>(e.exvalue)), e.line, e.pos);
			}
			else if (e.tp == Token::SYM) {
				return AST(AST::SYMBOL, AST::ae(std::make_shared<String>(e.exvalue)), e.line, e.pos);
			}
			else if (e.tp == Token::QUO) {
				auto r = Parser(tf, idx);
				if (std::get_if<AST>(&r)) {
					return AST(AST::QUOTE, std::make_shared<QuoteAst>(std::get<AST>(r)), e.line, e.pos);
				}
				else {
					return r;
				}
			}
			else {}

			auto r0 = TupleParser(tf, idx);
			if (std::get_if<AST>(&r0)) {
				return r0;
			} else {
				idx = rsz;
			}

			auto r1 = ListParser(tf, idx);
			if (std::get_if<AST>(&r1)) {
				return r1;
			} else {
				idx = rsz;
			}

			return e;
		}
		catch (const std::out_of_range&)
		{
			throw ParserException(L"表达式不完整", e.line, e.pos);
		}
	}

	inline ResAST TupleParser(std::vector<Token> &tf, size_t &idx) {
		auto first = tf.at(idx);
		size_t rsz = idx;
		if (first.tp != Token::LMP) {
			return tf[idx];
		}
		TupleAst r;
		try
		{
			for (idx++; ; idx++) {
				if (tf.at(idx).tp == Token::RMP) {
					break;
				}
				auto a = Parser(tf, idx);
				if (!std::get_if<AST>(&a)) {
					idx = rsz;
					return a;
				}
				r.push_back(std::get<AST>(a));
			}
		}
		catch (const std::out_of_range&)
		{
			throw ParserException(L"表达式不完整", tf[idx-1].line, tf[idx - 1].pos);
		}
		return AST(AST::TUPLE, std::make_shared<TupleAst>(r), first.line, first.pos);
	}

	inline ResAST ListParser(std::vector<Token> &tf, size_t &idx) {
		return tf.at(idx);
	}

}