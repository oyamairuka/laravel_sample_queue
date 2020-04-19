
#ifndef LSQ_LSQConsole_INCLUDED
#define LSQ_LSQConsole_INCLUDED

#include "Poco/Util/Subsystem.h"
#include "Poco/Util/Application.h"

using namespace Poco::Util;

namespace LSQ
{

class LSQConsole : public Subsystem
{
public:
    LSQConsole();
    const char *name() const override { return "LSQConsole"; }

    // コンソール入力をstartする
    void start();
    // ヘルプコマンドのテキストを返す
    std::string helpText() const;
    // コマンド文字
    static const char HELP;     // = 'h'
    static const char SIZE;     // = 's'
    static const char LIST;     // = 'l'
    static const char NEXT;     // = 'n'
    static const char WRITE;    // = 'w'
    static const char QUIT;     // = 'q'

protected:
    ~LSQConsole();
    void initialize(Application &app) override;
    void uninitialize() override;
};

} // namespace LSQ

#endif // LSQ_LSQConsole_INCLUDED