#pragma once
#include <string>

const std::string FS_VERSIONS[] = { "UNKNOWN VERSION", "FS 98", "FS 2000", "CFS 2", "CFS 1", "FLY", "FS 2002", "FS 2004", "FSX", "ESP", "Prepar3D" };

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned long U32;
typedef signed char S8;
typedef signed short S16;
typedef signed long S32;
typedef signed long long S64;
typedef float FLT32;
typedef double FLT64;
typedef char ASCIIZ;

enum DataType {
	TU8 = 1,
	TU16,
	TU32,
	TS8,
	TS16,
	TS64,
	TFLT32,
	TFLT64,
	TASCIIZ
};

class FsInterface
{
public:
	FsInterface();
	~FsInterface();
private:
	long errorCode;
	bool connected;
	std::string fsVersion;
	std::string uiVersion;
	std::string libVersion;
public:
	bool isConnected();
	std::string getFsVersion();
	std::string getUiVersion();
	std::string getLibVersion();
	std::string getRawValue(DataType t, int offset);
	U8 getU8(int offset);
	void connect();
	long getErrorCode();
};

