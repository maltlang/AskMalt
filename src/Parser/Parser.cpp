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
				idx++;
				return AST(AST::INT, AST::ae(std::stoll(e.exvalue)), e.line, e.pos);
			}
			else if (e.tp == Token::UINT) {
				idx++;
				return AST(AST::UINT, AST::ae(std::stoull(e.exvalue)), e.line, e.pos);
			}
			else if (e.tp == Token::FLOAT) {
				idx++;
				return AST(AST::FLOAT, AST::ae(std::stod(e.exvalue)), e.line, e.pos);
			}
			else if (e.tp == Token::STR) {
				idx++;
				return AST(AST::STRING, AST::ae(std::make_shared<String>(e.exvalue)), e.line, e.pos);
			}
			else if (e.tp == Token::SYM) {
				idx++;
				return AST(AST::SYMBOL, AST::ae(std::make_shared<String>(e.exvalue)), e.line, e.pos);
			}
			else if (e.tp == Token::QUO) {
				idx++;
				auto r = Parser(tf, idx);
				if (std::get_if<AST>(&r)) {
					//idx++;
					return AST(AST::QUOTE, std::make_shared<QuoteAst>(std::get<AST>(r)), e.line, e.pos);
				}
				else {
					return r;
				}
			}
			else {}

			auto r0 = TupleParser(tf, idx);
			if (std::get_if<AST>(&r0)) {
				//idx++;
				return r0;
			} else {
				idx = rsz;
			}

			auto r1 = ListParser(tf, idx);
			if (std::get_if<AST>(&r1)) {
				idx++;
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
			for (idx++; ; ) {
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
			throw ParserException(L"表达式不完整", tf[idx-1].line, tf[idx-1].pos);
		}
		return AST(AST::TUPLE, std::make_shared<TupleAst>(r), first.line, first.pos);
	}

	inline ResAST ListParser(std::vector<Token> &tf, size_t &idx) {
		auto first = tf.at(idx);
		size_t rsz = idx;
		if (first.tp != Token::LP) {
			return tf[idx];
		}
		idx++;
		auto em = idx;
		try
		{
			auto r = tf.at(idx);
			if (r.tp == Token::RP) {
				return AST(AST::NIL_, ui64(0), first.line, first.pos);
			}
			if (r == Token(Token::SYM, L"\\", 0, 0)) {
				// lambda
			}
			if (r == Token(Token::SYM, L"fun", 0, 0)) {
				// defun
			}
			if (r == Token(Token::SYM, L"let", 0, 0)) {
				// let
				idx++;
				auto a = Parser(tf, idx);
				if (!std::get_if<AST>(&a)) {
					idx = em;
					goto letend;
				}
				auto a1 = Parser(tf, idx);
				if (!std::get_if<AST>(&a1)) {
					idx = em;
					goto letend;
				}
				if (tf.at(idx).tp == Token::RP) {
					return AST(AST::LET, std::make_shared<LetAst>(std::get<AST>(a), std::get<AST>(a1)), first.line, first.pos);
				} else {
					idx = em;
					goto letend;
				}
			}
		letend:
			if (r == Token(Token::SYM, L"cond", 0, 0)) {
				// cond
				auto r = std::make_shared<CondAst>();
				//std::vector<std::shared_ptr<TupleAst>> r;
				for (idx++; ; idx++) {
					if (tf.at(idx).tp == Token::RP) {
						break;
					}
					auto a = TupleParser(tf, idx);
					if (!std::get_if<AST>(&a)) {
						idx = em;
						goto condend;
					}
					r.get()->exprlist.push_back(std::get<std::shared_ptr<TupleAst>>(std::get<AST>(a).expr));
				}
				return AST(AST::COND, r, first.line, first.pos);
			}
			condend:
			if (r == Token(Token::STR, L"match", 0, 0)) {
				// match
			}
			// fcall
			return r;
		}
		catch (const std::out_of_range&)
		{
			throw ParserException(L"表达式不完整", tf[idx - 1].line, tf[idx - 1].pos);
		}
		//return AST(AST::TUPLE, std::make_shared<TupleAst>(r), first.line, first.pos);
	}



}