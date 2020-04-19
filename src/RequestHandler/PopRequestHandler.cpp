#include "LSQ.h"
#include "ServerApplication/Subsystems/LSQSubsystem.h"
#include "ServerApplication/Subsystems/LSQQueue.h"
#include "RequestHandler/PopRequestHandler.h"
#include "Element/QueueElement.h"

#include "Poco/Util/ServerApplication.h"
#include "Poco/JSON/Object.h"

#include <sstream>

using namespace Poco::Util;
using namespace Poco::JSON;

namespace LSQ
{

void PopRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
{
    app().logger().information("[START] PopRequestHandler::handleRequest");
    response.setChunkedTransferEncoding(true);
    response.setContentType("json");

    std::pair<bool, QueueElement> p = app().getSubsystem<LSQQueue>().pop();
    if (p.first)
    {
        QueueElement e = p.second;
        Object::Ptr pJsonObject(e.toJsonObject());
        std::ostringstream oss;
        pJsonObject->stringify(oss);
        app().logger().debug(oss.str());
        response.send() << oss.str();
    }
    else
    {
        response.send();
    }

    app().logger().information("[END] PopRequestHandler::handleRequest");
}

} // namespace LSQ
