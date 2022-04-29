#include <windows.h>
#include <iostream>
#include "IUnknown.h"
#include "OBJBASE.h"
using namespace std;

typedef HRESULT_ (*FunctionType) (CLSID_, IID_, void**);

int main()
{
    FunctionType GetClassObject_;
    HINSTANCE h;

    h = LoadLibrary("C:/Users/lloid/Documents/GitHub/DLLComponentProgramming/build/Manager.dll");

    if (!h)
    {
           cout << "DLL not found !" << endl;
           return 0;
    }

    GetClassObject_ = (FunctionType) GetProcAddress(h,"GetClassObject_");

    if (!GetClassObject_)
    {
          cout << "DLL function not found !!" << endl;
          return 0;
    }

    IClassFactory2_* pF = NULL;
    HRESULT_ result = GetClassObject_(CLSID_SERVER, IID_ICLASSFACTORY2, (void**)&pF);
    if (result == S_OK_)
    {
        IY* pY = NULL;
        result = pF->CreateInstance2_(IID_IY, (void**)&pY, 3, 6);
        if (result == S_OK_)
        {
            cout << "NOD: " << pY->Nod() << endl;
        }
        else cout << "Warning" << endl;
        result = pY->QueryInterface_(IID_IX, (void**)&pY);
        if (result == S_OK_)
        {
            cout << "NOK: " << pY->Nod() << endl;
            pY->Release_();
        }
        else cout << "Warning" << endl;
        pY->Release_();
    }
    else cout << "Warning" << endl;
    pF->Release_();
    system("pause");
    return 0;
}