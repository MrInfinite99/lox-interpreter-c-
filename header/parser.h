#pragma once

#include <stdexcept>
#include<vector>
#include"scanner.h"
#include"Expr.h"

class Parser {
private:
	std::vector<TOKEN> tokens;
	int current = 0;

	Expr* expression();
	Expr* equality();
	Expr* comparison();
	Expr* term();
	Expr* factor();
	Expr* unary();
	Expr* primary();

	template<typename... TokenType>
	bool match(TokenType... types);

	bool  check(TokenType type);
	TOKEN  advance();
	bool  is_at_end();
	TOKEN peek();
	TOKEN previous();
	TOKEN consume(TokenType type,const std::string& message);

	void synchronize();

	 
	std::runtime_error error(TOKEN token, const std::string& message);
public:
	Parser(std::vector<TOKEN> tokens);

	Expr* parse();
		 
	 


};