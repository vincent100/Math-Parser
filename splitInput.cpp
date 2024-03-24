#include "splitInput.h"

// Global variables
static std::string input;
static std::vector<std::string> tokens;

signed main(){
	std::getline(std::cin, input); // Get entire line
	
	splitInput ( input );
	
	for (std::string s : tokens) {
		std::cout << s << "\n";
	}
}

/**
 * Finds "implicit" type
 *
 * ex: 'a' => LETTER
 *     '1' => INTEGER
 */
Type findType (char input) {
	if ('0' <= input && input <= '9') return INTEGER;

	if ('a' <= input && input <= 'z') return LETTER;
	if ('A' <= input && input <= 'Z') return LETTER;
	
	if (input == '(' || input == ')') return PARENTHESIS;
	if (input == '[' || input == ']') return PARENTHESIS;
	if (input == '|')                 return PARENTHESIS;


	return OPERAND;
}

/**
 * If the current token should be expanded
 */
bool shouldGroup (char first, char second) {
	Type tFirst = findType (first);
	Type tSecond = findType (second);
 
	if (tFirst == PARENTHESIS || tSecond == PARENTHESIS) return false;

	if (tFirst == tSecond) return true;

	return false;
}

/**
 * Splits input into tokens
 *
 * ex: 33x+3  => 33, x, +, 3
 *     33x+-3 => 33, x, +-, 3
 */
void splitInput (std::string input) {
	char last;
	std::string temp;
	std::string currToken;


	// Remove spaces
	temp = input;
	input = "";
	for (char c : temp) {
		if (c != ' ') input += c;
	}

	currToken = input[0];
	last = input[0];

	input = input.substr(1);
	for (char c : input) {
		
		if ( shouldGroup(last, c) ) currToken += c; // If should be grouped

		else {

			// If can be multiple parts (ex: 3sinx => 3 * sin x)
			if ( findType(currToken[0]) == 1 ) splitToken (currToken); // In this case, 1 represents both LETTER and INTEGER
			// If can only be one type
			else tokens.push_back(currToken);

			currToken = c;
		}

		last = c;
	}

	// Add last token
	if ( findType(currToken[0]) == LETTER ) splitToken (currToken);
	else tokens.push_back(currToken);
}

/**
 * Splits a string token into functions/variables
 *
 * ex: 3sinx => 3, *, sin, x
 */
void splitToken (std::string input) {
	bool isFun, isConst, isDigit;
	bool lastIsFun = true;
	int idx = 0;
	std::string tokenTry;

	while (idx < input.size()) {
		isFun = false;
		isConst = false;
		isDigit = false;
		
		// Combine digits to form numbers
		while (idx < input.size() && '0' <= input[idx] && input[idx] <= '9') {
			isDigit = true;
			tokenTry += input[idx];
			idx++;
		}
		if (isDigit) {
			if (idx != 0 && !lastIsFun) tokens.push_back("_");
			tokens.push_back(tokenTry); // Add number to tokens
			lastIsFun = false;
		}

		// If there is a function name starting at idx
		for (Function f : functions) {
			tokenTry = input.substr(idx, f.size);

			if (idx + f.size <= input.size() && tokenTry == f.name) {
				isFun = true;
				idx += f.size;
				
				// If implicit multiplication. ex: xsin => x*sin
				if (!lastIsFun && f.numParams == 1) tokens.push_back("*");
				
				// Add token
				tokens.push_back(tokenTry);
			}
		}

		// If there is a constant name starting at idx
		for (std::string c : constants) {
			tokenTry = input.substr(idx, c.size());

			if (idx + c.size() <= input.size() && tokenTry == c) {

				// Can process two tokens in the same iteration, so must reset
				lastIsFun = isFun;
				isConst = true;
				isFun = false;

				// If implicit multiplication
				if (!lastIsFun && idx != 0) tokens.push_back("*");
			
				// Add token
				idx += c.size();
				tokens.push_back(tokenTry);
			}
		}

		// If no functions or constant match, just add single letter (as math variable)
		if (!isFun && !isConst && !isDigit && idx < input.size()) {
			tokenTry = input[idx];

			if (idx != 0 && !lastIsFun) tokens.push_back( "*" );

			tokens.push_back( tokenTry );
			
			tokenTry = "";
			idx++;
		}

		lastIsFun = isFun;
		
	}

}

/**
 * Find if | are left or right signs
 *
 * ex: |x| => (x)
 */
void findAbs () {
	int depth;
	int direction;
	bool full, openedNew;
	std::string tokenOn;
	std::vector<int> minDepthBack (tokens.size()); // Minimum depth iterating backwards
	std::vector<int> minDepthFront (tokens.size()); // Minimum depth iterating forward

	depth = 0;
	full = false;
	for (int i = tokens.size() - 1; i >= 0; i--) { // Find min depth iterating back
		openedNew = false;

		// Change depth
		if (tokens[i] == "|" && depth > 0 && full) {
			direction = -1;
		}
		else if (tokens[i] == "|") {
			direction = 1;
			openedNew = true;
		}

		// Set full
		if (openedNew) full = false; // If went one level deeper
		else if (findType(tokens[i][0]) == INTEGER) full = true; // INTEGER and LETTER have same val
	
		if (tokens[i] != "|") continue;

		depth += direction;
		minDepthBack[i] = depth;
	}

	depth = 0;
	full = false;
	for (int i = 0; i < tokens.size(); i++) { // Find min depth iterating front
		openedNew = false;

		// Change depth
		if (tokens[i] == "|" && depth > 0 && full) {
			direction = -1;
		}
		else if (tokens[i] == "|") {
			direction = 1;
			openedNew = true;
		}

		// Set full
		if (openedNew) full = false;
		else if (findType(tokens[i][0]) == INTEGER) full = true;
	
		if (tokens[i] != "|") continue;
		
		depth += direction;
		minDepthFront[i] = depth;
	}

	for (int val : minDepthFront) std::cout << val << " ";
	std::cout << "\n";
	for (int val : minDepthBack) std::cout << val << " ";
	std::cout << "\n";

	for (int i = 0; i < tokens.size(); i++) { // Find which parenthesis works
	}
}
