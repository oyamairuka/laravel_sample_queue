#ifndef LSQ_CommandRequestHandler_INCLUDED
#define LSQ_CommandRequestHandler_INCLUDED

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

using namespace Poco::Net;

namespace LSQ
{

class CommandRequestHandler : public HTTPRequestHandler
{
public:
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) override;
};

} // namespace LSQ

#endif // LSQ_CommandRequestHandler_INCLUDED
