#ifndef PLANE_H_
#define PLANE_H_

#include "position.h"

namespace Tracer{
    struct Plane{
    Plane();
    Plane(Position UL, Position LL, Position UR, Position LR) : 
    upper_left(UL),
    lower_left(LL),
    upper_right(UR),
    lower_right(LR)
    {}
    Position upper_left;
    Position lower_left;
    Position upper_right;
    Position lower_right;

};
}
#endif