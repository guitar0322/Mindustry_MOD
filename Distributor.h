#pragma once
#include "Prop.h"
class ResDistribute;
class Distributor:
    public Prop
{
public:
    ResDistribute* resDistribute;
    Distributor();
    ~Distributor();
};

