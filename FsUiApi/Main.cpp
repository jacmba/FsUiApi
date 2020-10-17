#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <FSUIPC_User.h>
#include <httplib.h>

using namespace std;

int main(int argc, char **argv) {
	DWORD dwResult;
	BOOL done;

	done = FSUIPC_Open(SIM_ANY, &dwResult);
	if (done) {
		cout << "Successfully connected to FS, version: " << FSUIPC_FS_Version << endl;
	}
	else {
		cout << "Error connecting FS: " << dwResult << endl;
	}
	return 0;
}