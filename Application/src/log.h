#ifndef __LOG_H__
#define	__LOG_H__
#include <stdio.h>
#include <stdarg.h>
#include <sys/slog.h>
#include <time.h>
#include <string.h>

#define	LOG_TO_SLOG	//write log info to slogger，or write to stdout

#define	MAJOR_ID	21111
#define MINOR_ID	200
#define	LOG_NAME	"MYM2"
inline void NewLog(int code, int severity,const char* sFunction, const char *szFormat, ...)
{
	char tmpStr[256] = "";
	va_list pArgs ;
	va_start (pArgs, szFormat) ;
#ifdef LOG_TO_SLOG
	sprintf(tmpStr, "[%s] [%s] %s", LOG_NAME, sFunction, szFormat);
	vslogf(code, severity,tmpStr, pArgs);
#else
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC, &tp);
	struct tm *thetm = localtime(&tp.tv_sec);
	sprintf(tmpStr, "[%02d:%02d:%02d.%ld][%s] [%s] %s", thetm->tm_hour,thetm->tm_min, thetm->tm_sec, tp.tv_nsec,LOG_NAME, sFunction, szFormat);
	vprintf(tmpStr, pArgs );
#endif
	va_end (pArgs) ;
}

inline void monolog(const char *szFormat, ...)
{
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC, &tp);
	char tmpStr[256] = "";
	sprintf(tmpStr, "[%d:%ld]%s", tp.tv_sec, tp.tv_nsec,szFormat);
	va_list pArgs;
	va_start (pArgs, szFormat);
	vprintf(tmpStr, pArgs );
	va_end (pArgs);

}
#define	LOGINFO(...) NewLog(_SLOG_SETCODE(MAJOR_ID, MINOR_ID), _SLOG_DEBUG1,__FUNCTION__,__VA_ARGS__)



class LOG_InOut
{
public:
	LOG_InOut(
			const int line,
			const char* func)
	{
		printf("line:[%d], func:[%s]==go into \n", line, func);
		m_func = func;
		m_line = line;
	}
	~LOG_InOut(){
		printf("line:[%d], func:[%s]==go  out \n", m_line, m_func.c_str());
	}
private:

	int m_line;
	std::string m_func;
};


#ifdef LOG_TO_SLOG//如果定义了
	#define LOG_IN_OUT
#else
	#define LOG_IN_OUT	LOG_InOut printInfo(__LINE__, __FUNCTION__);
#endif// end LOG_TO_SLOG


#endif
