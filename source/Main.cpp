#include <windows.h>
#include <iostream>
#include "IUnknown.h"
#include "OBJBASE.h"
using namespace std;

int main()
{
    FunctionType GetClassObject;
    FunctionType2 FreeUnusedLibrires;
    HINSTANCE h;

    h = LoadLibrary("C:/Users/lloid/Documents/GitHub/DLLComponentProgramming/build/Manager.dll");
    if (!h)
    {
           cout << "DLL not found !" << endl;
           return 0;
    }

    GetClassObject = (FunctionType) GetProcAddress(h,"GetClassObject");
    if (!GetClassObject)
    {
          cout << "DLL GetClassObject not found !!" << endl;
          return 0;
    }

    FreeUnusedLibrires = (FunctionType2) GetProcAddress(h,"FreeUnusedLibrires");
    if (!FreeUnusedLibrires)
    {
          cout << "DLL FreeUnusedLibrires not found !!" << endl;
          return 0;
    }

    IClassFactory2_* pF = NULL;
    HRESULT_ result = GetClassObject(CLSID_SERVER, IID_ICLASSFACTORY2, (void**)&pF);
    if (result == S_OK_)
    {
        IY* pY = NULL;
        result = pF->CreateInstance2_(IID_IY, (void**)&pY, 3, 6);
        if (result == S_OK_)
        {
            cout << "NOD: " << pY->Nod() << endl;
            cout << "Library Status: " << FreeUnusedLibrires() << endl;
        }
        else
        {
            cout << "Warning" << endl;
            pF->Release_();
            system("pause");
            return 0;
        } 
        IX* pX = NULL;
        result = pY->QueryInterface_(IID_IX, (void**)&pX);
        if (result == S_OK_)
        {
            cout << "NOK: " << pX->Nok() << endl;
            pX->Release_();
        }
        else
        {
            cout << "Warning" << endl;
            pF->Release_();
            system("pause");
            return 0;
        }
        pY->Release_();
        cout << "Library Status: " << FreeUnusedLibrires() << endl;
        pF->Release_();
        cout << "Library Status: " << FreeUnusedLibrires() << endl;
        system("pause");
        return 0;
    }
    else
    {
        cout << "Warning" << endl;
        system("pause");
        return 0;
    } 
}