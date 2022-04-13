#pragma once
#include <memory>

class ArrayModel;
struct ArrayProperties;

class ArrayService
{
public:
	void initializeArray(const ArrayProperties & properties, bool randomValues);
	std::shared_ptr<ArrayModel> getArrayModel() const;

private:
	std::shared_ptr<ArrayModel> arrayModel;
};
