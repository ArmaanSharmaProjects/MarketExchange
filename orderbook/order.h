#pragma once
#include <cstdint>
#include <types/types.h>

namespace orderbook {

enum class OrderStatus : uint8_t {
    ACTIVE          = 0,
    PARTIALLY_FILLED,
    FILLED,
    CANCELLED
};

struct Order {
    types::OrderId       order_id;
    types::MatchId       match_id;

    types::ClientOrderId client_order_id;
    types::FirmId        firm_id;
    types::InstrumentId  instrument_id;

    types::Side          side;
    types::OrderType     order_type;
    types::Price         price;
    types::Quantity      quantity;
    types::Quantity      remaining_qty;
    types::TimeInForce   time_in_force;
    types::AloInst       alo_inst;

    types::TimeStamp     timestamp;
    OrderStatus          status;

    Order* next;
    Order* prev;
};

} 