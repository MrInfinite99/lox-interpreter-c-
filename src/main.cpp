#include"../header/lox.h"
#include"../header/astPrinter.h"
#include<iostream>

int main(int argc, char* argv[]) {
	LOX lox;

	if (argc > 2) {
		std::cerr << "Usage: lox[script]" << std::endl;
		std::exit(64); // Exit code for incorrect usage
	}
	else if (argc == 1) {
		lox.run_file(argv[1]);
	}
	else {
		lox.run_prompt();
	}

	return 0;
}

