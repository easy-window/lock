#pragma once

namespace Easy 
{
	
class CLock
{
public:

	/*!
	 * @brief Init 
	 * 
	 * Initialize process lock
	 * @param sName The name of lock.
	 * @return bool true is means success.
	 */
	static bool Init(CString sName);

	/*!
	 * @brief On 
	 * 
	 * On process lock
	 * @return bool true is means success.
	 */
	static bool On();

	/*!
	 * @brief Off 
	 * 
	 * Off process lock
	 * @return bool true is means success.
	 */
	static bool Off();

	/*!
	 * @brief Release 
	 * 
	 * Release process lock
	 * @return bool true is means success.
	 */
	static bool Release();

	/*!
	 * @brief GetLastError
	 * 
	 * Get the last error code
	 * @return DWORD the error code
	 */
	static DWORD GetLastError();

	/*!
	 * @brief GetLastErrorMsg 
	 * 
	 * Get the last error message
	 * @return CString the error message
	 */
	static CString GetLastErrorMsg();

private:
	/*!
	 * @brief GetSystemError 
	 * 
	 * used to get system error and save it
	 */
	void GetSystemError();

	/*!
	 * @brief FormatLastError 
	 * 
	 * format the last error code to string
	 * @param dwLastError the error code want to format
	 * @return CString the error message
	 */
	CString FormatLastError(DWORD dwLastError);

	static CString m_sLastError;
	static DWORD m_nLastError;

	static HANDLE s_hMutex;
	static int s_nCount;
	static CString m_sName;
};
	
}
