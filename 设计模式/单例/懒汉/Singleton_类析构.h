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
        18     }

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
    static CGarbo Garbo;//定义的一个静态成员变量，程序结束时，会自动调用它的析构函数。而它的析构函数，调用了delete，系统会调用单例类的析构。
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
CSingleton::CGarbo CSingleton::Garbo;