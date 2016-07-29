/*!
    \file processor.h
    \brief Logging processor interface definition
    \author Ivan Shynkarenka
    \date 26.07.2016
    \copyright MIT License
*/

#ifndef CPPLOGGING_PROCESSOR_H
#define CPPLOGGING_PROCESSOR_H

#include "logging/appender.h"
#include "logging/filter.h"
#include "logging/layout.h"

namespace CppLogging {

//! Logging processor interface
/*!
    Logging processor takes an instance of a single logging record
    and process it though all child layouts, filters and appenders.

    Thread-safe or not thread-safe.

    \see BufferProcessor
    \see SyncProcessor
    \see AsyncProcessor
*/
class Processor
{
public:
    Processor() = default;
    Processor(const Processor&) = default;
    Processor(Processor&&) = default;
    virtual ~Processor() = default;

    Processor& operator=(const Processor&) = default;
    Processor& operator=(Processor&&) = default;

    //! Get collection of child layouts
    std::vector<std::shared_ptr<Layout>>& layouts() noexcept { return _layouts; }
    //! Get collection of child filters
    std::vector<std::shared_ptr<Filter>>& filters() noexcept { return _filters; }
    //! Get collection of child appenders
    std::vector<std::shared_ptr<Appender>>& appenders() noexcept { return _appenders; }
    //! Get collection of child processors
    std::vector<std::shared_ptr<Processor>>& processors() noexcept { return _processors; }

    //! Process the given logging record through all child layouts, filters and appenders
    /*!
         Default behavior of the method will take the given logging record and process it
         in the following sequence:
         - all layouts (if any present)
         - all filters (if any present)
         - all appenders (if any present)
         - all sub processors (if any present)

         \param record - Logging record
         \return 'true' if the logging record was successfully processed, 'false' if the logging record was filtered out
    */
    virtual bool ProcessRecord(Record& record);

    //! Flush the current logging processor
    virtual void Flush();

private:
    std::vector<std::shared_ptr<Layout>> _layouts;
    std::vector<std::shared_ptr<Filter>> _filters;
    std::vector<std::shared_ptr<Appender>> _appenders;
    std::vector<std::shared_ptr<Processor>> _processors;
};

} // namespace CppLogging

#include "logging/processors/sync_processor.h"
/*
#include "logging/processors/buffer_processor.h"
#include "logging/processors/async_processor.h"
*/

#endif // CPPLOGGING_PROCESSOR_H
