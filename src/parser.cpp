#include"../header/parser.h"
/*
expression     ? equality ;
equality       ? comparison ( ( "!=" | "==" ) comparison )* ;
comparison     ? term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           ? factor ( ( "-" | "+" ) factor )* ;
factor         ? unary ( ( "/" | "*" ) unary )* ;
unary          ? ( "!" | "-" ) unary
			   | primary ;
primary        ? NUMBER | STRING | "true" | "false" | "nil"
			   | "(" expression ")" ;
*/
Parser::Parser(std::vector<TOKEN> token) {
	this->tokens = tokens;
}

Expr* Parser::parse() {
	try {
		return expression();
	}
	catch(std::runtime_error error){
		//return null;
	}
}

Expr* Parser::expression() {
	return equality();
}

Expr* Parser::equality() {
	Expr* expr = comparison();

	while (match(BANG_EQUAL,EQUAL_EQUAL)) {
		TOKEN Operator = previous();
		Expr* right = comparison();
		expr = new BinaryExpr(expr, Operator, right);
	}

	return expr;
}

Expr* Parser::comparison() {
	Expr* expr = term();

	while (match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)) {
		TOKEN Operator = previous();
		Expr* right = term();
		expr = new BinaryExpr(expr, Operator, right);
	}

	return expr;
}

Expr* Parser::term() {
	Expr* expr = factor();

	while (match(MINUS, PLUS)) {
		TOKEN Operator = previous();
		Expr* right = factor();
		expr = new BinaryExpr(expr, Operator, right);//create binary tree of tokens

	}

	return expr;
}

Expr* Parser::factor() {
	Expr* expr = unary();

	while (match(SLASH, STAR)) {
		TOKEN Operator = previous();
		Expr* right = unary();
		expr = new BinaryExpr(expr, Operator, right);

	}

	return expr;
}

Expr* Parser::unary() {
	if (match(BANG, MINUS)) {
		TOKEN Operator = previous();
		Expr* right = unary();
		return new UnaryExpr(Operator, right);

	}

	return primary();
}

Expr* Parser::primary() {
	if (match(FALSE)) {
		return new LiteralExpr(false);
	}

	if (match(TRUE)) {
		return new LiteralExpr(true);
	}

	if (match(NIL)) {
		return new LiteralExpr(std::monostate{});
	}

	if (match(NUMBER, STRING)) {
		return new LiteralExpr(previous().literal);
	}

	if (match(LEFT_PAREN)) {
		Expr* expr = expression();
		consume(RIGHT_PAREN, "Expect ')' after expression. ");
		return new GroupingExpr(expr);
	}

	throw error(peek(), "Expect expression.");
}

TOKEN Parser::consume(TokenType type,const std::string& message) {
	if (check(type)) {
		return advance();
	}

	throw error(peek(), message);
}

template<typename... TokenType>
bool Parser::match(TokenType... types) {
	if ((check(types) || ...)) {
		advance();
		return true;
	}

	return false;
}

bool Parser::check(TokenType type) {
	if (is_at_end()) {
		return false;
	}

	return peek().type == type;
}

TOKEN Parser::advance() {
	if (!is_at_end()) {
		current++;
	}

	return previous();
}

bool Parser::is_at_end() {
	return peek().type == EOF_TOKEN;
}

TOKEN Parser::peek() {//current token
	return tokens[current];
}

TOKEN Parser::previous() {//most recently consumed token
	return tokens[current - 1];
}

std::runtime_error Parser::error(TOKEN token,const std::string& message) {
	LOX lox;
	lox.error(token, message);

	return  std::runtime_error(token.line + " at '" + token.lexeme + "'" + message);
}

void Parser::synchronize() {
	advance();

	while (!is_at_end()) {
		if (previous().type == SEMICOLON) return;

		switch (peek().type) {
		case CLASS:
		case FUN:
		case VAR:
		case FOR:
		case IF:
		case WHILE:
		case PRINT:
		case RETURN:
			return;
		}

		advance();
	}
}