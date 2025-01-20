#pragma once
#include<iostream>
#include<string>
#include <fstream>
#include <sstream>
#include<vector>
#include"token.h"
#include"scanner.h"
#include"parser.h"
#include"astPrinter.h"

class LOX {
public:
	void run_file(const std::string& path);
	void run_prompt();
	void run(std::string& source);
	void error(int line,const std::string& message);
	void error(TOKEN token,const std::string& message);
	void report(int line,const std::string& where,const std::string& message);

private:
	bool hadError = false;
};