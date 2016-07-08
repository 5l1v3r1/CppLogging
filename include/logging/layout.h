/*!
    \file layout.h
    \brief Logging layout interface definition
    \author Ivan Shynkarenka
    \date 08.07.2016
    \copyright MIT License
*/

#ifndef CPPLOGGING_LAYOUT_H
#define CPPLOGGING_LAYOUT_H

#include "logging/record.h"

namespace CppLogging {

//! Logging layout interface
/*!
    Logging layout takes an instance of a single logging record
    and convert it into a raw buffer.

    Not thread-safe.

    \see BinaryLayout
    \see TextLayout
*/
class Layout
{
public:
    //! Layout the given logging record into a raw buffer
    /*!
         \param record - Logging record
         \return Raw buffer which contains logging record after the layout operation
    */
    virtual std::pair<void*, size_t> LayoutRecord(const Record& record) = 0;
};

} // namespace CppLogging

#include "logging/layouts/binary_layout.h"
#include "logging/layouts/text_layout.h"

#endif // CPPLOGGING_LAYOUT_H
