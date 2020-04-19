#include "LSQ.h"
#include "Element/QueueElement.h"

namespace LSQ
{

const std::string QueueElement::ID = "id";
const std::string QueueElement::QUEUE = "queue";
const std::string QueueElement::PAYLOAD = "payload";
const std::string QueueElement::ATTEMPTS = "attempts";
const std::string QueueElement::RESERVED_AT = "reservedAt";
const std::string QueueElement::AVAILABLE_AT = "availableAt";
const std::string QueueElement::CREATED_AT = "createdAt";

Object *QueueElement::toJsonObject()
{
    Object *jsonObject = new Object;
    jsonObject->set(QueueElement::ID, id());
    jsonObject->set(QueueElement::QUEUE, queue());
    jsonObject->set(QueueElement::PAYLOAD, payload());
    jsonObject->set(QueueElement::ATTEMPTS, attempts());
    jsonObject->set(QueueElement::RESERVED_AT, reservedAt());
    jsonObject->set(QueueElement::AVAILABLE_AT, availableAt());
    jsonObject->set(QueueElement::CREATED_AT, createdAt());
    return jsonObject;
}

} // namespace LSQ
