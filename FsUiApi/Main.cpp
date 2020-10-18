#include <iostream>
#include "FsInterface.h"
#include "RestServer.h";

using namespace std;

int main(int argc, char **argv) {
	FsInterface fs;

	if (fs.isConnected()) {
		cout << "Successfully connected to " << fs.getFsVersion() << "!!!" << endl;
		cout << "FSUIPC version " << fs.getUiVersion() << endl;
		cout << "Library version " << fs.getLibVersion() << endl;

		RestServer srv(&fs, 9999);
	}
	else {
		cout << "Connection to FS failed, error code " << fs.getErrorCode() << endl;
	}

	return 0;
}