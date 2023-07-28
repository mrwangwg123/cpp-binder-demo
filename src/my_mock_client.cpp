#include <binder/Binder.h>
#include <binder/IBinder.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "my_mock.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace my::mock;

int main(int argc, char** argv) {
    int opt;
    android::sp<IServiceManager> sm = defaultServiceManager();
    android::sp<IBinder> binder = sm->getService(String16("my.mock.service"));
    android::sp<IMyMock> cs = interface_cast<IMyMock>(binder);

    while ((opt = getopt(argc, argv, "g:s:t")) != -1) {
        printf("optarg: %s \n", optarg);
        switch (opt) {
            case 'g': {
                printf("get %s\n", optarg);
                std::string ret = cs->get(std::string(optarg));
                printf("RetCode: %s \n", ret.c_str());
            }
                return 0;
            case 's': {
                char* key = strtok(optarg, ":");
                char* val = strtok(NULL, ":");
                printf("set %s :%s \n", key, val);
                int ret = cs->set(std::string(key), std::string(val));
                printf("RetCode: %d \n", ret);
            }
                return 0;
            case 't':{
                printf("autoTest \n");
                int ret = cs->autoTest();
                printf("RetCode: %d \n", ret);
            }
                return 0;
            default:
                printf("Usage: %s [-g key] [-s key:val] [-t]\n", argv[0]);
                return 0;
        }
    }

    return 0;
}