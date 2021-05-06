#include "cone_union.h"

#include <cmath>

void ConeUnion::AddCone(Cone cone) {
    if (cone.GetStartAngle() > cone.GetEndAngle()) {
        AddCone(Cone{cone.GetStartAngle(), M_PI});
        AddCone(Cone{-M_PI, cone.GetEndAngle()});
        return;
    }

    auto current_cone = cones_.lower_bound(cone);
    if (current_cone != cones_.begin()) {
        --current_cone;
        if (current_cone->IsIntersectingWith(cone)) {
            cone = current_cone->UnionWithIntersectingCone(cone);
            current_cone = cones_.erase(current_cone);
        } else {
            ++current_cone;
        }
    }
    while (current_cone != cones_.end() && current_cone->IsIntersectingWith(cone)) {
        cone = current_cone->UnionWithIntersectingCone(cone);
        current_cone = cones_.erase(current_cone);
    }
    cones_.insert(cone);
}

bool ConeUnion::IsConeCovered(const Cone &cone) const {
    if (cone.GetStartAngle() > cone.GetEndAngle()) {
        return IsConeCovered(Cone{cone.GetStartAngle(), M_PI - 1e-9}) &&
               IsConeCovered(Cone{-M_PI + 1e-9, cone.GetEndAngle()});
    }

    auto cover = cones_.lower_bound(cone);
    if (cover == cones_.begin()) {
        return false;
    }
    --cover;
    return cover->GetEndAngle() > cone.GetEndAngle();
}

void ConeUnion::Reset() {
    cones_.clear();
}