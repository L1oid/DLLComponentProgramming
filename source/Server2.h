#ifndef SERVER2_H
#define SERVER2_H
#include "IUnknown.h"
#include "OBJBASE.h"
class Server2 : public IY
{
private:
    int a, b, result;
    long m_cRef_;
public:
    Server2();
    Server2(int, int);
    ~Server2();
    virtual int Nod();
    HRESULT_ QueryInterface_(IID_, void**);
    ULONG_ AddRef_();
    ULONG_ Release_();
};
#endif

class Server2Factory : public IClassFactory2_
{
private:
    long m_cRef_;
public:
    Server2Factory();
    ~Server2Factory();
    HRESULT_ CreateInstance_(IID_, void**);
    HRESULT_ CreateInstance2_(IID_, void**, int, int);
    HRESULT_ QueryInterface_(IID_, void**);
    ULONG_ AddRef_();
    ULONG_ Release_();
};