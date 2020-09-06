#include <jni.h>
#include <string>
#include "CLogReader.h"

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

extern "C" JNIEXPORT jlong JNICALL
Java_com_utkin_analyzerapp_AnalyzerAsyncTask_init(JNIEnv* env, jobject, jobject ref)
{
    CLogReader * pAnalyzer = new CLogReader(env, ref);
    return (jlong)pAnalyzer;
}

extern "C" JNIEXPORT void JNICALL
Java_com_utkin_analyzerapp_AnalyzerAsyncTask_deinit(JNIEnv* env, jobject, jlong logReader)
{
    CLogReader * pAnalyzer = (CLogReader *) logReader;
    delete pAnalyzer;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_utkin_analyzerapp_AnalyzerAsyncTask_setFilter(JNIEnv* env,
        jobject,
        jlong logReader,
        jbyteArray filter)
{
    int len = env->GetArrayLength(filter);
    char* buf = new char[len];
    env->GetByteArrayRegion(filter, 0, len, reinterpret_cast<jbyte*>(buf));
    CLogReader * pAnalyzer = (CLogReader *) logReader;
    pAnalyzer->SetFilter(buf);
    delete[] buf;
    return true;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_utkin_analyzerapp_AnalyzerAsyncTask_addSourceBlock(JNIEnv* env,
        jobject /* this */,
        jlong logReader,
        jbyteArray block, jint size)
{
    int len = env->GetArrayLength (block);
    char* buf = new char[len];
    env->GetByteArrayRegion(block, 0, len, reinterpret_cast<jbyte*>(buf));
    CLogReader * pAnalyzer = (CLogReader *) logReader;
    pAnalyzer->AddSourceBlock(buf, len);
    delete[] buf;
    return true;
}