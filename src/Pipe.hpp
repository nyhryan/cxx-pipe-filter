#pragma once
#include <vector>
#include <string>

template <typename T>
class IPipe
{
public:
    virtual ~IPipe() = default;
public:
    virtual void PutData(const std::vector<T> &in) = 0;
    virtual std::vector<T> GetData() = 0;

protected:
    std::vector<T> m_Buffer;
};

class StringPipe : public IPipe<std::string>
{
public:
    void PutData(const std::vector<std::string> &in) override { m_Buffer = in; }
    std::vector<std::string> GetData() override { return m_Buffer; }
};