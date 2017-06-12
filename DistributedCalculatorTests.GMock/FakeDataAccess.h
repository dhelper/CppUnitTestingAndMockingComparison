#pragma once
#include "gmock/gmock.h"
#include "../DistributedCalculator/DataAccess.h"
#include "../../../../../../../Projects/vcpkg/installed/x86-windows/include/gmock/gmock-generated-function-mockers.h"

class FakeDataAccess : public DataAccess
{
public:
	MOCK_CONST_METHOD0(GetData, std::pair<int, int>());
};
