#include "LSQ.h"
#include "ServerApplication/Subsystems/LSQSubsystem.h"
#include "ServerApplication/Subsystems/LSQQueue.h"

#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Path.h"

#include <sstream>
#include <fstream>

using namespace Poco::JSON;

namespace LSQ
{

// 終了時に現在のidを保存するファイル名
const std::string LAST_ID_FILE_NAME = "id";

LSQQueue::LSQQueue()
    : lastId_(0)
{
}

LSQQueue::~LSQQueue() {}

void LSQQueue::initialize(Application &app)
{
    app.logger().information("[START] Subsystem LSQQueue::initialize");
    Poco::Path p(app.config().getString("data.dir"));
    p.setFileName(LAST_ID_FILE_NAME);
    lastIdFile_ = p.toString();
    p.setFileName(app.config().getString("data.file"));
    dataFile_ = p.toString();
    readDateFile();
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

void LSQQueue::pushAutoIncrement(QueueElement &e)
{
    std::lock_guard<std::mutex> lock(mtx_);
    e.setId(++lastId_);
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
        std::ofstream ofs(dataFile_);
        if (ofs)
        {
            ofs << oss.str();
        }
        else
        {
            throw std::runtime_error("can't open data file : " + dataFile_);
        }

        std::ofstream idFile(lastIdFile_);
        if (idFile)
        {
            idFile << lastId_;
        }
        else
        {
            throw std::runtime_error("can't open id file : " + lastIdFile_);
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

void LSQQueue::readDateFile()
{
    std::lock_guard<std::mutex> lock(mtx_);
    try
    {
        std::ifstream ifs(dataFile_);
        if (ifs)
        {
            std::ostringstream oss;
            while (!ifs.eof())
            {
                std::string temp;
                std::getline(ifs, temp);
                oss << temp;
            }
            Parser parser;
            Poco::Dynamic::Var result = parser.parse(oss.str());
            Array::Ptr pArray = result.extract<Array::Ptr>();
            for (int i = 0; i < pArray->size(); ++i)
            {
                Object::Ptr pJsonObject = pArray->getObject(i);
                QueueElement e;
                e.setId(pJsonObject->get(QueueElement::ID));
                e.setQueue(pJsonObject->get(QueueElement::QUEUE));
                e.setPayload(pJsonObject->get(QueueElement::PAYLOAD));
                e.setAttempts(pJsonObject->get(QueueElement::ATTEMPTS));
                e.setReservedAt(pJsonObject->get(QueueElement::RESERVED_AT));
                e.setAvailableAt(pJsonObject->get(QueueElement::AVAILABLE_AT));
                e.setCreatedAt(pJsonObject->get(QueueElement::CREATED_AT));
                queue_.push(e);
            }
        }
        else
        {
            throw std::runtime_error("can't open data file : " + dataFile_);
        }

        std::ifstream idFile(lastIdFile_);
        if (idFile)
        {
            idFile >> lastId_;
        }
        else
        {
            throw std::runtime_error("can't open id file : " + lastIdFile_);
        }
    }
    catch (std::runtime_error &e)
    {
        app().logger().error(e.what());
        throw;
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

bool operator<(const QueueElement &e1, const QueueElement &e2)
{
    return e1.id() < e2.id();
}
bool operator>(const QueueElement &e1, const QueueElement &e2) { return e2 < e1; };
bool operator<=(const QueueElement &e1, const QueueElement &e2) { return !(e1 > e2); };
bool operator>=(const QueueElement &e1, const QueueElement &e2) { return !(e1 < e2); };

} // namespace LSQ
