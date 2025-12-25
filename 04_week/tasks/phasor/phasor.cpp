#include <cmath>
#include <iostream>
#include <format>
#include <numbers>

#define UNUSED(x) (static_cast<void>(x))

static inline double to_rad(double deg) {
    return (deg * std::numbers::pi) / 180;
}

static inline double to_deg(double rad) {
    return (rad * 180) / std::numbers::pi;
}

struct ExpTag {};
struct DegTag {};
struct AlgTag {};

class Phasor {
public:
    Phasor(double amplitude, double phase);
    Phasor(double amplitude, double phase, ExpTag tag);
    Phasor(double amplitude, double phase, DegTag tag);
    Phasor(double real, double imag, AlgTag tag);

    void SetPolar(double magnitude, double angle);
    void SetCartesian(double x, double y);
    
    double Magnitude() const;
    double Phase() const;
    double PhaseDeg() const;
    double Real() const;
    double Imag() const;

    double Abs() const;
    double Angle() const;
    double AngleDeg() const;

    Phasor operator+(const Phasor& other) const;
    Phasor operator-(const Phasor& other) const;
    Phasor operator*(const Phasor& other) const;
    Phasor operator/(const Phasor& other) const;
    Phasor operator-() const;

    Phasor operator+(double num) const;
    Phasor operator-(double num) const;
    Phasor operator*(double num) const;
    Phasor operator/(double num) const;

    Phasor operator+=(const Phasor& other);
    Phasor operator-=(const Phasor& other);
    Phasor operator*=(const Phasor& other);
    Phasor operator/=(const Phasor& other);

    bool operator==(const Phasor& other) const;
    bool operator!=(const Phasor& other) const;

    Phasor Conj() const;
    Phasor Inv() const;

private:
    double m_real;
    double m_imag;
};

Phasor::Phasor(double amplitude = 0.0, double phase = 0.0) {
    m_real = amplitude * std::cos(phase);
    m_imag = amplitude * std::sin(phase);
}

Phasor::Phasor(double amplitude, double phase, ExpTag tag) : Phasor(amplitude, phase) {
    UNUSED(tag);
}

Phasor::Phasor(double amplitude, double phase, DegTag tag) : Phasor(amplitude, to_rad(phase)) {
    UNUSED(tag);
}

Phasor::Phasor(double real, double imag, AlgTag tag) {
    UNUSED(tag);
    m_real = real;
    m_imag = imag;
}

void Phasor::SetPolar(double magnitude, double angle) {
    m_real = magnitude * std::cos(angle);
    m_imag = magnitude * std::sin(angle);
}

void Phasor::SetCartesian(double x, double y) {
    m_real = x;
    m_imag = y;
}

double Phasor::Magnitude() const {
    return std::sqrt(m_real * m_real + m_imag * m_imag);
}

double Phasor::Phase() const {
    double phase = std::atan2(m_imag, m_real);

    if (std::fabs(phase - (-std::numbers::pi)) < 1e-9) {
        return std::numbers::pi;
    }

    return std::atan2(m_imag, m_real);
}

double Phasor::PhaseDeg() const {
    return to_deg(Phase());
}

double Phasor::Real() const {
    return m_real;
}

double Phasor::Imag() const {
    return m_imag;
}

double Phasor::Abs() const {
    return Magnitude();
}

double Phasor::Angle() const {
    return Phase();
}

double Phasor::AngleDeg() const {
    return PhaseDeg();
}

Phasor Phasor::operator+(const Phasor& other) const {
    return Phasor(m_real + other.m_real, m_imag + other.m_imag, AlgTag{});
}

Phasor Phasor::operator-(const Phasor& other) const {
    return Phasor(m_real - other.m_real, m_imag - other.m_imag, AlgTag{});
}

Phasor Phasor::operator*(const Phasor& other) const {
    return Phasor(Abs() * other.Abs(), Angle() + other.Angle());
}

Phasor Phasor::operator/(const Phasor& other) const {
    return Phasor(Abs() / other.Abs(), Angle() - other.Angle());
}

Phasor Phasor::operator-() const {
    return Phasor(-m_real, -m_imag, AlgTag{});
}

Phasor Phasor::operator+(double num) const {
    return *this + Phasor(num, 0.0);
}

Phasor Phasor::operator-(double num) const {
    return *this - Phasor(num, 0.0);
}

Phasor Phasor::operator*(double num) const {
    return *this * Phasor(num, 0.0);
}

Phasor Phasor::operator/(double num) const {
    return *this / Phasor(num, 0.0);
}

Phasor operator+(double num, const Phasor& other) {
    return Phasor(num, 0.0) + other;
}

Phasor operator-(double num, const Phasor& other) {
    return Phasor(num, 0.0) - other;
}

Phasor operator*(double num, const Phasor& other) {
    return Phasor(num, 0.0) * other;
}

Phasor operator/(double num, const Phasor& other) {
    return Phasor(num, 0.0) / other;
}

Phasor Phasor::operator+=(const Phasor& other) {
    return *this = this->operator+(other);
}

Phasor Phasor::operator-=(const Phasor& other) {
    return *this = this->operator-(other);
}

Phasor Phasor::operator*=(const Phasor& other) {
    return *this = this->operator*(other);
}

Phasor Phasor::operator/=(const Phasor& other) {
    return *this = this->operator/(other);
}

bool Phasor::operator==(const Phasor& other) const {
    if ((std::fabs(m_real - other.m_real) < 1e-9) && (std::fabs(m_imag - other.m_imag) < 1e-9)) {
        return true;
    }

    return false;
}

bool Phasor::operator!=(const Phasor& other) const {
    return !(*this == other);
}

Phasor Phasor::Conj() const {
    return Phasor(m_real, -m_imag, AlgTag{});
}

Phasor Phasor::Inv() const {
    return 1.0 / (*this);
}

Phasor MakePhasorCartesian(double x, double y) {
    return Phasor(x, y, AlgTag{});
}

Phasor MakePhasorPolar(double amplitude, double phase) {
    return Phasor(amplitude, phase);
}

Phasor MakePhasorPolarDeg(double amplitude, double phase) {
    return Phasor(amplitude, phase, DegTag{});
}

std::ostream& operator<<(std::ostream& os, const Phasor& other) {
    return os << std::format("{:.3f}*e(j*{:.3f}) [{:.3f} + j*{:.3f}]", other.Abs(), other.AngleDeg(), other.Real(), other.Imag());
}