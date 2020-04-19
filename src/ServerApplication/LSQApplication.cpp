#include "LSQ.h"
#include "ServerApplication/Subsystems/LSQServer.h"
#include "ServerApplication/Subsystems/LSQQueue.h"
#include "ServerApplication/Subsystems/LSQConsole.h"
#include "ServerApplication/LSQApplication.h"
#include "Element/QueueElement.h"
#include "RequestHandlerFactory/QueueRequestHandlerFactory.h"

#include "Poco/Net/HTTPServer.h"
#include "Poco/Message.h"

#include <iostream>

using namespace Poco;
using namespace Poco::Net;

namespace LSQ
{

LSQApplication::LSQApplication()
{
    addSubsystem(new LSQQueue);
    addSubsystem(new LSQServer);
    addSubsystem(new LSQConsole);
}

void LSQApplication::initialize(Application &self)
{
    loadConfiguration();
    ServerApplication::initialize(self);
    self.logger().setLevel(Message::PRIO_DEBUG);
}

int LSQApplication::main(const std::vector<std::string> &)
{
    try
    {
        getSubsystem<LSQServer>().start();
        getSubsystem<LSQConsole>().start();
        std::cout << "to stop LSQServer please type ctrl + c." << std::endl;
        waitForTerminationRequest();
        getSubsystem<LSQServer>().stop();
    }
    catch (std::exception &e)
    {
        logger().information(e.what());
    }

    return Application::EXIT_OK;
}

} // namespace LSQ
