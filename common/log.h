#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdarg.h>

#define LOG_FATAL 1
#define LOG_ERROR 2
#define LOG_WARN 3
#define LOG_INFO 4
#define LOG_DEBUG 5

#define MAX_LOG_FILE_SIZE 2097152

class LogFile
{
public:
	LogFile() {}
	LogFile(const char * path, int level);
	void init(const char * path, int level);
	~LogFile();

	void fatal(const char * format, ...);
	void error(const char * format, ...);
	void warn(const char * format, ...);
	void info(const char * format, ...);
	void debug(const char * format, ...);
private :
	void output(int level, const char * format, va_list ap);
	const char * getLevelStr(int level);
private :
	FILE * fp;
	int level;
};

#endif
