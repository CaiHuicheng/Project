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
        static CSingleton Instance;
        return &Instance;
    }

};