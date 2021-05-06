#include "cone.h"

#include <algorithm>
#include <cmath>

Cone::Cone(double start_angle, double end_angle)
    : start_angle_(start_angle), end_angle_(end_angle) {
}

double Cone::GetStartAngle() const {
    return start_angle_;
}

double Cone::GetEndAngle() const {
    return end_angle_;
}

bool Cone::IsAngleInCone(double angle) const {
    return angle > start_angle_ && angle < end_angle_;
}

bool Cone::IsIntersectingWith(const Cone &other) const {
    return other.IsAngleInCone(GetStartAngle()) || IsAngleInCone(other.GetStartAngle());
}

Cone Cone::UnionWithIntersectingCone(const Cone &other) const {
    return Cone{std::min(GetStartAngle(), other.GetStartAngle()),
                std::max(GetEndAngle(), other.GetEndAngle())};
}

bool operator<(const Cone &lhs, const Cone &rhs) {
    return lhs.GetStartAngle() < rhs.GetStartAngle();
}