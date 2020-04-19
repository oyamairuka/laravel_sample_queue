#ifndef LSQ_LSQServerApplication_INCLUDED
#define LSQ_LSQServerApplication_INCLUDED

#include "Poco/Util/ServerApplication.h"

using namespace Poco::Util;

namespace LSQ
{

class LSQApplication : public ServerApplication
{
public:
    LSQApplication();

protected:
    // 初期化処理
    void initialize(Application &self) override;
    // このアプリケーションのメイン関数
    // この関数はPOCOのマクロを使って呼ばれる
    int main(const std::vector<std::string> &) override;
};

} // namespace LSQ

#endif // LSQ_LSQServerApplication_INCLUDED
