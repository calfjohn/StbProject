#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

void cocos_android_app_init (JNIEnv* env, jobject thiz) {
    LOGD("cocos_android_app_init");
    AppDelegate *pAppDelegate = new AppDelegate();
}

void callPlayVideo(const char* path){
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "playVideo", "(Ljava/lang/String;)V")) {
		jstring stringArg1 = t.env->NewStringUTF(path);

	    t.env->CallStaticVoidMethod(t.classID, t.methodID,stringArg1);
	    t.env->DeleteLocalRef(stringArg1);
	    t.env->DeleteLocalRef(t.classID);
	}
}
