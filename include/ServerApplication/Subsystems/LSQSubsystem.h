#ifndef LSQ_LSQSubsystem_INCLUDED
#define LSQ_LSQSubsystem_INCLUDED

#include "Poco/Util/Application.h"

namespace LSQ
{
inline Poco::Util::Application &app()
{
    return Poco::Util::Application::instance();
}

// httpリクエストで実行される各処理の結果コード
inline int SUCCESS() { return 0; }
inline int FAILED() { return -1; }

} // namespace LSQ

#endif // LSQ_LSQSubsystem_INCLUDED