#include "LSQ.h"
#include "ServerApplication/Subsystems/LSQSubsystem.h"
#include "RequestHandler/BulkRequestHandler.h"

#include "Poco/Util/ServerApplication.h"

using namespace Poco::Util;

namespace LSQ
{

void BulkRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
{
    app().logger().information("BulkRequestHandler::handleRequest");

    response.setChunkedTransferEncoding(true);
    response.setContentType("text");
    response.send() << "Thank You Request " << request.getURI();
}

} // namespace LSQ
