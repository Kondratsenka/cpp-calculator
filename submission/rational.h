#pragma once
#include <cstdlib>
#include <cinttypes>
#include <numeric>
#include <iostream>

class Rational {

public:
    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {

        if (denominator_ == 0) {
            std::abort();
        }
        // Приводим дробь к правильному формату.
        Reduction();
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
    friend std::istream& operator>>(std::istream& is, Rational& r);

    int GetNumerator() const {          // возвращаем знач. числителя
        return numerator_;
    }

    int GetDenominator() const {        // возврат знач. знаменателя
        return denominator_;
    }

    Rational Inv() const {
        return Rational{denominator_, numerator_};

    }

    Rational() : numerator_(0), denominator_(1) {}
    Rational(int numerator) : numerator_(numerator), denominator_(1) {
        Reduction();
    }
    Rational(const Rational& other) : numerator_(other.numerator_), denominator_(other.denominator_) {}



    Rational operator+(const Rational& r2) const {      // перегрузка (+)
        Rational other{*this};
        other += r2;
        return other;
    }

    Rational operator-(const Rational& r2) const {      // перегрузка (-)
        Rational other{*this};
        other -=r2;
        return other;
    }

    Rational operator*(const Rational& r2) const {            // перегрузка (*)
        Rational other{*this};
        other *=r2;
        return other;

    }

    Rational operator/(const Rational& r2)const {        //  перегрузка  (/)
        Rational other{*this};
        other /=r2;
        return other;
    }

    Rational& operator +=(const Rational& other) {      //   перегрузка  (+=)
        int chisl = (numerator_ * other.denominator_) + (denominator_ * other.numerator_);
        int znam = denominator_ * other.denominator_;
        numerator_ = chisl;
        denominator_ = znam;
        Reduction();
        return *this;

    }

    Rational& operator -=(const Rational& other) {          // перегрузка  (-=)
        int chisl = (numerator_ * other.denominator_) - (denominator_ * other.numerator_);
        int znam = denominator_ * other.denominator_;
        numerator_ = chisl;
        denominator_ = znam;
        Reduction();
        return *this;
    }

    Rational& operator *=(const Rational& other) {      // перегрузка  (*=)
        int chisl = numerator_ * other.numerator_;
        int znam = denominator_ * other.denominator_;
        numerator_ = chisl;
        denominator_ = znam;
        Reduction();
        return *this;

    }

    Rational& operator/=(const Rational& other) {      // перегрузка  (/=)
        int chisl = numerator_ * other.denominator_;
        int znam = denominator_ * other.numerator_;

        numerator_ = chisl;
        denominator_ = znam;
        Reduction();
        return *this;
    }

    Rational& operator=(const Rational& r2) = default;        // операция присваивания дробей (=)

    Rational operator+() const{                             // унарный оператор (++)
        return *this;
    }

    Rational operator-() const{                             // унарный оператор (--)
        return{-numerator_, denominator_};
    }

    bool operator==(const Rational& r) const = default;     // перегрузка равенства (==)

private:

    void Reduction() {

        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

private:

    int numerator_ = 0;      // чеслитель
    int denominator_ = 1;   // знаменатель

};

inline auto operator <=>(const Rational& lhs, const Rational& rhs) { // оператор трёхстороннего сравнения

    std::int64_t left = static_cast<std::int64_t>(lhs.GetNumerator()) * rhs.GetDenominator();
    std::int64_t right = static_cast<std::int64_t>(rhs.GetNumerator()) * lhs.GetDenominator();
    return left <=> right;

}


inline std::ostream& operator<<(std::ostream& os, const Rational& r) {  // прегруз вывода

    if(r.denominator_ == 1) {
        os<<r.numerator_;
    }
    else {
        os<<r.numerator_<<" / "<<r.denominator_;
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& r) {    // перегруз ввода
    char op;
    int numerator;
    int denominator;

    if(!(is>>std::ws>>numerator)) {
        return is;
    }

    if(is>>op && op == '/') {
        is>>denominator;
    }
    else {
        denominator = 1;
        is.putback(op);
    }

    r.numerator_ = numerator;
    r.denominator_ = denominator;

    if(r.denominator_ == 0) {
        is.setstate(std::ios::failbit);
    }
    r.Reduction();
    return is;
}


