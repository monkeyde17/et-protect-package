//
//  ETProtect.h
//  testcpp
//
//  Created by etond on 14/12/3.
//
//

#ifndef __ET_PROTECT__
#define __ET_PROTECT__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

#include "ETProtectData.h"
#include "xxhash/xxhash.h"

#define ETPROTECTDEBUG (false)

USING_NS_CC;

class ETProtect
{
public:
    /**
     * test the APK package
     *
     * @return
     *      whether package is origin
     *
     * @date 
     *      20141103
     *
     * @author
     *      etond
     */
    static bool isOriginPackage();
    
private:
    
    /**
     * read from file
     * get the hash value
     *
     * @return
     *      the hash value
     *      if open error, return 0
     *
     * @date 
     *      20141103
     *
     * @author
     *      etond
     */
    static unsigned int readValueFromFile(std::string filename = "config.et");
    
    
    /**
     * get the classes.dex file's hash value
     *
     * @return 
     *      the hash value
     *      if classes.dex open error, return 0
     *
     * @date 
     *      20141103
     *
     * @author
     *      etond
     */
    static unsigned int calculateValueFromFile(unsigned int seed = 0x12345678);
    
};

#endif
