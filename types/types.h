#pragma once
#include <cstdint>
#include <limits>
#include <string>
#include <types/macros.h>

namespace types {
    typedef uint8_t MsgType;
    constexpr auto MsgType_INVALID = std::numeric_limits<MsgType>::max();
    inline auto msgTypeToString(MsgType msg_type) -> std::string {
        if (UNLIKELY(msg_type == MsgType_INVALID)) {
            return "INVALID";
        }
        return std::to_string(static_cast<uint32_t>(msg_type));
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

    typedef uint8_t AloInst;
    constexpr auto AloInst_INVALID = std::numeric_limits<AloInst>::max();
    inline auto aloInstToString(AloInst alo_inst) -> std::string {
        if (UNLIKELY(alo_inst == AloInst_INVALID)) {
            return "INVALID";
        }
        return std::to_string(static_cast<uint32_t>(alo_inst));
    }

    typedef uint8_t Side;
    constexpr auto Side_INVALID = std::numeric_limits<Side>::max();
    inline auto sideToString(Side side) -> std::string {
        if (UNLIKELY(side == Side_INVALID)) {
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
}