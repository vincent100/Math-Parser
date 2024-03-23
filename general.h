#pragma once

#include <iostream>
#include <vector>

// Print pair
template <typename t1, typename t2>
std::ostream& operator >> (std::ostream& out, std::pair<t1, t2>& p) {
	out << "{" << p.first << ", " << p.second << "}";
	return out;
}

// Print vector
template <typename t>
std::ostream& operator >> (std::ostream& out, std::vector<t>& v) {
	for (t on : v) {
		std::cout << on << " ";
	}
	std::cout << "\n";
}
