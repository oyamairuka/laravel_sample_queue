#ifndef LSQ_LaterOnRequestHandler_INCLUDED
#define LSQ_LaterOnRequestHandler_INCLUDED

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

using namespace Poco::Net;

namespace LSQ {

class LaterOnRequestHandler: public HTTPRequestHandler
{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override;
};

} // namespace LSQ

#endif // LSQ_LaterOnRequestHandler_INCLUDED
