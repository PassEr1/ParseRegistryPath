
#include <iostream>
#include <Windows.h>
#include <Winnt.h>
#include <stdio.h>
#include <tchar.h>
#include "EnumerateKey.h"


void printRecursiveChild(EnumerateSingleKey_CURRENT_USER& enumerator, wstring sIdentationLevel=L"")
{
    wstring sNextChildName;
    while (!(sNextChildName = std::move(enumerator.fnGetNextChild())).empty())
    {
        wcout << sIdentationLevel << sNextChildName << endl;
        wstring nextChildPath = wstring(enumerator.fnGetPath()) + L"\\" + sNextChildName;
        EnumerateSingleKey_CURRENT_USER enumeratorforChild(nextChildPath.c_str());
        printRecursiveChild(enumeratorforChild, sIdentationLevel + L"\t");

    }
}

int main()
{
    EnumerateSingleKey_CURRENT_USER enumerator(L"AppEvents");
    printRecursiveChild(enumerator);


}
