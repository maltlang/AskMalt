#pragma once

#include <variant>
#include <memory>
#include "Objects.h"

namespace amalt {

	class TupleAst;
	class QuoteAst;
	class LetAst;
	class CondAst;
	class MatchAst;
	class FCallAst;
	class DefunAst;

	class AST {
	public:
		enum Type {
			NIL_,

			INT,
			UINT,
			FLOAT,
			STRING,
			SYMBOL,

			TUPLE,

			//QUOTE,

			LET,
			COND,
			MATCH,
			FCALL,
			DEFUN,
			//LAMBDA_,
		};
		const Type type;

		using ae = std::variant <
			//base data
			i64,
			ui64,
			f64,
			RString,
			// ast struct
			//std::shared_ptr<QuoteAst>,
			std::shared_ptr<TupleAst>,
			std::shared_ptr<LetAst>,
			std::shared_ptr<CondAst>,
			std::shared_ptr<MatchAst>,
			std::shared_ptr<FCallAst>,
			std::shared_ptr<DefunAst>
		>;
		ae expr;
		const ui64 line, pos;

		AST(const Type t,ae e, const ui64 l, const ui64 p);
		//AST();
		AST(const AST &o) = default;
		AST(AST &&) = default;
		//AST operator=(const AST&);
		String toString();
	};

	class TupleAst : public std::vector<AST> {
	public:
		String toString();
	};
	class QuoteAst {
	public:
		AST expr;
		String toString();
		QuoteAst(AST e);
	};

	class DefaultAst {
	public:
		DefaultAst() = default;
		DefaultAst(const DefaultAst &) = default;
		DefaultAst(DefaultAst &&) = default;
	};

	class LetAst : DefaultAst {
	public:
		AST nexpr;
		AST vexpr;
		LetAst(AST n, AST e);
		String toString();
	};

	class CondAst : DefaultAst {
	public:
		std::vector<AST> exprlist;
		CondAst() = default;
		CondAst(std::vector<AST> &el);
		String toString();
	};

	class MatchAst : DefaultAst {
	public:
		AST expr;
		std::vector<AST> exprlist;

		MatchAst(AST e);
		MatchAst(AST e, std::vector<AST> &el);
		String toString();
	};

	class FCallAst : DefaultAst {
	public:
		std::vector<AST> exprlist;

		FCallAst() = default;
		FCallAst(std::vector<AST> &el);
		String toString();
	};

	class DefunAst : DefaultAst {
	public:
		RString name;
		std::shared_ptr<TupleAst> argsnames;
		// expend
		std::vector<AST> exprlist;

		DefunAst(RString n, std::shared_ptr<TupleAst> &an, std::vector<AST> &el);
		String toString();
	};
}