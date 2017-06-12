#pragma once
#include <utility>

typedef std::pair<int,int> Inputnumbers;
class DataAccess
{
public:
	virtual ~DataAccess() = default;
	virtual Inputnumbers GetData() const = 0;
};
