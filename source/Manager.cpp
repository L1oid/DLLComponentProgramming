#include <iostream>
#include <windows.h>
#include <fstream>
#include "IUnknown.h"
#include "OBJBASE.h"

using namespace std;

HINSTANCE hinstLib;

typedef HRESULT_ (*FunctionType) (CLSID_, IID_, void**);

extern "C" HRESULT_ __declspec(dllexport) GetClassObject(CLSID_ CLSID, IID_ IID, void** ppv)
{
    FunctionType DLLGetClassObject;
    string temp;
    string str_cls_id = to_string(CLSID);
    char path[MAX_PATH] = {};
    ifstream f("C:/Users/lloid/Documents/GitHub/DLLComponentProgramming/build/Reg.txt");
    while(f >> temp)
    {
        if (temp == str_cls_id)
        {
            f >> path;
            break;
        }
    }
    f.close();
    hinstLib = LoadLibrary(path);
    if (!hinstLib)
    {
           cout << "DLL not found !" << endl;
           return S_FALSE_;
    }
    DLLGetClassObject = (FunctionType) GetProcAddress(hinstLib, "DLLGetClassObject");
    if (!DLLGetClassObject)
    {
          cout << "DLL function not found !!" << endl;
          return S_FALSE_;
    } 
    return DLLGetClassObject(CLSID, IID, ppv);
}

extern "C" HRESULT_ __declspec(dllexport) FreeUnusedLibrires()
{
    BOOL fFreeResult;
    fFreeResult = FreeLibrary(hinstLib);
}