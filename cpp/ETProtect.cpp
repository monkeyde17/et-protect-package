//
//  ETProtect.cpp
//  testcpp
//
//  Created by etond on 14/12/3.
//
//

#include "ETProtect.h"

bool ETProtect::isOriginPackage()
{
    unsigned int uHashValue = calculateValueFromFile();
    unsigned int uReadValue = readValueFromFile();
    
#if (ETPROTECTDEBUG)
    CCLOG("[log] -- hash %u", uHashValue);
    CCLOG("[log] -- read %u", uReadValue);
#endif
    
    if (uReadValue == 0 || uHashValue == 0)
    {
        return false;
    }
    
    return uReadValue == uHashValue;
}

unsigned int ETProtect::readValueFromFile(std::string filename /* default = config.et */)
{
    unsigned int uValue = 0;
    
    Data data = FileUtils::getInstance()->getDataFromFile(filename);
    
    if (data.getSize() > 0)
    {
        uValue = ((ETProtectData *)data.getBytes())->getHashValue();
    }

    return uValue;
}

unsigned int ETProtect::calculateValueFromFile(unsigned int seed /* default = 0x12345678 */)
{
    std::string path = "";
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 "org/cocos2dx/cpp/AppActivity",
                                                 "getPath",
                                                 "()Ljava/lang/String;");
    if (isHave)
    {
        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
        
        /* get the return value */
        path = JniHelper::jstring2string((jstring)jobj).c_str();
        CCLOG("JNI SUCCESS!");
    }
#endif
    
    unsigned int value = 0;
    
    if (path.length() > 0)
    {
        ssize_t len = 0;
        unsigned char *buf = FileUtils::getInstance()->getFileDataFromZip(path, "classes.dex", &len);
        if (buf)
        {
            value = XXH32(buf, len, seed);
        }
        delete[] buf;
    }
    
    return value;
}
