#pragma once
#include "FsInterface.h"
#include <httplib.h>
#include <string>

#define JSON "application/json"
#define TEXT "text/plain"

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
	std::string getRaw(int t, int o);
};

