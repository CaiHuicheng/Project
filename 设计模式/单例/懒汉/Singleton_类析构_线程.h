#pragma once

#include <iostream>
#include <mutex>

class CSingleton
{
private:
    CSingleton()
    {
        std::cout << "构造" << std::endl;
    }
    ~CSingleton()
    {
        std::cout << "析构" << std::endl;
    }

    class CGarbo
    {
    public:
        CGarbo()
        {
            std::cout << "成员构造" << std::endl;
        }
        ~CGarbo()
        {
            if (CSingleton::m_pInstance)
            {
                delete CSingleton::m_pInstance;CSingleton::m_pInstance = nullptr;
            }
        }
    };
public:
    static CSingleton* GetInstance()
    {
        m_mutex.lock();
        if (!m_pInstance)
        {
            m_pInstance = new CSingleton();
        }
        m_mutex.unlock();
        return m_pInstance;
    }

private:
    static CSingleton* m_pInstance;
    static std::mutex m_mutex;
    static CGarbo Garbo;
};

CSingleton* CSingleton::m_pInstance = nullptr;
std::mutex CSingleton::m_mutex;
CSingleton::CGarbo CSingleton::Garbo;