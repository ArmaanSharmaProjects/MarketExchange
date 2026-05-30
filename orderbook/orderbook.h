#pragma once
#include <array>
#include <unordered_map>
#include <types/types.h>
#include <orderbook/order.h>

namespace orderbook {

static constexpr uint32_t     max_price_level = 4096;
static constexpr types::Price tick_size       = 100;   

struct PriceLevel {
    types::Price    price;
    types::Quantity total_qty;
    uint32_t        order_count;
    Order*          head;
    Order*          tail;
};

struct PriceLevelIndex {
    std::array<PriceLevel, max_price_level> levels;
    types::Price base_price;
    uint32_t     best_idx;

    uint32_t priceToIndex(types::Price price) const
    {
        return static_cast<uint32_t>((price - base_price) / tick_size);
    }

    types::Price indexToPrice(uint32_t idx) const
    {
        return base_price + static_cast<types::Price>(idx) * tick_size;
    }

    PriceLevel& bestLevel() { return levels[best_idx]; }
};

struct OrderBook {
    types::InstrumentId instrument_id;
    types::Price        last_traded_price; //added this so we don't have to look for last traded price in the array
    PriceLevelIndex     bids;
    PriceLevelIndex     asks;
};

struct MarketExchange {
    std::unordered_map<types::InstrumentId, OrderBook> orderbooks;

    OrderBook* getOrderBook(types::InstrumentId id)
    {
        auto it = orderbooks.find(id);
        return it != orderbooks.end() ? &it->second : nullptr;
 

    }

    // added the below method cause idk if we are going to pre fill the orderbooks with tickers or not

    OrderBook& getOrCreateOrderBook(types::InstrumentId id)
    {
        auto res = orderbooks.emplace(id, OrderBook{});
        if (res.second) res.first->second.instrument_id = id;        
        return res.first->second;
        
    }
};

} 