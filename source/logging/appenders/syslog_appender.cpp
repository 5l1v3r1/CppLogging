/*!
    \file syslog_appender.cpp
    \brief Logging syslog appender implementation
    \author Ivan Shynkarenka
    \date 26.07.2016
    \copyright MIT License
*/

#include "logging/appenders/syslog_appender.h"

#if defined(unix) || defined(__unix) || defined(__unix__)
#include <syslog.h>
#endif

namespace CppLogging {

SyslogAppender::SyslogAppender()
{
#if defined(unix) || defined(__unix) || defined(__unix__)
    openlog(nullptr, LOG_NDELAY | LOG_PID, LOG_USER);
#endif
}

SyslogAppender::~SyslogAppender()
{
#if defined(unix) || defined(__unix) || defined(__unix__)
    closelog();
#endif
}

void SyslogAppender::AppendRecord(Record& record)
{
    // Skip logging records without layout
    if (record.raw.first == nullptr)
        return;

#if defined(unix) || defined(__unix) || defined(__unix__)
    // Setup syslog priority depends on the logging level
    int priority = LOG_INFO;
    switch (record.level)
    {
        case Level::FATAL:
            priority = LOG_CRIT;
            break;
        case Level::ERROR:
            priority = LOG_ERR;
            break;
        case Level::WARN:
            priority = LOG_WARNING;
            break;
        case Level::INFO:
            priority = LOG_INFO;
            break;
        case Level::DEBUG:
            priority = LOG_DEBUG;
            break;
    }

    // Append logging record content
    syslog(priority, "%.*s", (int)record.raw.second, record.raw.first);
#endif
}

} // namespace CppLogging
