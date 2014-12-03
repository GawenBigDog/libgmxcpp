
/**
 * @author James Barnett, jbarnet4@tulane.edu
 */

#include "CommandLine.h"

bool getArgument(int argc, char* argv[], string flag, string *argToReturn) {

	string arg;
	for (int i=1;i<argc;i++) {
		arg = argv[i];
		if (arg == flag) {
			if (i+1 >= argc) {
                cout << "ERROR: missing argument to " << flag << "." << endl;
                return false;
            }
			*argToReturn = argv[i+1];
			return true;
		}
	}
    return false;
}

bool checkHelpArg(int argc, char* argv[], string flag) {

	string arg;
	for (int i=1;i<argc;i++) {
		arg = argv[i];
		if (arg == flag) {
            return true;
		}
	}

    return false;
}
