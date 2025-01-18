#pragma once
#include "token.h"
#include<string>
//using namespace lox;
class Expr; // forward declare
class BinaryExpr; // forward declare
class GroupingExpr; // forward declare
class LiteralExpr; // forward declare
class UnaryExpr; // forward declare



class ExprVisitor {//visitor pattern 
public:
	virtual ~ExprVisitor() {}
	virtual std::string visitBinaryExpr(BinaryExpr* Expr) = 0;
	virtual std::string visitGroupingExpr(GroupingExpr* Expr) = 0;
	virtual std::string visitLiteralExpr(LiteralExpr* Expr) = 0;
	virtual std::string visitUnaryExpr(UnaryExpr* Expr) = 0;
};
class Expr {
public:
	virtual ~Expr() {}
	virtual std::string accept(ExprVisitor* visitor) = 0;
};


class BinaryExpr : public Expr {
public:
	BinaryExpr(Expr* left, TOKEN Operator, Expr* right) : left(left), Operator(Operator), right(right) {}
	std::string accept(ExprVisitor* visitor) override {
		return visitor->visitBinaryExpr(this);
	}
public:
	Expr* left;
	TOKEN Operator;
	Expr* right;
};
class GroupingExpr : public Expr {
public:
	GroupingExpr(Expr* expression) : expression(expression) {}
	std::string accept(ExprVisitor* visitor) override {
		return visitor->visitGroupingExpr(this);
	}
public:
	Expr* expression;
};

class LiteralExpr : public Expr {
public:
	LiteralExpr(std::string value) : value(value){}
	LiteralExpr(bool value) :boolValue(value) {}
   LiteralExpr(int value):intValue(value){}
   LiteralExpr(std::variant<std::monostate, double, std::string> value) :literal(value){}
	 
	std::string accept(ExprVisitor* visitor) override {
		return visitor->visitLiteralExpr(this);
	}
public:
	 std::string value;
	 int intValue;
	 bool boolValue;
	 std::variant<std::monostate, double, std::string> literal;
};
class UnaryExpr : public Expr {
public:
	UnaryExpr(TOKEN Operator, Expr* right) : Operator(Operator), right(right) {}
	std::string accept(ExprVisitor* visitor) override {
		return visitor->visitUnaryExpr(this);
	}
public:
	TOKEN Operator;
	Expr* right;
};

