#pragma once
#include <iostream>
#include <Windows.h>
#include <Winnt.h>
#include <stdio.h>
#include <tchar.h>
using namespace std;

#define SIZE_OF_KEY_NAME 255

class EnumerateSingleKey_CURRENT_USER{
public:
	EnumerateSingleKey_CURRENT_USER(LPCWSTR  sKeyPath)
		:m_basePath(HKEY_CURRENT_USER),
		m_sKeyPath(sKeyPath)
	{

		if (ERROR_SUCCESS != RegOpenKeyExW(
			m_basePath,
			sKeyPath,
			0,
			KEY_ALL_ACCESS,
			&m_hKey
		))
		{
			cout << "Error Could not Open Key" << endl;
		}

	}

	~EnumerateSingleKey_CURRENT_USER()
	{
		RegCloseKey(m_hKey);
	}

	const LPCWSTR fnGetPath()
	{
		return m_sKeyPath;
	}


	wstring fnGetNextChild()
	{
		PCWSTR sNameOfKeyBuffer = NULL;
		DWORD sNameOfKeyBufferActuallyCopied;
		wstring sSnitialResult(L"");

		sNameOfKeyBuffer = (PCWSTR)HeapAlloc(GetProcessHeap(), 0, SIZE_OF_KEY_NAME);
		if (ERROR_SUCCESS != RegEnumKeyExW(
			m_hKey,
			m_dwSubKeyIndex,
			(LPWSTR)sNameOfKeyBuffer,
			&sNameOfKeyBufferActuallyCopied,
			NULL,
			NULL,
			NULL,
			NULL
		))
		{
			return sSnitialResult;
		}

		wstring sDirectChileNameToReturn(sNameOfKeyBuffer);
		HeapFree(GetProcessHeap(), 0, (BYTE*)sNameOfKeyBuffer);
		m_dwSubKeyIndex++;
		return sDirectChileNameToReturn;
	}

private:
	const HKEY m_basePath;
	const LPCWSTR m_sKeyPath;
	HKEY m_hKey;
	DWORD m_dwSubKeyIndex = 0;
};
