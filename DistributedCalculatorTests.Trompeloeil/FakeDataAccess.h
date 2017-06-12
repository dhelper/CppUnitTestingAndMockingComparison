#pragma once
#include "../DistributedCalculator/DataAccess.h"
#include "trompeloeil.hpp"


class FakeDataAccess : public DataAccess
{
public:
	MAKE_CONST_MOCK0(GetData, Inputnumbers());
};
