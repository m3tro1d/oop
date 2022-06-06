#include "CTaxi.h"

CTaxi::CTaxi(std::size_t placeCount, MakeOfTheCar makeOfTheCar)
	: CCarImpl<ITaxi>(placeCount, makeOfTheCar)
{
}
