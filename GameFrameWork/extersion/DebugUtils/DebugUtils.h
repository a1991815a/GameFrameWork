#ifndef __DEBUGUTILS__
#define __DEBUGUTILS__
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>

#define DEBUG_BUFSIZE 10240
#define LOG_DIR		"../LOG"
#define LOG_FILE	LOG_DIR##"/"##"log.txt"

#define _debugUtils			DebugUtils::getInstance()

#define LOG_E(MSG, ...) _debugUtils->log_error(MSG, __VA_ARGS__)
#define LOG_D(MSG, ...) _debugUtils->log_debug(MSG, __VA_ARGS__)
#define LOG_I(MSG, ...) _debugUtils->log_info(MSG, __VA_ARGS__)
#define LOG_W(MSG, ...) _debugUtils->log_warning(MSG, __VA_ARGS__)

#define LOG_EF(MSG, ...) _debugUtils->log_error_f(MSG, __VA_ARGS__)
#define LOG_DF(MSG, ...) _debugUtils->log_debug_f(MSG, __VA_ARGS__)
#define LOG_IF(MSG, ...) _debugUtils->log_info_f(MSG, __VA_ARGS__)
#define LOG_WF(MSG, ...) _debugUtils->log_warning_f(MSG, __VA_ARGS__)

class DebugUtils{
public:
	static DebugUtils* getInstance();
	static void destroyInstance();
private:
	static DebugUtils* m_instance;
	DebugUtils();
	~DebugUtils();
public:
	void log_error(const char* format, ...);
	void log_debug(const char* format, ...);
	void log_info(const char* format, ...);
	void log_warning(const char* format, ...);

	void log_error_f(const char* format, ...);
	void log_debug_f(const char* format, ...);
	void log_info_f(const char* format, ...);
	void log_warning_f(const char* format, ...);
private:
	char*		m_pDebugBufArray;		//DEBUG缓冲区
	FILE*		m_pFile;				//Log文件
	int			m_iCurLen;				//本次长度
};
#endif