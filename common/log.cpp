#include "log.h"

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

LogFile::LogFile(const char * path, int level)
{
	this->init(path, level);
}
void LogFile::init(const char * path, int level)
{
	this->level = level;
	char * filename = 0;
	int len = 0;
	char * name = "log.txt";
	if(!path)
		len = strlen(name) + 1;
	else 
		len = strlen(path) + strlen(name) + 2;
	filename = new char [len];
	memset(filename, 0, len);
	if(path)
	{
		strcpy(filename, path);
		strcat(filename, "/");
	}

	strcat(filename, name);

	fp = fopen(filename, "ab");

	delete filename;
}

LogFile::~LogFile()
{
	if(fp) 
		fclose(fp);
}

const char * LogFile::getLevelStr(int level)
{
	switch(level)
	{
		case LOG_FATAL :
			return "FATAL";
		case LOG_ERROR :
			return "ERROR";
		case LOG_WARN :
			return "WARN";
		case LOG_INFO :
			return "INFO";
		case LOG_DEBUG :
			return "DEBUG";
		default :
			return "DEBUG";
	}
}
void LogFile::output(int level, const char * format, va_list ap)
{
	if(this->level >= level)
	{
		char newFormat[1024] = {0}; 
		//snprintf(newFormat, sizeof(newFormat), "[%s]%s", getLevelStr(level), format);
		time_t sec = time(NULL);
		tm * t = localtime(&sec);
		size_t n = strftime(newFormat, sizeof(newFormat), "[%Y-%m-%d %H:%M:%S]", t);
		sprintf(newFormat+n, "[%s]%s\n", getLevelStr(level), format);
		vfprintf(fp, newFormat, ap);
		//fprintf(fp, "[%s]%s\n", getLevelStr(level), format, *ap);
	}
	//va_end(ap);
}

void LogFile::fatal(const char * format, ...)
{
	va_list ap;
	va_start(ap, format);
	output(LOG_FATAL, format, ap);
	va_end(ap);
}

void LogFile::error(const char * format, ...)
{
	va_list ap;
	va_start(ap, format);

	output(LOG_ERROR, format, ap);
	va_end(ap);
}
void LogFile::warn(const char * format, ...)
{
	va_list ap;
	va_start(ap, format);

	output(LOG_WARN, format, ap);
	va_end(ap);
}
void LogFile::info(const char * format, ...)
{
	va_list ap;
	va_start(ap, format);

	output(LOG_INFO, format, ap);
	va_end(ap);
}
void LogFile::debug(const char * format, ...)
{
	va_list ap;
	va_start(ap, format);

	output(LOG_DEBUG, format, ap);
	va_end(ap);
}
