#ifndef __LOGGER_H__
#define __LOGGER_H__

void begin_log(const char* path);
void end_log();
void add_log(const char* fmt, ...);

#endif