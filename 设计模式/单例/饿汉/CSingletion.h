#pragma once

#include <iostream>
#include <mutex>


class CSingleton
{
public:
    static CSingleton* GetInstance()
    {
        return m_pInstance;
    }
private:
    CSingleton()
    {
        std::cout << "构造" << std::endl;
    };
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
                delete CSingleton::m_pInstance;
                m_pInstance = nullptr;
            }
        }
    };
private:
    static CSingleton* m_pInstance;
    static CGarbo Garbo;
};

CSingleton* CSingleton::m_pInstance = new(std::nothrow)CSingleton;
CSingleton::CGarbo CSingleton::Garbo;