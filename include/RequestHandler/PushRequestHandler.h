#ifndef LSQ_PushRequestHandler_INCLUDED
#define LSQ_PushRequestHandler_INCLUDED

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

using namespace Poco::Net;

namespace LSQ
{

class PushRequestHandler : public HTTPRequestHandler
{
public:
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) override;
};

} // namespace LSQ

#endif // LSQ_PushRequestHandler_INCLUDED
