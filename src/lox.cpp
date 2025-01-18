#include"../header/lox.h"

void LOX::run_file(const std::string& path) {
	std::ifstream bytes(path, std::ios::binary);

	if (!bytes) {
		std::cerr << "could not open file:" << path << std::endl;
		std::exit(65);
	}

	//file into string 
	std::ostringstream buffer;
	buffer << bytes.rdbuf();
	std::string fileContent = buffer.str();

	run(fileContent);
}

void LOX::run_prompt() {
	std::string line;
	 
	while (true) {
		std::cout << ">";
		if (!std::getline(std::cin, line)) break; // Exit if EOF (Ctrl+D or Ctrl+Z)
		//if (line == NULL) break;

		run(line);
		hadError = false;

	}
}

void LOX::run(std::string& source) {
//	std::stringstream scanner(source);
	//std::vector<token> tokens;
	//while (scanner >> tokens) {
		//std::cout << tokens << std::endl;
	//}

	//if (haderror) {
	//	std::exit(65);
	//}

	SCANNER scanner(source);

	std::vector<TOKEN> tokens = scanner.scan_tokens();

	for (TOKEN token : tokens) {
		token.print_token();
	 }

}

void LOX::error(int line,const std::string& message) {
	std::string emptyStr = "";
	report(line,emptyStr, message);
}                                                              

void LOX::report(int line,const std::string& where,const std::string& message) {
	std::cerr << "[line"<<line<<"] Error"<<where << ":" << message<<std::endl;
	hadError = true;
}

void LOX::error(TOKEN token,const std::string& message) {
	if (token.type == EOF_TOKEN) {
		report(token.line, " at end", message);
	}
	else {
		report(token.line, " at '" + token.lexeme + "'", message);
	}
}