#include "StdAfx.h"
#include "Lock.h"

namespace Easy 
{

CString m_sLastError;
DWORD m_nLastError = 0;
HANDLE CLock::s_hMutex = NULL;
int CLock::s_nCount = 0;
CString CLock::m_sName;

bool CLock::Init( CString sName )
{
	s_nCount = 0;
	m_sName = sName;
	s_hMutex = OpenMutex(SYNCHRONIZE, FALSE, sName.GetBuffer());
	sName.ReleaseBuffer();
	if (s_hMutex != NULL) GetSystemError();
	if (s_hMutex != NULL) return true;
	s_hMutex = CreateMutex(NULL, false, sName.GetBuffer());
	sName.ReleaseBuffer();
	if (s_hMutex != NULL) GetSystemError();
	return NULL == s_hMutex;
}

bool CLock::On()
{
	if (s_nCount++ > 0) {
		return true;
	}
	if (s_hMutex == NULL) Init(m_sName);
	if (s_hMutex == NULL) return false;
	return WAIT_OBJECT_0 == WaitForSingleObject(s_hMutex, INFINITE);
}

bool CLock::Off()
{
	if (--s_nCount > 0) {
		return true;
	}
	if (s_hMutex == NULL) return false;
	bool bSuccess = ReleaseMutex(s_hMutex);
	if (!bSuccess) GetSystemError();
	return bSuccess;
}

bool CLock::Release()
{
	if (s_hMutex == NULL) return false;
	bool bSuccess = CloseHandle(s_hMutex);
	if (!bSuccess) GetSystemError();
	return bSuccess;
}


CString CLock::GetLastErrorMsg()
{
	return  m_sLastError;
}

DWORD CLock::GetLastError()
{
	return  m_nLastError;
}

CString CLock::FormatLastError( DWORD dwLastError )
{
	LPVOID lpMsgBuf;
	CString sErrMsg = _T("");

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL);

	sErrMsg.Format(_T("%s"), lpMsgBuf);
	LocalFree(lpMsgBuf);

	return sErrMsg;
}

void CLock::GetSystemError()
{
	LPVOID lpMsgBuf;
	m_nLastError = ::GetLastError(); 

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		m_nLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL);

	m_sLastError.Format(_T("Error Code: %d.\r\nError Message: %s"), m_nLastError, lpMsgBuf);
	LocalFree(lpMsgBuf);
}

}