#include "ArrayService.h"
#include "ArrayModel.h"
#include "Logger.h"

void ArrayService::initializeArray(const ArrayProperties & properties, const bool randomValues)
{
	arrayModel = std::make_shared<ArrayModel>();
	if(randomValues)
	{
		arrayModel->initializeRandomData(properties);
	}
	else
	{
		arrayModel->initializeData(properties);
	}
}

std::shared_ptr<ArrayModel> ArrayService::getArrayModel() const
{
	return arrayModel;
}
