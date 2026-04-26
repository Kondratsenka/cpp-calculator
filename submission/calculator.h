#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template <typename Number>
class Calculator {
private:
    Number number_; // тек число
    std::optional<Number> mem_; // память

public:
    Calculator(Number init = {}) : number_(init) {}
    std::optional<Error> Add(Number r) {
        number_ += r;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number r) {
        number_ -= r;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number r) {
        number_ *= r;
        return std::nullopt;
    }

    std::optional<Error> Div(Number r) {
        if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            if(r == Number(0)) {
                return "Division by zero";
            }
        }

        number_ /= r;
        return  std::nullopt;
    }

    std::optional<Error> Pow(Number r) {
        if(number_ == Number(0) && r == Number(0)) {
            return "Zero power to zero";
        }

        if constexpr (std::is_integral_v<Number>) {
            if(r < Number(0)) {
                return "Integer negative power";
            }

            number_ = ::IntegerPow(number_, r);
        }
        else if constexpr (std::is_same_v<Number, Rational>) {
            if(r.GetDenominator() != 1) {
                return "Fractional power is not supported";
            }
            number_ = ::Pow(number_, r);
        }
        else {
            number_ = std::pow(static_cast<double>(number_),
                               static_cast<double>(r));
        }

        return std::nullopt;
    }

    void Save() {
        mem_ = number_;
    }

    void Load() {
        if(mem_.has_value()) {
            number_ = mem_.value();
        }
    }

    void ClearMemory() {
        mem_.reset();
    }

    bool GetHasMem() const {
        return mem_.has_value();
    }

    void Set(Number n) {
        number_ = n;
    }

    void Negate(Number n) {
        Set(n);
        Mul(-1);
    }

    Number GetNumber() const {
        return number_;
    }

    std::string GetNumberRepr() const {
        return std::to_string(number_);
    }
};
