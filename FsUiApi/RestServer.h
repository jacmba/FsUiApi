#pragma once
#include "FsInterface.h"
#include <httplib.h>
#include <string>

class RestServer
{
public:
	RestServer(FsInterface*, int port);
	~RestServer();
private:
	FsInterface* fs;
	httplib::Server srv;
public:
	std::string getStatus();
};

