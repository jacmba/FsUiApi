#include <iostream>
#include "RestServer.h"

using namespace std;
using namespace httplib;

RestServer::RestServer(FsInterface *fs, int port)
{
	this->fs = fs;

	srv.Get("/status", [&](const Request& req, Response& res) {
		string result = this->getStatus();
		res.set_content(result, "application/json");
	});

	cout << "Start server listening on port " << port << endl;
	srv.listen("0.0.0.0", port);
}


RestServer::~RestServer()
{
}


string RestServer::getStatus()
{
	string statusJson = "{\"connected\":";
	statusJson += fs->isConnected() ? "true" : "false";
	statusJson += ",\"fs_version\":\"";
	statusJson += fs->getFsVersion();
	statusJson += "\",\"fsuipc_version\":\"";
	statusJson += fs->getUiVersion();
	statusJson += "\",\"lib_version\":\"";
	statusJson += fs->getLibVersion();
	statusJson += "\"}";
	return statusJson;
}
