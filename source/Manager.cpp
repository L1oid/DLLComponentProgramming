#include <iostream>
#include <windows.h>
#include "IUnknown.h"
#include "OBJBASE.h"

using namespace std;

typedef HRESULT_ (*FunctionType) (CLSID_, IID_, void**);

extern "C" HRESULT_ __declspec(dllexport) GetClassObject_(CLSID_ CLSID, IID_ IID, void** ppv)
{
    FunctionType DLLGetClassObject_;
    HINSTANCE h;
    h = LoadLibrary("C:/Users/lloid/Documents/GitHub/DLLComponentProgramming/build/ServersDLL.dll");
    if (!h)
    {
           cout << "DLL not found !" << endl;
           return 0;
    }
    DLLGetClassObject_ = (FunctionType) GetProcAddress(h,"DLLGetClassObject_");
    if (!DLLGetClassObject_)
    {
          cout << "DLL function not found !!" << endl;
          return 0;
    } 
    return DLLGetClassObject_(CLSID, IID, ppv);
}


//FreeUnusedLibrires - проверка использования DLL