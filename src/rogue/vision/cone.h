#pragma once

// cone (start_angle_, end_angle_) not containing p
class Cone {
public:
    Cone(double start_angle, double end_angle);

    double GetStartAngle() const;
    double GetEndAngle() const;

    bool IsAngleInCone(double angle) const;
    bool IsIntersectingWith(const Cone &other) const;
    Cone UnionWithIntersectingCone(const Cone &other) const;

private:
    double start_angle_;
    double end_angle_;
};

bool operator<(const Cone &lhs, const Cone &rhs);