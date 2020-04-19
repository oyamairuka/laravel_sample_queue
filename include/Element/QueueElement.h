#ifndef LSQ_QueueElement_INCLUDED
#define LSQ_QueueElement_INCLUDED

#include "Poco/JSON/Object.h"

#include <string>

using namespace Poco::JSON;

namespace LSQ
{

class QueueElement
{
public:
    unsigned long long id() const { return id_; }
    std::string queue() const { return queue_; }
    std::string payload() const { return payload_; }
    unsigned char attempts() const { return attempts_; }
    unsigned int reservedAt() const { return reservedAt_; }
    unsigned int availableAt() const { return availableAt_; }
    unsigned int createdAt() const { return createdAt_; }

    void setId(unsigned long long id) { id_ = id; }
    void setQueue(std::string queue) { queue_ = queue; }
    void setPayload(std::string payload) { payload_ = payload; }
    void setAttempts(unsigned char attempts) { attempts_ = attempts; }
    void setReservedAt(unsigned int reservedAt) { reservedAt_ = reservedAt; }
    void setAvailableAt(unsigned int availableAt) { availableAt_ = availableAt; }
    void setCreatedAt(unsigned int createdAt) { createdAt_ = createdAt; }

    Object *toJsonObject();

    static const std::string ID;
    static const std::string QUEUE;
    static const std::string PAYLOAD;
    static const std::string ATTEMPTS;
    static const std::string RESERVED_AT;
    static const std::string AVAILABLE_AT;
    static const std::string CREATED_AT;

private:
    unsigned long long id_;
    std::string queue_;
    std::string payload_;
    unsigned char attempts_;
    unsigned int reservedAt_;
    unsigned int availableAt_;
    unsigned int createdAt_;
};

bool operator<(const QueueElement &e1, const QueueElement &e2);
bool operator>(const QueueElement &e1, const QueueElement &e2);
bool operator<=(const QueueElement &e1, const QueueElement &e2);
bool operator>=(const QueueElement &e1, const QueueElement &e2);

} // namespace LSQ

#endif // LSQ_QueueElement_INCLUDED