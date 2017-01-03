#include <stdarg.h>
#include <fstream>
#include <time.h>
#include "logger.h"

std::ofstream ofile;

void begin_log(const char* path)
{
	if(ofile)
		ofile.close();

	ofile.open(path, std::ios::app);
}

void end_log()
{
	if(ofile)
		ofile.close();
}

void add_log(const char *fmt, ...)
{
	if(ofile)
	{
		if(!fmt) { return; }

		va_list va_alist;
		char logbuf[256] = {0};
		time_t t;
		tm ttm;

		time(&t);
		localtime_s(&ttm, &t);
		strftime(logbuf, sizeof(logbuf), "[%H:%M:%S] ", &ttm);

		va_start (va_alist, fmt);
		_vsnprintf_s(logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), sizeof(logbuf), fmt, va_alist);
		va_end (va_alist);

		ofile << logbuf << std::endl;
	}
}