#pragma once

#include "../general.h"

// Function
struct Function {
	std::string name;
	int numParams;
	int size;
};

// List of functions
const std::vector<Function> functions = {
	{"sin", 1, 3},
	{"cos", 1, 3},
	{"tan", 1, 3},
	{"cot", 1, 3},
	{"cot", 1, 3},
	{"sec", 1, 3},
	{"csc", 1, 3},
	{"choose", 2, 6}
};

// List of constants
const std::vector<std::string> constants = {
	"pi", "phi", "gamma", "beta"
};

// Implicit type
enum Type {
	EMPTY,
	INTEGER,
	LETTER,
	PARENTHESIS,
	OPERAND,
};

// Functions
Type findType (char input);
bool shouldGroup (char first, char second);
void splitToken (std::string input);
void splitInput (std::string input);
