#ifndef LSQ_LSQQueue_INCLUDED
#define LSQ_LSQQueue_INCLUDED

#include "Element/QueueElement.h"

#include "Poco/Util/Subsystem.h"
#include "Poco/Util/Application.h"

#include <queue>
#include <mutex>

using namespace Poco::Util;

namespace LSQ
{

struct Compare
{
    bool operator()(const QueueElement &lhs, const QueueElement &rhs) const;
};

class LSQQueue : public Subsystem
{
public:
    LSQQueue();
    const char *name() const override { return "LSQQueue"; }

    size_t size() const;
    void push(const QueueElement &e);
    void pushAutoIncrement(QueueElement &e);
    void save();
    std::pair<bool, QueueElement> pop(int currentTime);

    unsigned long long lastId() { return lastId_; }
    unsigned long long nextId();

protected:
    ~LSQQueue();
    void initialize(Application &app) override;
    void uninitialize() override;

private:
    void readDateFile();

    // このサブシステム(キューを管理する)のインスタンスにおいて最後に発行されたジョブID
    unsigned long long lastId_;
    // データファイルの絶対パス
    std::string dataFile_;
    // IDの現在値を保存するファイルの絶対パス
    std::string lastIdFile_;
    std::priority_queue<QueueElement, std::vector<QueueElement>, Compare> queue_;
    std::mutex mtx_;
};

} // namespace LSQ

#endif // LSQ_LSQQueue_INCLUDED