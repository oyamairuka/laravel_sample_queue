#include "LSQ.h"
#include "ServerApplication/Subsystems/LSQSubsystem.h"
#include "ServerApplication/Subsystems/LSQQueue.h"
#include "RequestHandler/CommandRequestHandler.h"

#include "Poco/URI.h"

#include <sstream>

namespace LSQ
{

const std::string HELP = "help";
const std::string COUNT = "count";
const std::string LIST = "list";
const std::string NEXT = "next";

const std::string helpText()
{
    std::ostringstream oss;
    oss << HELP << " : show help message." << std::endl
        << COUNT << " : show current queue elements size." << std::endl
        << LIST << " : disp elements of queue." << std::endl
        << NEXT << " : show next element id." << std::endl;
    return oss.str();
}

void CommandRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
{
    try
    {
        app().logger().information("[START] CommandRequestHandler::handleRequest");
        response.setChunkedTransferEncoding(true);
        response.setContentType("text");

        Poco::URI url(request.getURI());
        std::vector<std::string> segments;
        url.getPathSegments(segments);
        if (segments.size() >= 2)
        {
            std::string command = segments[1];
            if (command == HELP)
            {
                response.send() << helpText() << std::endl;
            }
            else if (command == COUNT)
            {
                response.send() << "queue size is " << app().getSubsystem<LSQQueue>().size() << std::endl;
            }
            else if (command == LIST)
            {
                response.send() << "list command" << std::endl;
            }
            else if (command == NEXT)
            {
                response.send() << "next element id is " << app().getSubsystem<LSQQueue>().lastId() + 1 << std::endl;
            }
            else
            {
                response.send() << "command not found" << std::endl;
            }
        }

        app().logger().information("[END] CommandRequestHandler::handleRequest");
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
