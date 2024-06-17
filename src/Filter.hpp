#pragma once

#include <string_view>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <sstream>
#include <format>
#include <algorithm>
#include <locale>

#include "Pipe.hpp"

class IFilter
{
public:
    virtual ~IFilter() = default;

public:
    virtual void Process() = 0;
};

class ReadFileFilter : public IFilter
{
public:
    ReadFileFilter(std::string_view fileName, StringPipe &outPipe)
        : m_FileName(fileName), m_OutputPipe(outPipe)
    {
    }

public:
    void Process() override
    {
        std::ifstream ifs{ m_FileName.data() };
        if (!ifs.is_open())
        {
            throw std::runtime_error("could not open file...");
            exit(EXIT_FAILURE);
        }

        std::vector<std::string> lineData;
        std::string temp;
        while (!ifs.eof())
        {
            std::getline(ifs, temp);
            lineData.push_back(temp);
        }

        m_OutputPipe.PutData(lineData);
    }

private:
    std::string_view m_FileName;
    StringPipe &m_OutputPipe;
};

class WriteToConsoleFilter : public IFilter
{
public:
    WriteToConsoleFilter(StringPipe &inPipe) : m_InputPipe(inPipe) {}

public:
    void Process() override
    {
        auto data = m_InputPipe.GetData();
        for (auto &d : data)
        {
            std::cout << d << std::endl;
        }
    }

private:
    StringPipe &m_InputPipe;
};

class CountWordFilter : public IFilter
{
public:
    CountWordFilter(StringPipe &inPipe, StringPipe &outPipe)
        : m_InputPipe(inPipe), m_OutputPipe(outPipe)
    {
    }

public:
    void Process() override
    {
        auto data = m_InputPipe.GetData();
        size_t totalWordCount = 0;

        std::vector<std::string> result;
        for (size_t i = 0; i < data.size(); ++i)
        {
            std::stringstream ss{ data[i] };
            std::string temp;
            size_t count = 0;
            while (ss >> temp)
                ++count;

            totalWordCount += count;
            result.emplace_back(
                std::format("Line {:02} : Word count : {}", i, count));
        }
        result.emplace_back(
            std::format(">> Total word count : {}", totalWordCount));
        m_OutputPipe.PutData(result);
    }

private:
    StringPipe &m_InputPipe;
    StringPipe &m_OutputPipe;
};

class SortWordFilter : public IFilter
{
public:
    SortWordFilter(StringPipe &inPipe, StringPipe &outPipe)
        : m_InputPipe(inPipe), m_OutputPipe(outPipe)
    {
    }

public:
    void Process() override
    {
        auto data = m_InputPipe.GetData();

        std::vector<std::string> result;
        for (auto &d : data)
        {
            std::vector<std::string> tempVector;
            std::stringstream ss{ d };
            std::string temp;
            while (ss >> temp)
                tempVector.emplace_back(temp);

            // sort words in line case insensitively
            std::sort(tempVector.begin(), tempVector.end(),
                [](const auto &a, const auto &b)
                {
                    const auto result = std::mismatch(a.cbegin(), a.cend(), b.cbegin(), b.cend(),
                        [](const unsigned char lhs, const unsigned char rhs) { return std::tolower(lhs) == std::tolower(rhs); });

                    return result.second != b.cend() &&
                           (result.first == a.cend() || std::tolower(*result.first) < std::tolower(*result.second));
                });

            ss.clear();
            for (auto &word : tempVector)
                ss << word << " ";
            result.emplace_back(ss.str());
        }

        m_OutputPipe.PutData(result);
    }

private:
    StringPipe &m_InputPipe;
    StringPipe &m_OutputPipe;
};
