#include "LSQ.h"
#include "ServerApplication/Subsystems/LSQSubsystem.h"
#include "ServerApplication/Subsystems/LSQServer.h"
#include "RequestHandlerFactory/QueueRequestHandlerFactory.h"

#include "Poco/AutoPtr.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/PropertyFileConfiguration.h"

using namespace Poco;
using namespace Poco::Net;

namespace LSQ
{

LSQServer::LSQServer()
{
}

LSQServer::~LSQServer() {}

void LSQServer::initialize(Application &app)
{
    app.logger().information("[START] Subsystem LSQServer::initialize");
    UInt16 port = static_cast<UInt16>(app.config().getUInt("port"));
    std::unique_ptr<HTTPServer> temp(new HTTPServer(new QueueRequestHandlerFactory, port));
    pSrv_ = std::move(temp);
    app.logger().information("[END] Subsystem LSQServer::initialize");
}

void LSQServer::uninitialize()
{
    app().logger().information("[START] Subsystem LSQServer::uninitialize");
    app().logger().information("[END] Subsystem LSQServer::uninitialize");
}

void LSQServer::start()
{
    pSrv_->start();
    app().logger().information("HTTP Server started on port %hu.", pSrv_->port());
}

void LSQServer::stop()
{
    app().logger().information("Stopping HTTP Server...");
    pSrv_->stop();
}

} // namespace LSQ