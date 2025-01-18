#pragma once
#include"TokenType.h"
#include <variant>
#include<string>
#include<iostream>
 

class TOKEN {
     
public:

	TokenType type;
	std::string lexeme;
	std::variant<std::monostate, double, std::string> literal; // Literal value (supports string and number)
	int line;

	std::string toString(){
		//return type + " " + lexeme + " " + literal;
	}

	TOKEN(TokenType type,const std::string& lexeme,std::variant<std::monostate, double, std::string> literal, int line) {
		this->type = type;
		this->lexeme = lexeme;
		this->literal = literal;
		this->line = line;

	}

	void print_token() {
		std::cout << this->lexeme << std::endl;
	}
};