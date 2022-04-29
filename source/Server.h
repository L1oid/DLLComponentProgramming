#ifndef SERVER_H
#define SERVER_H
#include "IUnknown.h"
#include "OBJBASE.h"
class Server : public IX, public IY
{
private:
    int a, b, result;
    long m_cRef_;
public:
    Server();
    Server(int, int);
    ~Server();
    virtual int Nok();
    virtual int Nod();
    HRESULT_ QueryInterface_(IID_, void**);
    ULONG_ AddRef_();
    ULONG_ Release_();
};
#endif

class ServerFactory : public IClassFactory2_
{
private:
    long m_cRef_;
public:
    ServerFactory();
    ~ServerFactory();
    HRESULT_ CreateInstance_(IID_, void**);
    HRESULT_ CreateInstance2_(IID_, void**, int, int);
    HRESULT_ QueryInterface_(IID_, void**);
    ULONG_ AddRef_();
    ULONG_ Release_();
};