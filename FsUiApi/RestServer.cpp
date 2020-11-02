#include <iostream>
#include <cstdlib>
#include "RestServer.h"

using namespace std;
using namespace httplib;

RestServer::RestServer(FsInterface *fs, int port)
{
	this->fs = fs;

	srv.Get("/status", [&](const Request& req, Response& res) {
		string result = this->getStatus();
		res.set_content(result, JSON);
	});

	srv.Get("/raw", [&](const Request& req, Response& res) {
		if (!req.has_param("type")) {
			res.set_content("Missing param 'type'", TEXT);
			return;
		}

		if (!req.has_param("offset")) {
			res.set_content("Missing param 'offset'", TEXT);
			return;
		}

		int t = atoi(req.get_param_value("type").c_str());
		int o = atoi(req.get_param_value("offset").c_str());

		string result = this->getRaw(t, o);

		res.set_content(result, TEXT);
	});

	srv.Get("/u8", [&](const Request& req, Response& res) {
		if (!req.has_param("offset")) {
			res.set_content("Missing param 'offset'", TEXT);
			return;
		}

		int o = atoi(req.get_param_value("offset").c_str());
		U8 u8 = this->getU8(o);
		char result[4];
		sprintf(result, "%d", u8);
		res.set_content(result, TEXT);
	});

	cout << "Start server listening on port " << port << endl;
	srv.listen("0.0.0.0", port);
}


RestServer::~RestServer()
{
	delete fs;
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

string RestServer::getRaw(int t, int o) {
	return fs->getRawValue((DataType)t, o);
}

U8 RestServer::getU8(int o) {
	return fs->getU8(o);
}
