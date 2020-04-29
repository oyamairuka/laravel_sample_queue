#include "LSQ.h"
#include "ServerApplication/Subsystems/LSQSubsystem.h"
#include "ServerApplication/Subsystems/LSQQueue.h"
#include "RequestHandler/PushRequestHandler.h"
#include "Element/QueueElement.h"

#include "Poco/Util/ServerApplication.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/JSON/Object.h"

using namespace Poco::Util;
using namespace Poco::Net;
using namespace Poco::JSON;

namespace LSQ
{

void PushRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
{
    try
    {
        app().logger().information("[START] PushRequestHandler::handleRequest");
        response.setChunkedTransferEncoding(true);
        response.setContentType("text");

        Object *jsonObject = new Object;
        Object::Ptr pJsonObject(jsonObject);
        HTMLForm form(request, request.stream());
        for (auto &e : form)
        {
            pJsonObject->set(e.first, e.second);
        }

        QueueElement e;
        e.setQueue(pJsonObject->get(QueueElement::QUEUE));
        e.setPayload(pJsonObject->get(QueueElement::PAYLOAD));
        e.setAttempts(pJsonObject->get(QueueElement::ATTEMPTS));
        e.setReservedAt(pJsonObject->get(QueueElement::RESERVED_AT));
        e.setAvailableAt(pJsonObject->get(QueueElement::AVAILABLE_AT));
        e.setCreatedAt(pJsonObject->get(QueueElement::CREATED_AT));
        app().getSubsystem<LSQQueue>().pushAutoIncrement(e);

        response.send() << SUCCESS();

        app().logger().information("[END] PushRequestHandler::handleRequest");
    }
    catch (const std::exception &e)
    {
        app().logger().error(e.what());
        response.send() << FAILED();
    }
    catch (...)
    {
        app().logger().error("unexpected error.");
        response.send() << FAILED();
    }
}

} // namespace LSQ
