#pragma once
#include <cstdint>
#include <limits>
#include <string>
#include <types/macros.h>

namespace types
{
    enum class MsgType : char
    {
        NEW_ORDER = 'B',
        CANCEL_ORDER = 'C',
        EDIT_ORDER = 'R',
        ORDER_ACCEPTED = 'b',
        ORDER_REPLACED = 'r',
        ORDER_CANCELED = 'c',
        ORDER_EXECUTED = 'e',
        ORDER_REJECTED = 'j',
        INVALID = '\xFF'
    };

    inline auto msgTypeToString(MsgType msg_type) -> std::string
    {
        if (UNLIKELY(msg_type == MsgType::INVALID))
        {
            return "INVALID";
        }
        return std::string(1, static_cast<char>(msg_type));
    }

    typedef uint16_t FirmId;
    constexpr auto FirmId_INVALID = std::numeric_limits<FirmId>::max();
    inline auto firmIdToString(FirmId firm_id) -> std::string {
        if (UNLIKELY(firm_id == FirmId_INVALID)) {
            return "INVALID";
        }
        return std::to_string(firm_id);
    }

    typedef uint16_t InstrumentId;
    constexpr auto InstrumentId_INVALID = std::numeric_limits<InstrumentId>::max();
    inline auto instrumentIdToString(InstrumentId instrument_id) -> std::string {
        if (UNLIKELY(instrument_id == InstrumentId_INVALID)) {
            return "INVALID";
        }
        return std::to_string(instrument_id);
    }

    struct ClientOrderId {
        char data[16];
    };
    inline auto clientOrderIdToString(const ClientOrderId& client_order_id) -> std::string {
        return std::string(client_order_id.data, 16);
    }

    enum class AloInst : char
    {
        YES = 'Y',
        NO = 'N',
        INVALID = '\xFF'
    };

    inline auto aloInstToString(AloInst alo_inst) -> std::string
    {
        if (UNLIKELY(alo_inst == AloInst::INVALID))
        {
            return "INVALID";
        }
        return std::string(1, static_cast<char>(alo_inst));
    }

    enum class Side : char
    {
        BUY = 'B',
        SELL = 'S',
        INVALID = '\xFF'
    };

    inline auto sideToString(Side side) -> std::string
    {
        if (UNLIKELY(side == Side::INVALID))
        {
            return "INVALID";
        }
        return std::string(1, static_cast<char>(side));
    }

    typedef uint8_t OrderType;
    constexpr auto OrderType_INVALID = std::numeric_limits<OrderType>::max();
    inline auto orderTypeToString(OrderType order_type) -> std::string {
        if (UNLIKELY(order_type == OrderType_INVALID)) {
            return "INVALID";
        }
        return std::string(1, static_cast<char>(order_type));
    }

    typedef uint64_t Price;
    constexpr auto Price_INVALID = std::numeric_limits<Price>::max();
    inline auto priceToString(Price price) -> std::string {
        if (UNLIKELY(price == Price_INVALID)) {
            return "INVALID";
        }
        return std::to_string(price);
    }

    typedef uint16_t Quantity;
    constexpr auto Quantity_INVALID = std::numeric_limits<Quantity>::max();
    inline auto quantityToString(Quantity quantity) -> std::string {
        if (UNLIKELY(quantity == Quantity_INVALID)) {
            return "INVALID";
        }
        return std::to_string(quantity);
    }

    typedef uint8_t TimeInForce;
    constexpr auto TimeInForce_INVALID = std::numeric_limits<TimeInForce>::max();
    inline auto timeInForceToString(TimeInForce tif) -> std::string {
        if (UNLIKELY(tif == TimeInForce_INVALID)) {
            return "INVALID";
        }
        return std::to_string(static_cast<uint32_t>(tif));
    }

    typedef uint64_t TimeStamp;
    constexpr auto TimeStamp_INVALID = std::numeric_limits<TimeStamp>::max();
    inline auto timeStampToString(TimeStamp timestamp) -> std::string {
        if (UNLIKELY(timestamp == TimeStamp_INVALID)) {
            return "INVALID";
        }
        return std::to_string(timestamp);
    }

    // this is internal order id used by the exchange
    typedef uint64_t OrderId;
    constexpr auto OrderId_INVALID = std::numeric_limits<OrderId>::max();
    inline auto orderIdToString(OrderId order_id) -> std::string {
        if (UNLIKELY(order_id == OrderId_INVALID)) {
            return "INVALID";
        }
        return std::to_string(order_id);
    }

    typedef uint32_t CrossId;
    constexpr auto CrossId_INVALID = std::numeric_limits<CrossId>::max();
    inline auto crossIdToString(CrossId cross_id) -> std::string {
        if (UNLIKELY(cross_id == CrossId_INVALID)) {
            return "INVALID";
        }
        return std::to_string(cross_id);
    }

    typedef uint32_t MatchId;
    constexpr auto MatchId_INVALID = std::numeric_limits<MatchId>::max();
    inline auto matchIdToString(MatchId match_id) -> std::string {
        if (UNLIKELY(match_id == MatchId_INVALID)) {
            return "INVALID";
        }
        return std::to_string(match_id);
    }

    typedef uint8_t CancelReason;
    constexpr auto CancelReason_INVALID = std::numeric_limits<CancelReason>::max();
    inline auto cancelReasonToString(CancelReason reason) -> std::string {
        if (UNLIKELY(reason == CancelReason_INVALID)) {
            return "INVALID";
        }
        return std::string(1, static_cast<char>(reason));
    }

    typedef uint8_t LiquidityInd;
    constexpr auto LiquidityInd_INVALID = std::numeric_limits<LiquidityInd>::max();
    inline auto liquidityIndToString(LiquidityInd ind) -> std::string {
        if (UNLIKELY(ind == LiquidityInd_INVALID)) {
            return "INVALID";
        }
        return std::string(1, static_cast<char>(ind));
    }
    
    typedef uint16_t RejectCode;
    constexpr auto RejectCode_INVALID = std::numeric_limits<RejectCode>::max();
    inline auto rejectCodeToString(RejectCode code) -> std::string {
        if (UNLIKELY(code == RejectCode_INVALID)) {
            return "INVALID";
        }
        return std::to_string(code);
    }
}