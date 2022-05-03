#include <iostream>
#include <windows.h>
#include <fstream>
#include "Server.h"
#include "OBJBASE.h"

using namespace std;

TCHAR path[MAX_PATH];
long global_m_cRef;

extern "C" HRESULT_ __declspec(dllexport) DLLGetClassObject(CLSID_ CLSID, IID_ IID, void** ppv)
{
    IUnknown_* pIUnknown = NULL;
    switch (CLSID) 
    {
    case CLSID_SERVER:
        pIUnknown = (IClassFactory_*) new ServerFactory;
        cout << "GetClassObject: ServerFactory connected." << endl;
        break;
    default:
        cout << "GetClassObject: connection error." << endl;
        return S_FALSE_;
        break;
    }
    return pIUnknown->QueryInterface_(IID, ppv);
}

extern "C"  HRESULT_ __declspec(dllexport) DllRegisterServer(void)
{
    string str_cls_id = to_string(CLSID_SERVER);
    string temp;
    ifstream f1("C:/Users/lloid/Documents/GitHub/DLLComponentProgramming/build/Reg.txt");
    while (f1 >> temp)
    {
        if (temp == str_cls_id)
        {
            f1.close();
            return S_OK_;
        }
    }
    f1.close();
    ofstream f2("C:/Users/lloid/Documents/GitHub/DLLComponentProgramming/build/Reg.txt", ios::app);
    f2 << CLSID_SERVER << " " << path << endl;
    f2.close();
    return S_OK_;
    
}

extern "C"  void __declspec(dllexport) DllUnregisterServer()
{

}

extern "C" HRESULT_ __declspec(dllexport) DllCanUnloadNow_()
{
    if(global_m_cRef == 0)
    {
        return S_OK_;
    }
    else return S_FALSE_;
}
 
Server::Server() 
{
    m_cRef_ = 0;
};
Server::Server(int a_p, int b_p) 
{
    a = a_p;
    b = b_p;
    m_cRef_ = 0;
};
Server::~Server() 
{
    cout << "Server.Destructor: Liquidated." << endl;
};

int Server::Nok()
{
    result = (a * b) / Nod();
	return result;
}

int Server::Nod()
{
    result = 0;
	for (int i = a; i > 0; i--)
	{
		if (a % i == 0 && b % i == 0)
		{
			result = i;
			break;
		}
	}
	return result;
}

HRESULT_ Server::QueryInterface_(IID_ IID, void** ppv) 
{
    switch (IID)
    {
    case IID_IUNKNOWN:
        *ppv = (IUnknown_*)(IX*)ppv;
        cout << "Server.QueryInterface: IUnknown connected." << endl;
        break;
    case IID_IX:
        *ppv = (IX*)this;
        cout << "Server.QueryInterface: IX connected." << endl;
        break;
    case IID_IY:
        *ppv = (IY*)this;
        cout << "Server.QueryInterface: IY connected." << endl;
        break;
    default:
        *ppv = NULL;
        cout << "Server.QueryInterface: Invalid interface" << endl;
        return S_FALSE_;
    }
    reinterpret_cast<IUnknown_*>(*ppv)->AddRef_();
    return S_OK_;
}

ULONG_ Server::AddRef_() 
{ 
    cout << "Server.AddRef = " << m_cRef_ + 1 << endl;
    cout << "Server.GlobalAddRef = " << global_m_cRef + 1 << endl;
    ++global_m_cRef;
    return ++m_cRef_; 
} 
 
ULONG_ Server::Release_()
{ 
    cout << "Server.Release = " << m_cRef_ - 1 << endl;
    if(global_m_cRef != 0)
    {
        cout << "Server.GloblaRelease = " << global_m_cRef - 1 << endl;
        --global_m_cRef;
    }
    if(--m_cRef_ == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef_;
}

ServerFactory::ServerFactory() 
{
    m_cRef_ = 0;
};
ServerFactory::~ServerFactory() 
{
    cout << "ServerFactory.Destructor: Liquidated." << endl;
};

HRESULT_ ServerFactory::CreateInstance_(IID_ IID, void** ppv)
{
    Server* server = new Server;
    cout << "Server.CreateInstance: Server connected." << endl;
    return server->QueryInterface_(IID, ppv);
};

HRESULT_ ServerFactory::CreateInstance2_(IID_ IID, void** ppv, int num1, int num2)
{
    Server* server = new Server(num1, num2);
    cout << "Server.CreateInstance2: Server connected." << endl;
    return server->QueryInterface_(IID, ppv);
};

HRESULT_ ServerFactory::QueryInterface_(IID_ IID, void** ppv)
{
    switch (IID)
    {
    case IID_ICLASSFACTORY:
        cout << "ServerFactory.QueryInterface: IClassFactory connected." << endl;
        *ppv = (IClassFactory_*)this;
        break;
    case IID_ICLASSFACTORY2:
        cout << "ServerFactory.QueryInterface: IClassFactory2 connected." << endl;
        *ppv = (IClassFactory2_*)this;
        break;
    default:
        cout << "ServerFactory.QueryInterface: Invalid interface" << endl;
        *ppv = NULL;
        return S_FALSE_;
    }
    reinterpret_cast<IUnknown_*>(*ppv)->AddRef_();
    return S_OK_;
};

ULONG_ ServerFactory::AddRef_() 
{ 
    cout << "ServerFactory.AddRef = " << m_cRef_ + 1 << endl;
    cout << "ServerFactory.GlobalAddRef = " << global_m_cRef + 1 << endl;
    ++global_m_cRef;
    return ++m_cRef_; 
} 
 
ULONG_ ServerFactory::Release_() 
{ 
    cout << "ServerFactory.Release = " << m_cRef_ - 1 << endl;
    if(global_m_cRef != 0)
    {
        cout << "ServerFactory.GloblaRelease = " << global_m_cRef - 1 << endl;
        --global_m_cRef;
    }
    if(--m_cRef_ == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef_;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    GetModuleFileName(hinstDLL, path, MAX_PATH);
    global_m_cRef = 0;
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}

//DLLUnRegisterServer - дерегестрирует DLL