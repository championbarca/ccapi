#pragma once

namespace combined_ob {
    template <size_t Precision>
    class Double {
        double value;
    public:
        Double() : value(0) {}
        Double(double value) : value(value) {}
        double getValue() const {
            return this->value;
        }
        void setValue(double value) {
            this->value = value;
        }
    };

}