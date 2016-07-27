/*!
    \file console_appender.cpp
    \brief Logging console appender implementation
    \author Ivan Shynkarenka
    \date 26.07.2016
    \copyright MIT License
*/

#include "logging/appenders/console_appender.h"

#include "system/console.h"

#include <cstdio>

namespace CppLogging {

void ConsoleAppender::AppendRecord(Record& record)
{
    // Skip logging records without layout
    if (record.raw.first == nullptr)
        return;

    // Setup console color depends on the logging level
    switch (record.level)
    {
        case Level::NONE:
            CppCommon::Console::SetColor(CppCommon::Color::DARKGREY);
            break;
        case Level::FATAL:
            CppCommon::Console::SetColor(CppCommon::Color::WHITE, CppCommon::Color::RED);
            break;
        case Level::ERROR:
            CppCommon::Console::SetColor(CppCommon::Color::LIGHTRED);
            break;
        case Level::WARN:
            CppCommon::Console::SetColor(CppCommon::Color::YELLOW);
            break;
        case Level::INFO:
            CppCommon::Console::SetColor(CppCommon::Color::WHITE);
            break;
        case Level::DEBUG:
            CppCommon::Console::SetColor(CppCommon::Color::LIGHTMAGENTA);
            break;
        case Level::ALL:
            CppCommon::Console::SetColor(CppCommon::Color::GREY);
            break;
    }

    // Append logging record content
    std::fwrite(record.raw.first, 1, record.raw.second, stdout);

    // Reset console color
    CppCommon::Console::SetColor(CppCommon::Color::WHITE);
}

void ConsoleAppender::Flush()
{
    // Flush stream
    std::fflush(stdout);
}

} // namespace CppLogging
