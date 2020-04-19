#ifndef LSQ_LSQSubsystem_INCLUDED
#define LSQ_LSQSubsystem_INCLUDED

#include "Poco/Util/Application.h"

namespace LSQ
{
    inline Poco::Util::Application& app()
    {
        return Poco::Util::Application::instance();
    }

} // namespace LSQ

#endif // LSQ_LSQSubsystem_INCLUDED