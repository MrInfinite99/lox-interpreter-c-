#include"../header/scanner.h"

SCANNER::SCANNER(std::string& source) {
	this->source = source;
}

std::vector<TOKEN> SCANNER::scan_tokens() {
	while (!is_at_end()) {
		start = current;

		scan_token();
	}

	tokens.push_back(TOKEN(EOF_TOKEN, " ", std::monostate{}, line));

	return tokens;
}

bool SCANNER::is_at_end() {
	return current >= source.length();
}

void SCANNER::scan_token() {
	char c = advance();
	switch (c) {
	case '(': add_token(LEFT_PAREN); break;
	case ')': add_token(RIGHT_PAREN); break;
	case '{': add_token(LEFT_BRACE); break;
	case '}': add_token(RIGHT_BRACE); break;
	case ',': add_token(COMMA); break;
	case '.': add_token(DOT); break;
	case '-': add_token(MINUS); break;
	case '+': add_token(PLUS); break;
	case ';': add_token(SEMICOLON); break;
	case '*': add_token(STAR); break;
	case '!':
		add_token(match('=') ? BANG_EQUAL : BANG);
		break;
	case '=':
		add_token(match('=') ? EQUAL_EQUAL : EQUAL);
		break;
	case '<':
		add_token(match('=') ? LESS_EQUAL : LESS);
		break;
	case '>':
		add_token(match('=') ? GREATER_EQUAL : GREATER);
		break;

	//Longer Lexemes
	case '/':
		if (match('/')) {
			// A comment goes until the end of the line.
			while (peek() != '\n' && !is_at_end()) {
				advance();
			}
		}
		else {
			add_token(SLASH);
		}
		break;

	case '"':
		string();
		break;
	case 'o':
		if (match('r')) {
			add_token(OR);
		}
		break;
	


	case ' ':
	case '\r':
	case '\t':
		// Ignore whitespace.
		break;

	case '\n':
		line++;
		break;


	default:
		if (is_digit(c)) {
			number();
		}
		else if (is_alpha(c)) {//maximal munch
			identifier();
		}
		else {
			LOX lox;
			lox.error(line, "Unexpected character");
			break;
		}
	}			 
}

char SCANNER::advance() {
	return source[current++];
}

void SCANNER::add_token(TokenType type) {
	add_token(type,std::monostate{});
}

void SCANNER::add_token(TokenType type, std::variant<std::monostate,double,std::string> literal) {
	std::cout << "start:" << start << "current" << current << std::endl;
	std::string text = source.substr(start, current-start);
	std::cout << "the token to be added" << text << std::endl;
	tokens.push_back(TOKEN(type, text, literal, line));
}

bool SCANNER::match(char expected) {
	if (is_at_end()) {
		std::cout << "current token(is_at_end())" << source[current] << std::endl;
		return false;
	}
	if (source[current] != expected) {
		std::cout <<"current token"<< source[current] << std::endl;
		return false;
	}

	//current++;
	return true;
}

char SCANNER::peek() {
	if (is_at_end()) {
		return '\0';
	}

	return source[current];
}

void SCANNER::string() {
	while (peek() != '"' && !is_at_end()) {
		if (peek() == '\n') {//multi line strings
			line++;
		}

		if (is_at_end()) {//check if at end of string 
			LOX lox;
			lox.error(line, "Unexpected character");
			break;
		}

		advance();
	}
		std::string value = source.substr(start + 1, current - 2-start);
		add_token(STRING, value);
	
}

bool SCANNER::is_digit(char c) {
	 
	 
	return c >= '0' && c <= '9';
}

void SCANNER::number() {
	while (is_digit(peek())) {
		advance();
	}

	if (peek() == '.' && is_digit(peek_next())) {
		advance();
		while (is_digit(peek())) {
			advance();
		}
	}

	add_token(NUMBER, std::stod(source.substr(start, current-start))); //stod casts the stirng to diuble type
}

char SCANNER::peek_next() {
	if (current + 1 >= source.length()) {
		return '\0';
	}

	return source[current + 1];
}

void SCANNER::identifier() {
	while (is_alpha_numeric(peek())) {
		advance();
	}

	std::string text = source.substr(start, current-start);
	TokenType type = keywords.find(text)->second;//find the value of the key
	if (type == NULL) {
		type = IDENTIFIER;
	}
	add_token(type);
}

bool SCANNER::is_alpha(char c) {
	return (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		c == '_';
}

bool SCANNER::is_alpha_numeric(char c) {
	return is_alpha(c) || is_digit(c);
}