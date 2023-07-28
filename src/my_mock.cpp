#include "my_mock.h"
#include <binder/Parcel.h>
#include <utils/Log.h>

namespace my
{
    namespace mock
    {

        IMPLEMENT_META_INTERFACE(MyMock, "my.mock.IMyMock");

        BpMyMock::BpMyMock(const sp<IBinder> &impl) : BpInterface<IMyMock>(impl) {}

        int BpMyMock::set(std::string key, std::string val)
        {
            Parcel data, reply;
            data.writeInterfaceToken(IMyMock::getInterfaceDescriptor());
            data.writeCString(key.c_str());
            data.writeCString(val.c_str());
            remote()->transact(MY_MOCK_SET, data, &reply);
            return reply.readInt32();
        }

        std::string BpMyMock::get(std::string key)
        {
            Parcel data, reply;
            data.writeInterfaceToken(IMyMock::getInterfaceDescriptor());
            data.writeCString(key.c_str());
            remote()->transact(MY_MOCK_GET, data, &reply);
            std::string ret = reply.readCString();
            return ret;
        }

        int BpMyMock::autoTest()
        {
            Parcel data, reply;
            data.writeInterfaceToken(IMyMock::getInterfaceDescriptor());
            remote()->transact(MY_MOCK_AUTO_TEST, data, &reply);
            return reply.readInt32();
        }

        status_t BnMyMock::onTransact(uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags)
        {
            printf("onTransact->code:%d, flags:%d \n", code, flags);
            switch (code)
            {
            case MY_MOCK_SET:
            {
                CHECK_INTERFACE(IMyMock, data, reply);
                std::string key, val;
                key = data.readCString();
                val = data.readCString();
                int ret = set(key, val);
                reply->writeInt32(ret);
                return NO_ERROR;
            }
            break;
            case MY_MOCK_GET:
            {
                CHECK_INTERFACE(IMyMock, data, reply);
                std::string key;
                key = data.readCString();
                std::string val = get(key);
                reply->writeCString(val.c_str());
                return NO_ERROR;
            }
            break;
            case MY_MOCK_AUTO_TEST:
            {
                CHECK_INTERFACE(IMyMock, data, reply);
                int ret = autoTest();
                reply->writeInt32(ret);
                return NO_ERROR;
            }
            break;
            default:
                return BBinder::onTransact(code, data, reply, flags);
            }
        }
    }
}