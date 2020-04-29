#include "LSQ.h"
#include "ServerApplication/Subsystems/LSQSubsystem.h"
#include "RequestHandlerFactory/QueueRequestHandlerFactory.h"
#include "RequestHandler/BulkRequestHandler.h"
#include "RequestHandler/LaterOnRequestHandler.h"
#include "RequestHandler/LaterRequestHandler.h"
#include "RequestHandler/PopRequestHandler.h"
#include "RequestHandler/PushOnRequestHandler.h"
#include "RequestHandler/PushRawRequestHandler.h"
#include "RequestHandler/PushRequestHandler.h"
#include "RequestHandler/SizeRequestHandler.h"
#include "RequestHandler/CommandRequestHandler.h"

#include "Poco/URI.h"

#include <iostream>
#include <vector>

namespace LSQ
{
// URL
const std::string LSQ = "lsq";
const std::string BULK = "/" + LSQ + "/bulk";
const std::string LATER_ON = "/" + LSQ + "/laterOn";
const std::string LATER = "/" + LSQ + "/later";
const std::string POP = "/" + LSQ + "/pop";
const std::string PUSH_ON = "/" + LSQ + "/pushOn";
const std::string PUSH_RAW = "/" + LSQ + "/pushRaw";
const std::string PUSH = "/" + LSQ + "/push";
const std::string SIZE = "/" + LSQ + "/size";

// ハンドラーファクトリー関数
HTTPRequestHandler *BulkRequestHandlerFactory(const HTTPServerRequest &) { return new BulkRequestHandler; }
HTTPRequestHandler *LaterOnRequestHandlerFactory(const HTTPServerRequest &) { return new LaterOnRequestHandler; }
HTTPRequestHandler *LaterRequestHandlerFactory(const HTTPServerRequest &) { return new LaterRequestHandler; }
HTTPRequestHandler *PopRequestHandlerFactory(const HTTPServerRequest &) { return new PopRequestHandler; }
HTTPRequestHandler *PushOnRequestHandlerFactory(const HTTPServerRequest &) { return new PushOnRequestHandler; }
HTTPRequestHandler *PushRawRequestHandlerFactory(const HTTPServerRequest &) { return new PushRawRequestHandler; }
HTTPRequestHandler *PushRequestHandlerFactory(const HTTPServerRequest &) { return new PushRequestHandler; }
HTTPRequestHandler *SizeRequestHandlerFactory(const HTTPServerRequest &) { return new SizeRequestHandler; }

// このハンドラーファクトリーはmapに登録せずに上記ハンドラー以外のリクエストに対応する
HTTPRequestHandler *CommandRequestHandlerFactory(const HTTPServerRequest &) { return new CommandRequestHandler; }

QueueRequestHandlerFactory::QueueRequestHandlerFactory()
{
    factorys_.insert(std::make_pair(std::make_pair(HTTPRequest::HTTP_POST, BULK), BulkRequestHandlerFactory));
    factorys_.insert(std::make_pair(std::make_pair(HTTPRequest::HTTP_POST, LATER_ON), LaterOnRequestHandlerFactory));
    factorys_.insert(std::make_pair(std::make_pair(HTTPRequest::HTTP_POST, LATER), LaterRequestHandlerFactory));
    factorys_.insert(std::make_pair(std::make_pair(HTTPRequest::HTTP_POST, POP), PopRequestHandlerFactory));
    factorys_.insert(std::make_pair(std::make_pair(HTTPRequest::HTTP_POST, PUSH_ON), PushOnRequestHandlerFactory));
    factorys_.insert(std::make_pair(std::make_pair(HTTPRequest::HTTP_POST, PUSH_RAW), PushRawRequestHandlerFactory));
    factorys_.insert(std::make_pair(std::make_pair(HTTPRequest::HTTP_POST, PUSH), PushRequestHandlerFactory));
    factorys_.insert(std::make_pair(std::make_pair(HTTPRequest::HTTP_GET, SIZE), SizeRequestHandlerFactory));
}

HTTPRequestHandler *QueueRequestHandlerFactory::createRequestHandler(const HTTPServerRequest &request)
{
    app().logger().information(request.getMethod());
    app().logger().information(request.getURI());
    if (factorys_.find(std::make_pair(request.getMethod(), request.getURI())) == factorys_.end())
    {
        Poco::URI url(request.getURI());
        std::vector<std::string> segments;
        url.getPathSegments(segments);
        if (segments.size() >= 2 && segments[0] == LSQ)
        {
            return CommandRequestHandlerFactory(request);
        }
    }
    return factorys_.at(std::make_pair(request.getMethod(), request.getURI()))(request);
}

} // namespace LSQ
