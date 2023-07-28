#include "my_mock.h"
#include <unordered_map>
#include <binder/Binder.h>
#include <binder/IBinder.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

namespace my
{
    namespace mock
    {
        class MyMockServer : public BnMyMock
        {
        public:
            MyMockServer() {}

            int set(std::string key, std::string val) override;
            std::string get(std::string key) override;
            int autoTest() override;

        private:
            std::unordered_map<std::string, std::string> mMockMap;
        };

        int MyMockServer::set(std::string key, std::string val)
        {
            mMockMap[key] = val;
            return 0;
        }

        std::string MyMockServer::get(std::string key)
        {
            if (mMockMap.find(key) == mMockMap.end())
            {
                return "";
            }
            return mMockMap[key];
        }

        int MyMockServer::autoTest()
        {
            for (auto &kv : mMockMap)
            {
                std::cout << kv.first << " : " << kv.second << std::endl;
            }
            return 0;
        }

    }
}

using namespace my::mock;

int main(int /* argc */, char * /* argv */[])
{
    android::sp<IServiceManager> sm = defaultServiceManager();
    sm->addService(String16("my.mock.service"), new MyMockServer());
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}