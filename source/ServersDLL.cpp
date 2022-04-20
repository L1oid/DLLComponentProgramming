#include <iostream>
#include <windows.h>
#include "Server.h"
#include "Server2.h"
#include "IUnknown.h"
#include "OBJBASE.h"

using namespace std;

extern "C" HRESULT_ __declspec(dllexport) GetClassObject(CLSID_ CLSID, IID_ IID, void** ppv)
{
    IUnknown_* pIUnknown = NULL;
    switch (CLSID) 
    {
    case CLSID_SERVER:
        pIUnknown = (IClassFactory_*) new ServerFactory;
        cout << "GetClassObject: ServerFactory connected." << endl;
        break;
    case CLSID_SERVER2:
        pIUnknown = (IClassFactory_*) new Server2Factory;
        cout << "GetClassObject: Server2Factory connected." << endl;
        break;
    default:
        cout << "GetClassObject: connection error." << endl;
        return S_FAIL;
        break;
    }
    return pIUnknown->QueryInterface(IID, ppv);
}

HRESULT_ CreateInstance(CLSID_ CLSID, IID_ IID, void** ppv)
{
    IUnknown_* pIUnknown = NULL;
    switch (CLSID) 
    {
    case CLSID_SERVER:
        pIUnknown = (IX*) new Server;
        cout << "Global.CreateInstance: Server connected." << endl;
        break;
    case CLSID_SERVER2:
        pIUnknown = (IY*) new Server2;
        cout << "Global.CreateInstance: Server2 connected." << endl;
        break;
    default:
        cout << "Global.CreateInstance: connection error." << endl;
        return S_FAIL;
        break;
    }
    return pIUnknown->QueryInterface(IID, ppv);
}

Server::Server() 
{
    m_cRef = 0;
};
Server::Server(int a_p, int b_p) 
{
    a = a_p;
    b = b_p;
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

HRESULT_ Server::QueryInterface(IID_ IID, void** ppv) 
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
        return S_FAIL;
    }
    reinterpret_cast<IUnknown_*>(*ppv)->AddRef();
    return S_OK_;
}

ULONG_ Server::AddRef() 
{ 
    cout << "Server.AddRef = " << m_cRef + 1 << endl;
    return ++m_cRef; 
} 
 
ULONG_ Server::Release()
{ 
    cout << "Server.Release = " << m_cRef - 1 << endl;
    if(--m_cRef == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
}

ServerFactory::ServerFactory() 
{
    m_cRef = 0;
};
ServerFactory::~ServerFactory() 
{
    cout << "ServerFactory.Destructor: Liquidated." << endl;
};

HRESULT_ ServerFactory::CreateInstance(IID_ IID, void** ppv)
{
    Server* server = new Server;
    cout << "Server.CreateInstance: Server connected." << endl;
    return server->QueryInterface(IID, ppv);
};

HRESULT_ ServerFactory::CreateInstance2(IID_ IID, void** ppv, int num1, int num2)
{
    Server* server = new Server(num1, num2);
    cout << "Server.CreateInstance2: Server connected." << endl;
    return server->QueryInterface(IID, ppv);
};

HRESULT_ ServerFactory::QueryInterface(IID_ IID, void** ppv)
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
        return S_FAIL;
    }
    reinterpret_cast<IUnknown_*>(*ppv)->AddRef();
    return S_OK_;
};

ULONG_ ServerFactory::AddRef() 
{ 
    cout << "ServerFactory.AddRef = " << m_cRef + 1 << endl;
    return ++m_cRef; 
} 
 
ULONG_ ServerFactory::Release() 
{ 
    cout << "ServerFactory.Release = " << m_cRef - 1 << endl;
    if(--m_cRef == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
}

Server2::Server2() 
{
    m_cRef = 0;
};
Server2::Server2(int a_p, int b_p) 
{
    a = a_p;
    b = b_p;
};
Server2::~Server2() 
{
    cout << "Server2.Destructor: Liquidated." << endl;
};

int Server2::Nod()
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

HRESULT_ Server2::QueryInterface(IID_ IID, void** ppv)
{
    switch (IID)
    {
    case IID_IUNKNOWN:
        *ppv = (IUnknown_*)(IY*)ppv;
        cout << "Server2.QueryInterface: IUnknown connected." << endl;
        break;
    case IID_IY:
        *ppv = (IY*)this;
        cout << "Server2.QueryInterface: IY connected." << endl;
        break;
    default:
        *ppv = NULL;
        cout << "Server2.QueryInterface: Invalid interface" << endl;
        return S_FAIL;
    }
    return S_OK_;
}

ULONG_ Server2::AddRef() 
{
    cout << "Server2.AddRef = " << m_cRef + 1 << endl;
    return ++m_cRef; 
} 
 
ULONG_ Server2::Release() 
{ 
    cout << "Server2.Release = " << m_cRef - 1 << endl;
    if(--m_cRef == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
}


Server2Factory::Server2Factory() 
{
    m_cRef = 0;
};
Server2Factory::~Server2Factory() 
{
    cout << "Server2Factory.Destructor: Liquidated." << endl;
};

HRESULT_ Server2Factory::CreateInstance(IID_ IID, void** ppv)
{
    Server2* server2 = new Server2;
    cout << "Server2.CreateInstance: Server2 connected." << endl;
    return server2->QueryInterface(IID, ppv);
};

HRESULT_ Server2Factory::CreateInstance2(IID_ IID, void** ppv, int num1, int num2)
{
    Server2* server2 = new Server2(num1, num2);
    cout << "Server2.CreateInstance2: Server2 connected." << endl;
    return server2->QueryInterface(IID, ppv);
};

HRESULT_ Server2Factory::QueryInterface(IID_ IID, void** ppv)
{
    switch (IID)
    {
    case IID_ICLASSFACTORY:
        cout << "Server2Factory.QueryInterface: IClassFactory connected." << endl;
        *ppv = (IClassFactory_*)this;
        break;
    case IID_ICLASSFACTORY2:
        cout << "Server2Factory.QueryInterface: IClassFactory2 connected." << endl;
        *ppv = (IClassFactory2_*)this;
        break;
    default:
        cout << "Server2Factory.QueryInterface: Invalid interface" << endl;
        *ppv = NULL;
        return S_FAIL;
    }
    return S_OK_;
}

ULONG_ Server2Factory::AddRef() 
{ 
    cout << "Server2Factory.AddRef = " << m_cRef + 1 << endl;
    return ++m_cRef; 
} 
 
ULONG_ Server2Factory::Release() 
{ 
    cout << "Server2Factory.Release = " << m_cRef - 1 << endl;
    if(--m_cRef == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
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