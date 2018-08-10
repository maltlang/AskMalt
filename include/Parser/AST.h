#pragma once

#include <variant>
#include <memory>
#include "Objects.h"

namespace amalt {

	class TupleAst;
	class QuoteAst;
	class LetAst;

	class AST {
	public:
		enum Type {
			//NIL_,

			INT,
			UINT,
			FLOAT,
			STRING,
			SYMBOL,

			TUPLE,

			QUOTE,

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

			std::unique_ptr<QuoteAst>,
			std::unique_ptr<TupleAst>,
			std::unique_ptr<LetAst>

		>;
		ae expr;
		const ui64 line, pos;

		AST(const Type t,ae e, const ui64 l, const ui64 p);
		AST(const AST &) = default;
		AST(AST &&) = default;
	};

	class TupleAst : public std::vector<AST> {};
	class QuoteAst : public AST {};

	class DefaultAst {
	public:
		DefaultAst() = default;
		DefaultAst(const DefaultAst &) = default;
		DefaultAst(DefaultAst &&) = default;
	};

	class LetAst : DefaultAst {
	public:
		const RString name;
		AST expr;
		LetAst(const RString n, AST e);
	};

	class CondAst : DefaultAst {
	public:
		std::vector<std::tuple<AST, AST>> exprlist;

		CondAst(std::vector<std::tuple<AST, AST>> &el);
	};

	class MatchAst : DefaultAst {
	public:
		AST expr;
		std::vector<std::tuple<AST, AST>> exprlist;

		MatchAst(AST e, std::vector<std::tuple<AST, AST>> &el);
	};

	class FCallAst : DefaultAst {
	public:
		std::vector<std::tuple<AST, AST>> exprlist;

		FCallAst(std::vector<std::tuple<AST, AST>> &el);
	};

	class DefunAst : DefaultAst {
		const RString name;
		const std::vector<RString> argsnames;
		// expend
		std::vector<AST> exprlist;

		DefunAst(const RString n, const std::vector<RString> &an, std::vector<AST> &el);
	};
}