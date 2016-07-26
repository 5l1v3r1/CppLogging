/*!
    \file memory_appender.h
    \brief Logging memory appender definition
    \author Ivan Shynkarenka
    \date 26.07.2016
    \copyright MIT License
*/

#ifndef CPPLOGGING_MEMORY_APPENDER_H
#define CPPLOGGING_MEMORY_APPENDER_H

#include "logging/appender.h"

namespace CppLogging {

//! Logging memory appender
/*!
    Logging memory appender collects all given logging records into
    growing memory buffer with the given initial capacity.

    Not thread-safe.
*/
class MemoryAppender : public Appender
{
public:
    //! Initialize memory appender with a given capacity
    /*!
         \param capacity - Memory buffer capacity (default is 0)
    */
    MemoryAppender(size_t capacity = 0) : _buffer(capacity) {}
    MemoryAppender(const MemoryAppender&) = delete;
    MemoryAppender(MemoryAppender&&) = default;
    ~MemoryAppender() = default;

    MemoryAppender& operator=(const MemoryAppender&) = delete;
    MemoryAppender& operator=(MemoryAppender&&) = default;

    // Implementation of Appender
    void AppendRecord(Record& record) override;

private:
    std::vector<uint8_t> _buffer;
};

} // namespace CppLogging

#endif // CPPLOGGING_MEMORY_APPENDER_H
