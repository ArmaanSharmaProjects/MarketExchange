#pragma once
#pragma once
#include <cstdint>   
#include <limits>    // For std::numeric_limits
#include <string>   
#include <cstring>   // For std::memcmp
#include "types.h"

// Force 1-byte alignment for network packing
#pragma pack(push, 1)

namespace network
{
    namespace itch
    {

        // compressed 4 byte price field
        typedef uint32_t NetworkPrice;
        constexpr auto NetworkPrice_INVALID = std::numeric_limits<NetworkPrice>::max();

        inline auto networkPriceToString(NetworkPrice price) -> std::string
        {
            if (UNLIKELY(price == NetworkPrice_INVALID))
            {
                return "INVALID";
            }
            return std::to_string(price);
        }

        struct Timestamp48
        {
            uint8_t data[6];

            bool operator==(const Timestamp48 &other) const
            {
                return std::memcmp(data, other.data, 6) == 0;
            }
        };

        // Fill all 6 bytes with 0xFF to represent the absolute max value
        constexpr Timestamp48 Timestamp48_INVALID = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};

        inline auto timestamp48ToString(const Timestamp48 &ts) -> std::string
        {
            if (UNLIKELY(ts == Timestamp48_INVALID))
            {
                return "INVALID";
            }

            // Reconstruct the 6-byte array into an 8-byte uint64_t for printing
            // Note: Assuming Little-Endian CPU architecture
            uint64_t val = 0;
            val |= static_cast<uint64_t>(ts.data[0]);
            val |= static_cast<uint64_t>(ts.data[1]) << 8;
            val |= static_cast<uint64_t>(ts.data[2]) << 16;
            val |= static_cast<uint64_t>(ts.data[3]) << 24;
            val |= static_cast<uint64_t>(ts.data[4]) << 32;
            val |= static_cast<uint64_t>(ts.data[5]) << 40;

            return std::to_string(val);
        }

        struct Alpha8
        {
            char data[8];

            bool operator==(const Alpha8 &other) const
            {
                return std::memcmp(data, other.data, 8) == 0;
            }
        };

        // 0xFF byte is an unprintable character, safe for invalidating text fields
        constexpr Alpha8 Alpha8_INVALID = {{'\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF'}};

        inline auto alpha8ToString(const Alpha8 &alpha) -> std::string
        {
            if (UNLIKELY(alpha == Alpha8_INVALID))
            {
                return "INVALID";
            }

            // Convert to string and strip the trailing spaces for clean log output
            std::string str(alpha.data, 8);
            str.erase(str.find_last_not_of(' ') + 1);
            return str;
        }

        // MESSAGES

        struct AddOrderMessage
        {
            types::MsgType msg_type = types::MsgType::ITCH_ADD_ORDER;
            types::InstrumentId instrument_id;
            Timestamp48 timestamp;
            types::OrderId order_reference_number;
            types::Side buy_sell_indicator;
            types::Quantity shares;
            Alpha8 stock_ticker;
            NetworkPrice price;
        };

        struct OrderExecutedMessage
        {
            types::MsgType msg_type = types::MsgType::ITCH_ORDER_EXECUTED;
            types::InstrumentId instrument_id;
            Timestamp48 timestamp;
            types::OrderId order_reference_number;
            types::Quantity executed_shares;
            types::MatchId match_id; // Using your optimized 4-byte internal ID
        };

        // Order Cancel Message (Partial Size Reduction)
        struct OrderCancelMessage
        {
            types::MsgType msg_type = types::MsgType::ITCH_ORDER_CANCEL;
            types::InstrumentId instrument_id;
            Timestamp48 timestamp;
            types::OrderId order_reference_number;
            types::Quantity canceled_shares;
        };

        // Order Delete Message (Full Removal)
        struct OrderDeleteMessage
        {
            types::MsgType msg_type = types::MsgType::ITCH_ORDER_DELETE;
            types::InstrumentId instrument_id;
            Timestamp48 timestamp;
            types::OrderId order_reference_number;
        };

        struct OrderReplaceMessage
        {
            types::MsgType msg_type = types::MsgType::ITCH_ORDER_REPLACE;
            types::InstrumentId instrument_id;
            Timestamp48 timestamp;
            types::OrderId original_order_reference_number;
            types::OrderId new_order_reference_number;
            types::Quantity shares;
            NetworkPrice price;
        };

    }
}

#pragma pack(pop)