#pragma once
#include <string>

const std::string FS_VERSIONS[] = { "UNKNOWN VERSION", "FS 98", "FS 2000", "CFS 2", "CFS 1", "FLY", "FS 2002", "FS 2004", "FSX", "ESP", "Prepar3D" };

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
	void connect();
	long getErrorCode();
};

