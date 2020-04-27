#include "LSQ.h"
#include "ServerApplication/Subsystems/LSQSubsystem.h"
#include "ServerApplication/Subsystems/LSQConsole.h"
#include "ServerApplication/Subsystems/LSQQueue.h"

#include <iostream>
#include <sstream>

namespace LSQ
{

const char LSQConsole::HELP = 'h';
const char LSQConsole::SIZE = 's';
const char LSQConsole::LIST = 'l';
const char LSQConsole::NEXT = 'n';
const char LSQConsole::WRITE = 'w';
const char LSQConsole::QUIT = 'q';

LSQConsole::LSQConsole()
{
}

LSQConsole::~LSQConsole()
{
}

void LSQConsole::initialize(Application &app)
{
    app.logger().information("[START] Subsystem LSQConsole::initialize");
    app.logger().information("[END] Subsystem LSQConsole::initialize");
}

void LSQConsole::uninitialize()
{
    app().logger().information("[START] Subsystem LSQConsole::uninitialize");
    app().logger().information("[END] Subsystem LSQConsole::uninitialize");
}

void LSQConsole::start()
{
    app().logger().debug("LSQConsole::start");
    std::cout << "LSQConsole::start" << std::endl;
    char c = ' ';
    bool quit = false;
    while (!quit && std::cin >> c)
    {
        switch (c)
        {
        case HELP:
            std::cout << helpText() << std::endl;
            break;
        case SIZE:
            std::cout << "queue size is " << app().getSubsystem<LSQQueue>().size() << std::endl;
            break;
        case LIST:
            std::cout << "list command" << std::endl;
            break;
        case NEXT:
            std::cout << "next element id is " << app().getSubsystem<LSQQueue>().lastId() + 1 << std::endl;
            break;
        case WRITE:
            app().getSubsystem<LSQQueue>().save();
            std::cout << "save command was completed normally." << std::endl;
            break;
        case QUIT:
            quit = true;
            break;
        default:
            std::cout << "command not found" << std::endl;
        }
    }
}

std::string LSQConsole::helpText() const
{
    std::ostringstream oss;
    oss << HELP << " : show help message." << std::endl
        << SIZE << " : show current queue elements size." << std::endl
        << LIST << " : disp elements of queue." << std::endl
        << NEXT << " : show next element id." << std::endl
        << WRITE << " : write queue elements to data file." << std::endl
        << QUIT << " : exit command." << std::endl;
    return oss.str();
}

} // namespace LSQ