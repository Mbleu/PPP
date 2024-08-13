//Example of what happens with an uncaught exception.

#include "..\..\std_lib_facilities.h"

int main()
/*try*/ {
	error("Oh dear!");
}
//catch (runtime_error& e) {
//	cerr << "Error: " << e.what() << '\n';
//	keep_window_open();
//	return 1;
//}