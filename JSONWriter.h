#ifndef __JSON_WRITER_H__
#define __JSON_WRITER_H__
#include <string>
#include <vector>
#include <map>
#include "srtuctMacro.h"


struct cJSON;
class JSONWriter
{
    cJSON* _root;
    cJSON* _cur;
public:
    JSONWriter(const char* sz);
    virtual ~JSONWriter();

    template<typename T>
    JSONWriter& operator >> (T& value)
    {
        value.serialize(*this);
        return *this;
    }

    JSONWriter& convert(const char* sz, int& value);
    JSONWriter& convert(const char* sz, float& value);
    JSONWriter& convert(const char* sz, double& value);
    JSONWriter& convert(const char* sz, unsigned int& value);
    JSONWriter& convert(const char* sz, std::string& value);
    JSONWriter& convert(const char* sz, bool& value);
    JSONWriter& convert(const char* sz, std::vector<int>& value);
    JSONWriter& convert(const char* sz, std::vector<float>& value);
    JSONWriter& convert(const char* sz, std::vector<double>& value);
    JSONWriter& convert(const char* sz, std::vector<std::string>& value);

    template<typename T>
    JSONWriter& convert(const char* sz, T& value)
    {
        cJSON* curItem = cur();
        getObject(sz);
        value.deserialize(*this);
        cur(curItem);
        return *this;
    }
    template<typename T>
    JSONWriter& convert(const char* sz, std::vector<T>& value)
    {
        cJSON* curItem = cur();
        getObject(sz);
        int size = getArraySize();
        for (int i = 0; i < size; ++i)
        {
            cJSON* lastItem = cur();
            getArrayItem(i);
            T item;
            DESERIALIZATION_1((*this), item);
            value.push_back(item);
            cur(lastItem);
        }
        cur(curItem);
        return *this;
    }
private:
    void getObject(const char* sz);
    int getArraySize()const;
    void getArrayItem(int i);
    void cur(cJSON* item) { _cur = item; }
    cJSON* cur() { return _cur; }
};


#endif