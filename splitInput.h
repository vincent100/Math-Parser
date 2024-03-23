#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

// Constants
const int maxVal32 = ~(1 << 31);
const int minVal32 = (1 << 31);

const long long maxVal64 = ~(1ll << 63);
const long long minVal64 = (1ll << 63);

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
	INTEGER = 1,
	LETTER = 1,
	PARENTHESIS,
	OPERAND,
};

// Functions
Type findType (char input);
bool shouldGroup (char first, char second);
void splitToken (std::string input);
void splitInput (std::string input);
void findAbs ();
