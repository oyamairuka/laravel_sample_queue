#include "LSQ.h"
#include "ServerApplication/Subsystems/LSQSubsystem.h"
#include "ServerApplication/Subsystems/LSQQueue.h"
#include "RequestHandler/PopRequestHandler.h"
#include "Element/QueueElement.h"

#include "Poco/Util/ServerApplication.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/JSON/Object.h"

#include <sstream>

using namespace Poco::Util;
using namespace Poco::Net;
using namespace Poco::JSON;

namespace LSQ
{

const std::string PopRequestHandler::CURRENT_TIME = "currentTime";

void PopRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
{
    try
    {
        app().logger().information("[START] PopRequestHandler::handleRequest");
        response.setChunkedTransferEncoding(true);
        response.setContentType("json");

        Object *jsonObject = new Object;
        Object::Ptr pJsonObject(jsonObject);
        HTMLForm form(request, request.stream());
        for (auto &e : form)
        {
            pJsonObject->set(e.first, e.second);
        }

        std::pair<bool, QueueElement> p = app().getSubsystem<LSQQueue>().pop(pJsonObject->get(PopRequestHandler::CURRENT_TIME));
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
            response.send() << "";
        }

        app().logger().information("[END] PopRequestHandler::handleRequest");
    }
    catch (const std::exception &e)
    {
        app().logger().error(e.what());
        response.send() << "";
    }
    catch (...)
    {
        app().logger().error("unexpected error.");
        response.send() << "";
    }
}

} // namespace LSQ
