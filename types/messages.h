#pragma once
#include "types.h"

// Force 1-byte alignment for network packing
#pragma pack(push, 1)

namespace network
{
    namespace inbound
    {
        struct NewOrder {
            types::MsgType msg_type = types::MsgType::NEW_ORDER;
            types::FirmId firm_id;
            types::InstrumentId instrument_id;
            types::ClientOrderId client_order_id;
            types::AloInst alo_inst;
            types::Side side;
            types::OrderType order_type;
            types::Price price;
            types::Quantity quantity;
            types::TimeInForce time_in_force;
        };

        struct CancelOrder{
            types::MsgType msg_type = types::MsgType::CANCEL_ORDER;
            types::FirmId firm_id;
            types::ClientOrderId client_order_id;
        };

        struct EditOrder{
            types::MsgType msg_type = types::MsgType::EDIT_ORDER;
            types::FirmId firm_id;
            types::ClientOrderId original_client_order_id;
            types::ClientOrderId new_client_order_id;
            types::OrderType order_type;
            types::Price price;
            types::Quantity quantity;
            types::TimeInForce time_in_force;
        };
    }

    namespace outbound
    {
        struct OrderAccepted{
            types::MsgType msg_type = types::MsgType::ORDER_ACCEPTED;
            types::TimeStamp time_stamp;
            types::FirmId firm_id;
            types::InstrumentId instrument_id;
            types::OrderId order_id; // internal order ID
            types::ClientOrderId client_order_id;
            types::AloInst alo_inst;
            types::Side side;
            types::OrderType order_type;
            types::Price price;
            types::Quantity quantity;
            types::TimeInForce time_in_force;
        };

        struct OrderReplaced{
            types::MsgType msg_type = types::MsgType::ORDER_REPLACED;
            types::TimeStamp time_stamp;
            types::FirmId firm_id;
            types::InstrumentId instrument_id;
            types::OrderId original_order_id; // internal order ID
            types::OrderId new_order_id; // internal order ID
            types::ClientOrderId original_client_order_id;
            types::ClientOrderId new_client_order_id;
            types::AloInst alo_inst;
            types::Side side;
            types::OrderType order_type;
            types::Price price;
            types::Quantity quantity;
            types::TimeInForce time_in_force; 
        };

        struct OrderCancelled{
            types::MsgType msg_type = types::MsgType::ORDER_CANCELED;
            types::TimeStamp time_stamp;
            types::FirmId firm_id;
            types::InstrumentId instrument_id;
            types::OrderId order_id; // internal id of cancelled order
            types::ClientOrderId client_order_id;
            types::CancelReason cancel_reason;
        };

        struct OrderExecuted{
            types::MsgType msg_type = types::MsgType::ORDER_EXECUTED;
            types::TimeStamp time_stamp;
            types::FirmId firm_id;
            types::InstrumentId instrument_id;
            types::OrderId order_id; // internal id
            types::ClientOrderId client_order_id;
            types::CrossId cross_id;
            types::MatchId match_id;
            types::Side side;
            types::Price price;
            types::Quantity quantity;
            types::LiquidityInd liquidity_indicator;
        };

        struct OrderRejected{
            types::MsgType msg_type = types::MsgType::ORDER_REJECTED;
            types::TimeStamp time_stamp;
            types::MsgType rejected_order_message_type;
            types::ClientOrderId client_order_id;
            types::RejectCode reject_code;
        };
    }
}

// Restore standard compiler padding
#pragma pack(pop)