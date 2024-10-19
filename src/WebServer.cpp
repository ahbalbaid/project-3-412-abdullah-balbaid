#include "WebServer.h"

WebServer::WebServer() : request_start_time_(0), id(0) {}

WebServer::WebServer(int id) : request_start_time_(0), id(id) {}

void WebServer::AddRequest(const Request &req, int curr_time)
{
    r_ = req;
    request_start_time_ = curr_time;
}

Request WebServer::GetRequest() const
{
    return r_;
}

int WebServer::GetId() const
{
    return id;
}

bool WebServer::IsRequestDone(int curr_time) const
{
    return curr_time >= (request_start_time_ + r_.time);
}
