#include "Parser/AST.h"

namespace amalt {
	AST::AST(const Type t, ae e, const ui64 l, const ui64 p) : type(t), expr(std::move(e)), line(l), pos(p) {}
	LetAst::LetAst(const RString n, AST e) : name(std::move(n)), expr(std::move(e)) {}
	CondAst::CondAst(std::vector<std::tuple<AST, AST>> &el) : exprlist(std::move(el)) {}
	MatchAst::MatchAst(AST e, std::vector<std::tuple<AST, AST>>& el) : expr(std::move(e)), exprlist(std::move(el)) {}
	FCallAst::FCallAst(std::vector<std::tuple<AST, AST>>& el) : exprlist(std::move(el)) {}
	DefunAst::DefunAst(const RString n, const std::vector<RString>& an, std::vector<AST>& el) : name(std::move(n)), argsnames(std::move(an)), exprlist(std::move(el)) {}
}
