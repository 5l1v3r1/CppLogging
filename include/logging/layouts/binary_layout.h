/*!
    \file binary_layout.h
    \brief Logging binary layout definition
    \author Ivan Shynkarenka
    \date 08.07.2016
    \copyright MIT License
*/

#ifndef CPPLOGGING_BINARY_LAYOUT_H
#define CPPLOGGING_BINARY_LAYOUT_H

#include "logging/layout.h"

#include <vector>

namespace CppLogging {

//! Logging binary layout
/*!
    Binary layout performs simple memory copy operation to convert
    the given logging record into the plane raw buffer.

    Not thread-safe.
*/
class BinaryLayout
{
public:
    BinaryLayout() : _buffer(1024) {}
    BinaryLayout(const BinaryLayout&) = delete;
    BinaryLayout(BinaryLayout&&) = default;
    ~BinaryLayout();

    BinaryLayout& operator=(const BinaryLayout&) = delete;
    BinaryLayout& operator=(BinaryLayout&&) = default;

    //! Layout the given logging record into a raw buffer
    /*!
         \param record - Logging record
         \return Raw buffer which contains logging record after the layout operation
    */
    std::pair<void*, size_t> LayoutRecord(const Record& record) override;

private:
    std::vector<char> _buffer;
};

} // namespace CppLogging

#endif // CPPLOGGING_BINARY_LAYOUT_H
