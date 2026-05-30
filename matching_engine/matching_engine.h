#pragma once
#include <unordered_map>
#include <types/messages.h>
#include <orderbook/orderbook.h>

namespace matching_engine {

class MatchingEngine {
public:
    explicit MatchingEngine(orderbook::MarketExchange& exchange);

    void processNewOrder   (const network::inbound::NewOrder&    msg);
    void processCancelOrder(const network::inbound::CancelOrder& msg);
    void processEditOrder  (const network::inbound::EditOrder&   msg);

private:
    void tryMatch      (orderbook::OrderBook& book, orderbook::Order* incoming);
    void addToBook     (orderbook::OrderBook& book, orderbook::Order* order);
    void removeFromBook(orderbook::OrderBook& book, orderbook::Order* order);
    void removeFromSide(orderbook::PriceLevelIndex& side, orderbook::Order* order);

    orderbook::Order* allocOrder();
    void              freeOrder(orderbook::Order* order);

    orderbook::MarketExchange& exchange_;
    


    types::OrderId next_order_id_{ 0 };
    types::MatchId next_match_id_{ 0 };

    std::unordered_map<types::OrderId, orderbook::Order*> order_map_;
    std::unordered_map<uint64_t, types::OrderId>          client_order_map_;

    orderbook::Order* free_list_{ nullptr };

    

};

} 
