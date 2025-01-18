#pragma once
#include"Expr.h"
#include<string>
#include<sstream>
#include<any>
 

class AstPrinter : public ExprVisitor {
	

	template<typename... Expr> //ellipsis operator
	std::string parenthesize(std::string name, Expr*... exprs) {
		std::ostringstream builder;

		builder << "(" << name;

		((builder << " " << exprs->accept(this)), ...);//fold expression to expand the paramter pack
        builder << ")";

		return builder.str(); //change to string
	}

public:

	std::string print(Expr* expr) {
		return expr->accept(this);
	}

	std::string visitBinaryExpr(BinaryExpr* Expr) override {
		return parenthesize(Expr->Operator.lexeme, Expr->left, Expr->right);
	}

	std::string visitGroupingExpr(GroupingExpr* Expr) override {
		return parenthesize("group", Expr->expression);
	}

	std::string visitLiteralExpr(LiteralExpr* Expr) override {
		if (Expr->value == "") {
			return "nil";
		}
		return Expr->value;
	}

	std::string visitUnaryExpr(UnaryExpr* Expr) override {
		return parenthesize(Expr->Operator.lexeme, Expr->right);
	}
};