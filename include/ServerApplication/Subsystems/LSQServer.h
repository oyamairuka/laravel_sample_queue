#ifndef LSQ_LSQServer_INCLUDED
#define LSQ_LSQServer_INCLUDED

#include "Poco/Util/Subsystem.h"
#include "Poco/Net/HTTPServer.h"

#include <memory>

using namespace Poco::Util;
using namespace Poco::Net;

namespace LSQ
{

class LSQServer : public Subsystem
{
public:
    LSQServer();
    const char *name() const override { return "LSQServer"; }

    // HttpServerをstartする
    void start();
    // HttpServerをstopする
    void stop();

protected:
    ~LSQServer();
    void initialize(Application &app) override;
    void uninitialize() override;

private:
    std::unique_ptr<HTTPServer> pSrv_;
};

} // namespace LSQ

#endif // LSQ_LSQServer_INCLUDED