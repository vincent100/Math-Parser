#pragma once

// Includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stack>

// Constants
const int minVal32 = (1 << 31);
const int maxVal32 = ~(1 << 31);

const long long minVal64 = (1ll << 63);
const long long maxVal64 = ~(1ll << 63);

// Print pair
template <typename t1, typename t2>
std::ostream& operator << (std::ostream& out, std::pair<t1, t2>& p) {
	out << "{" << p.first << ", " << p.second << "}";
	return out;
}

// Print vector
template <typename t>
std::ostream& operator << (std::ostream& out, std::vector<t>& v) {
	for (t on : v) {
		out << on << " ";
	}
	out << "\n";
	return out;
}

// Get pair
template <typename t1, typename t2>
std::istream& operator >> (std::istream& in, std::pair<t1, t2>& p) {
	in >> p.first >> p.second;
	return in;
}

// Get properly sized vector
template <typename t> 
std::istream& operator >> (std::istream& in, std::vector<t>& v) {
	for (t& on : v) {
		in >> on;
	}
	return in;
}
