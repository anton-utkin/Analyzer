#include "CLogReader.h"

CLogReader::CLogReader(JNIEnv* env, jobject javaObject):mEnv(env)
{
    mJavaObject = mEnv->NewGlobalRef(javaObject);
    jclass clazz = reinterpret_cast<jclass>(mEnv->GetObjectClass(javaObject));
    mOnMatchFound = env->GetMethodID(clazz, "onMatchFound", "(Ljava/lang/String;)V");
};

bool CLogReader::SetFilter(const char *filter)
{
    mFilter.assign(filter);
    mNfa = mEngine.toNFA(mFilter);
    if(!PRODUCTION) {
        LOGI("SetFilter() %s", mFilter.c_str());
    }
    return true;
}


bool CLogReader::AddSourceBlock(const char* block, const size_t block_size)
{
    std::vector<std::string> result;
    int markbegin = 0;
    int markend = 0;

    for (int i = 0; i < block_size; ++i) {
        if (block[i] == '\n') {
            markend = i;
            std::string str = std::string(block + markbegin, markend - markbegin);
            result.push_back(str);
            markbegin = i + 1;
        }
    }

    for(int i = 0; i < result.size(); ++i ){
        if(!PRODUCTION) {
            LOGI("AddSourceBlock() processing line %s %d", result[i].c_str(), result[i].size());
        }
        bool found = mEngine.search(mNfa, result[i]);
        if (found)
        {
            jstring line = mEnv->NewStringUTF(result[i].c_str());
            mEnv->CallVoidMethod(mJavaObject, mOnMatchFound, line);
            mEnv->DeleteLocalRef(line);
            if(!PRODUCTION) {
                LOGI("AddSourceBlock() match found %s", result[i].c_str());
            }
        }
        else {
            if(!PRODUCTION) {
                LOGI("AddSourceBlock() match not found %s", result[i].c_str());
            }
        }
    }
    return true;
}
