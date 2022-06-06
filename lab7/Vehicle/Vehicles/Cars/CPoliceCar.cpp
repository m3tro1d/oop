#include "CPoliceCar.h"

CPoliceCar::CPoliceCar(std::size_t placeCount, MakeOfTheCar makeOfTheCar)
	: CCarImpl<IPoliceCar>(placeCount, makeOfTheCar)
{
}
