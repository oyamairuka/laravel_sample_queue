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
    app().logger().information("[START] PushRequestHandler::handleRequest");

    Object *jsonObject = new Object;
    Object::Ptr pJsonObject(jsonObject);
    HTMLForm form(request, request.stream());
    for (auto &e : form)
    {
        pJsonObject->set(e.first, e.second);
    }

    QueueElement e;
    e.setId(app().getSubsystem<LSQQueue>().nextId());
    e.setQueue(pJsonObject->get(QueueElement::QUEUE));
    e.setPayload(pJsonObject->get(QueueElement::PAYLOAD));
    e.setAttempts(pJsonObject->get(QueueElement::ATTEMPTS));
    e.setReservedAt(pJsonObject->get(QueueElement::RESERVED_AT));
    e.setAvailableAt(pJsonObject->get(QueueElement::AVAILABLE_AT));
    e.setCreatedAt(pJsonObject->get(QueueElement::CREATED_AT));
    app().getSubsystem<LSQQueue>().push(e);

    response.setChunkedTransferEncoding(true);
    response.setContentType("text");
    response.send() << "Thank You Request " << request.getURI();

    app().logger().information("[END] PushRequestHandler::handleRequest");
}

} // namespace LSQ