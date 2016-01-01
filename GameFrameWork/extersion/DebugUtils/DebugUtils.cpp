#include "DebugUtils.h"
#include <io.h>
#include <direct.h>

DebugUtils* DebugUtils::m_instance = nullptr;

DebugUtils::DebugUtils()
{
	m_pDebugBufArray = new char[DEBUG_BUFSIZE];
	memset(m_pDebugBufArray, 0, DEBUG_BUFSIZE);
	_finddata_t file_data = { 0 };
	int file_handle = _findfirst(LOG_DIR, &file_data);
	if (file_handle == -1)
		_mkdir(LOG_DIR);
	fopen_s(&m_pFile, LOG_FILE, "wb+");
}

DebugUtils::~DebugUtils()
{
	if(m_pDebugBufArray)
		delete m_pDebugBufArray;
	if(m_pFile)
		fclose(m_pFile);
}

DebugUtils* DebugUtils::getInstance()
{
	if(m_instance == nullptr)
		m_instance = new DebugUtils();
	return m_instance;
}

void DebugUtils::destroyInstance()
{
	if(m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

void DebugUtils::log_error( const char* format, ... )
{
	va_list ap;
	va_start(ap, format);
	m_iCurLen = vsprintf_s(
		m_pDebugBufArray, DEBUG_BUFSIZE, 
		format, ap);
	va_end(ap);
	OutputDebugStringA("Error: ");
	OutputDebugStringA(m_pDebugBufArray);
	OutputDebugStringA("\n");
}

void DebugUtils::log_debug( const char* format, ... )
{
	va_list ap;
	va_start(ap, format);
	m_iCurLen = vsprintf_s(
		m_pDebugBufArray, DEBUG_BUFSIZE, 
		format, ap);
	va_end(ap);
	OutputDebugStringA("Debug: ");
	OutputDebugStringA(m_pDebugBufArray);
	OutputDebugStringA("\n");
}

void DebugUtils::log_info( const char* format, ... )
{
	va_list ap;
	va_start(ap, format);
	m_iCurLen = vsprintf_s(
		m_pDebugBufArray, DEBUG_BUFSIZE, 
		format, ap);
	va_end(ap);
	OutputDebugStringA("Info: ");
	OutputDebugStringA(m_pDebugBufArray);
	OutputDebugStringA("\n");
}

void DebugUtils::log_warning( const char* format, ... )
{
	va_list ap;
	va_start(ap, format);
	m_iCurLen = vsprintf_s(
		m_pDebugBufArray, DEBUG_BUFSIZE, 
		format, ap);
	va_end(ap);
	OutputDebugStringA("Warning: ");
	OutputDebugStringA(m_pDebugBufArray);
	OutputDebugStringA("\n");
}

void DebugUtils::log_error_f( const char* format, ... )
{
	va_list ap;
	va_start(ap, format);
	m_iCurLen = vsprintf_s(
		m_pDebugBufArray, DEBUG_BUFSIZE, 
		format, ap);
	va_end(ap);

	fwrite("Error: ", 1, 7, m_pFile);
	fwrite(m_pDebugBufArray, 1, m_iCurLen, m_pFile);
	fwrite("\r\n", 1, 2, m_pFile);
}

void DebugUtils::log_debug_f( const char* format, ... )
{
	va_list ap;
	va_start(ap, format);
	m_iCurLen = vsprintf_s(
		m_pDebugBufArray, DEBUG_BUFSIZE, 
		format, ap);
	va_end(ap);
	fwrite("Debug: ", 1, 7, m_pFile);
	fwrite(m_pDebugBufArray, 1, m_iCurLen, m_pFile);
	fwrite("\r\n", 1, 2, m_pFile);
}

void DebugUtils::log_info_f( const char* format, ... )
{
	va_list ap;
	va_start(ap, format);
	m_iCurLen = vsprintf_s(
		m_pDebugBufArray, DEBUG_BUFSIZE, 
		format, ap);
	va_end(ap);
	fwrite("Info: ", 1, 6, m_pFile);
	fwrite(m_pDebugBufArray, 1, m_iCurLen, m_pFile);
	fwrite("\r\n", 1, 2, m_pFile);
}

void DebugUtils::log_warning_f( const char* format, ... )
{
	va_list ap;
	va_start(ap, format);
	m_iCurLen = vsprintf_s(
		m_pDebugBufArray, DEBUG_BUFSIZE, 
		format, ap);
	va_end(ap);
	fwrite("Warning: ", 1, 9, m_pFile);
	fwrite(m_pDebugBufArray, 1, m_iCurLen, m_pFile);
	fwrite("\r\n", 1, 2, m_pFile);
}
