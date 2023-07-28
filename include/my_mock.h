/**
 * @file my_mock.h
 * @author mrwangwg (mrwangwg123@163.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MY_MOCK_H
#define MY_MOCK_H

#include <binder/IInterface.h>

namespace my {
namespace mock {

using namespace android;

class IMyMock : public IInterface {
  public:
    DECLARE_META_INTERFACE(MyMock);
    virtual int set(std::string  key, std::string val) = 0;
    virtual std::string get(std::string key) = 0;
    virtual int autoTest() = 0;
};

enum {
    MY_MOCK_SET = IBinder::FIRST_CALL_TRANSACTION,
    MY_MOCK_GET,
    MY_MOCK_AUTO_TEST
};

class BpMyMock : public BpInterface<IMyMock> {
  public:
    explicit BpMyMock(const sp<IBinder>& impl);
    int set(std::string  key, std::string val) override; 
    std::string get(std::string key) override;
    int autoTest() override;
};

class BnMyMock : public BnInterface<IMyMock> {
  public:
    virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags);
};

}
}

#endif // MY_MOCK_H