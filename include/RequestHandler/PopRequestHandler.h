#ifndef LSQ_PopRequestHandler_INCLUDED
#define LSQ_PopRequestHandler_INCLUDED

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

using namespace Poco::Net;

namespace LSQ {

class PopRequestHandler: public HTTPRequestHandler
{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override;
};

} // namespace LSQ

#endif // LSQ_PopRequestHandler_INCLUDED
