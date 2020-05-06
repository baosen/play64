#include "hex.hpp"
#include <iomanip>
using namespace std;

void hexify(stringstream& wss) {
	wss << hex << setfill('0') << setw(8);
}
