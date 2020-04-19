#ifndef LSQ_QueueRequestHandlerFactory_INCLUDED
#define LSQ_QueueRequestHandlerFactory_INCLUDED

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"

#include <map>

using namespace Poco::Net;

namespace LSQ
{

class QueueRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
    QueueRequestHandlerFactory();
    HTTPRequestHandler *createRequestHandler(const HTTPServerRequest &) override;

private:
    std::map<std::pair<const std::string, const std::string>, HTTPRequestHandler *(*)(const HTTPServerRequest &)> factorys_;
};

} // namespace LSQ

#endif // LSQ_QueueRequestHandlerFactory_INCLUDED
