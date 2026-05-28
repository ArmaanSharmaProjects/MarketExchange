#pragma once
#include <map>
#include <unordered_map>
#include <types/types.h>
#include <orderbook/order.h>

namespace orderbook {

struct PriceLevel {
    types::Price    price;
    types::Quantity total_qty;
    uint32_t        order_count;
    // added above stuff for quick price level data could be useful
    Order*          head;
    Order*          tail; // add this for quick appends
};

struct PriceLevelIndex {
    std::map<types::Price, PriceLevel>            tree;
    std::unordered_map<types::Price, PriceLevel*> flat;
};

struct OrderBook {
    types::InstrumentId instrument_id;
    PriceLevelIndex      bids;
    PriceLevelIndex      asks;
};

// just labelled the orderbooks by ticker as market exchange
struct MarketExchange {
    std::unordered_map<types::InstrumentId, OrderBook> orderbooks;

    OrderBook* getOrderBook(types::InstrumentId id)
    {
        
    }

    OrderBook& getOrCreateOrderBook(types::InstrumentId id)
    {
        
    }
};

} 
