#pragma once
#include <map>
#include "ccapi_cpp/ccapi_macro.h"
#include "DataTypes.hpp"

namespace combined_ob {

    template <typename Compare> // Compare is a functor.
    class Depth {
        using Double_P = Double<CCAPI_PRINT_DOUBLE_PRECISION_DEFAULT>;
        std::map<Double_P, Double_P, Compare> depth;
    public:
        void update(const std::map<Double_P, Double_P>& depth) {
            this->depth = depth;
        }
        std::map<Double_P, Double_P> getDepth() const {
            return this->depth;
        }
    };

    class OrderBook {
        using Double_P = Double<CCAPI_PRINT_DOUBLE_PRECISION_DEFAULT>;
        Depth <std::greater<Double_P>>  bids;
        Depth <std::less<Double_P>>     asks;
    public:
        void updateBids(const std::map<Double_P, Double_P>& bids) {
            this->bids.update(bids);
        }
        void updateAsks(const std::map<Double_P, Double_P>& asks) {
            this->asks.update(asks);
        }
        std::map<Double_P, Double_P> getBids() const {
            return this->bids.getDepth();
        }
        std::map<Double_P, Double_P> getAsks() const {
            return this->asks.getDepth();
        }
    };
}