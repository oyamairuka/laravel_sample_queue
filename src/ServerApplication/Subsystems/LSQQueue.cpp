#include "LSQ.h"
#include "ServerApplication/Subsystems/LSQSubsystem.h"
#include "ServerApplication/Subsystems/LSQQueue.h"

#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"

#include <sstream>
#include <fstream>

using namespace Poco::JSON;

namespace LSQ
{

LSQQueue::LSQQueue()
    : lastId_(0)
{
}

LSQQueue::~LSQQueue() {}

void LSQQueue::initialize(Application &app)
{
    app.logger().information("[START] Subsystem LSQQueue::initialize");
    app.logger().information("[END] Subsystem LSQQueue::initialize");
}

void LSQQueue::uninitialize()
{
    app().logger().information("[START] Subsystem LSQQueue::uninitialize");
    app().logger().information("[END] Subsystem LSQQueue::uninitialize");
}

size_t LSQQueue::size() const
{
    return queue_.size();
}

void LSQQueue::push(const QueueElement &e)
{
    std::lock_guard<std::mutex> lock(mtx_);
    queue_.push(e);
}

std::pair<bool, QueueElement> LSQQueue::pop()
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (queue_.empty())
    {
        QueueElement e;
        return std::pair<bool, QueueElement>(false, e);
    }
    QueueElement save = queue_.top();
    queue_.pop();
    return std::pair<bool, QueueElement>(true, save);
}

void LSQQueue::save()
{
    std::lock_guard<std::mutex> lock(mtx_);
    try
    {
        app().logger().information("[START] LSQQueue::save");

        // キューを全てコピー
        auto temp = queue_;
        // キューの要素全てをJsonObjectにしてこのArrayに設定する
        Array *array = new Array();
        Array::Ptr pArray(array);
        while (!temp.empty())
        {
            auto e = temp.top();
            temp.pop();
            Object::Ptr pJsonObject(e.toJsonObject());
            pArray->set(pArray->size(), pJsonObject);
        }
        std::ostringstream oss;
        pArray->stringify(oss);
        std::string filePath = app().config().getString("data");
        std::ofstream ofs(filePath);
        if (ofs)
        {
            ofs << oss.str();
        }
        else
        {
            throw std::runtime_error("can't open data file : " + filePath);
        }

        app().logger().information("[END] LSQQueue::save");
    }
    catch (std::exception &e)
    {
        app().logger().error(e.what());
        throw;
    }
    catch (...)
    {
        app().logger().error("unexpected error.");
        throw;
    }
}

unsigned long long LSQQueue::nextId()
{
    std::lock_guard<std::mutex> lock(mtx_);
    return ++lastId_;
}

bool operator<(const QueueElement &e1, const QueueElement &e2)
{
    return e1.id() < e2.id();
}
bool operator>(const QueueElement &e1, const QueueElement &e2) { return e2 < e1; };
bool operator<=(const QueueElement &e1, const QueueElement &e2) { return !(e1 > e2); };
bool operator>=(const QueueElement &e1, const QueueElement &e2) { return !(e1 < e2); };

} // namespace LSQ
