#pragma once

#include <set>

#include "cone.h"

class ConeUnion {
public:
    ConeUnion() = default;

    void AddCone(Cone cone);
    bool IsConeCovered(const Cone &cone) const;
    void Reset();

private:
    std::set<Cone> cones_;
};
