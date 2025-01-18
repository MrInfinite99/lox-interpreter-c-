#pragma once
#include<vector>
#include<unordered_map>
#include"token.h"
#include"lox.h"





class SCANNER {
	std::string source;
	std::vector<TOKEN> tokens;
	int start = 0;
	int current = 0;
	int line = 1;

	const std::unordered_map<std::string, TokenType> keywords = {
	{"and",  AND},
	{"class",CLASS},
	{"else", ELSE},
	{"false",FALSE},
	{"for",  FOR},
	{"fun",  FUN},
	{"if",   IF},
	{"nil",  NIL},
	{"or",   OR},
	{"print",PRINT},
	{"return",RETURN},
	{"super",SUPER},
	{"this", THIS},
	{"true", TRUE},
	{"var",  VAR},
	{"while",WHILE}
	};

public:
	SCANNER(std::string& source);
	std::vector<TOKEN> scan_tokens();
	
	bool is_at_end();
	bool match(char expected);
private:
	void scan_token();
	char advance();
	void add_token(TokenType type);
	void add_token(TokenType type, std::variant<std::monostate, double, std::string> literal);
	
	char peek();
	void string();
	bool is_digit(char c);

	void number();
	char peek_next();

	bool is_alpha(char c);
	bool is_alpha_numeric(char c);

	void identifier();
		 
		 
};
