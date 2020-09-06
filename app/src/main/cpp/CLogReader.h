#ifndef ANALYZERAPP_CLOGREADER_H
#define ANALYZERAPP_CLOGREADER_H

#include <cstddef>
#include <string>
#include <jni.h>

#include "Regexp.h"
#include "Logger.h"

class CLogReader
{
public:
    CLogReader(JNIEnv* env, jobject javaObject);
    ~CLogReader(){};

    bool SetFilter(const char *filter);
    bool AddSourceBlock(const char* block, const size_t block_size);
private:
    std::string mFilter;
    Regexp mEngine;
    NFA_t mNfa;
    jobject mJavaObject;
    JNIEnv* mEnv;
    jmethodID mOnMatchFound;
};

#endif //ANALYZERAPP_CLOGREADER_H
