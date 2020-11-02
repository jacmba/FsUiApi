#include "FsInterface.h"
#include <Windows.h>
#include <FSUIPC_User.h>
#include <string>
#include <cstdio>

using namespace std;

string parseVersion(long v) {
	char buff[] = {
		'0' + (0x0F & (v >> 28)),
		'.',
		'0' + (0x0F & (v >> 24)),
		'0' + (0x0F & (v >> 20)),
		'0' + (0x0F & (v >> 16)),
		0
	};

	int i = 0;
	string result;
	while (buff[i] != 0) {
		result += buff[i];
		i++;
	}
	const char a = (FSUIPC_Version & 0xFFFF) ? 'a' + (FSUIPC_Version & 0xFF) - 1 : ' ';
	result += a;

	return result;
}

FsInterface::FsInterface()
{
	errorCode = 0;
	connected = false;

	connect();
}


FsInterface::~FsInterface()
{
	if (isConnected()) {
		FSUIPC_Close();
	}
}


bool FsInterface::isConnected()
{
	return connected;
}


std::string FsInterface::getFsVersion()
{
	return fsVersion;
}


std::string FsInterface::getUiVersion()
{
	return uiVersion;
}


std::string FsInterface::getLibVersion()
{
	return libVersion;
}


void FsInterface::connect()
{
	connected = FSUIPC_Open(SIM_ANY, (DWORD*)&errorCode);
	if (connected) {
		fsVersion = FS_VERSIONS[FSUIPC_FS_Version];
	}

	uiVersion = parseVersion(FSUIPC_Version);
	libVersion = parseVersion(FSUIPC_Lib_Version);
}

string FsInterface::getRawValue(DataType t, int offset) {
	char result[256];
	DWORD dwResult;
	BOOL success;

	switch (t)
	{
	case TU8:
		U8 u8 = getU8(offset);
		sprintf(result, "%d", u8);
		break;
	case TU16:
		break;
	case TU32:
		break;
	case TS8:
		break;
	case TS16:
		break;
	case TS64:
		break;
	case TFLT32:
		break;
	case TFLT64:
		break;
	case TASCIIZ:
		break;
	default:
		success = FALSE;
		break;
	}

	return result;
}

U8 FsInterface::getU8(int offset) {
	U8 result;
	DWORD dwResult;
	BOOL success;

	success = FSUIPC_Read(offset, sizeof(U8), &result, &dwResult);
	if (!success) {
		throw dwResult;
	}
	FSUIPC_Process(&dwResult);
	if (dwResult > 0) {
		throw dwResult;
	}

	return result;
}


long FsInterface::getErrorCode()
{
	return errorCode;
}