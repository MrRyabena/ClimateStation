#pragma once


#include <stdint.h>

namespace shs
{
    namespace utils
    {
        constexpr uint16_t rgb565(const uint8_t r, const uint8_t g, const uint8_t b)
        {
            return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
        }

        constexpr uint16_t rgb565(const uint32_t rgb) { return rgb565(rgb >> 16, rgb >> 8, rgb); }
    }
}
