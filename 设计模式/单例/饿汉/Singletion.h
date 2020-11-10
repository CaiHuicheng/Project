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


private:
    static CSingleton* m_pInstance;
};

CSingleton* CSingleton::m_pInstance = new(std::nothrow)CSingleton;