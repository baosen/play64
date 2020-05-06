#include "strmanip.hpp"
using namespace std;

string convert(const string& s) {
	string r;
	r.assign(begin(s), end(s));
	return r;
}
