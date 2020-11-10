#pragma once

#include <iostream>

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

public:
    static CSingleton* GetInstance()
    {
        if (!m_pInstance)
        {
            m_pInstance = new CSingleton();
        }
        return m_pInstance;
    }

private:
    static CSingleton* m_pInstance;
};

CSingleton* CSingleton::m_pInstance = nullptr;