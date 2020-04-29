#ifndef LSQ_PushRawRequestHandler_INCLUDED
#define LSQ_PushRawRequestHandler_INCLUDED

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

using namespace Poco::Net;

namespace LSQ
{

class PushRawRequestHandler : public HTTPRequestHandler
{
public:
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) override;
};

} // namespace LSQ

#endif // LSQ_PushRawRequestHandler_INCLUDED
