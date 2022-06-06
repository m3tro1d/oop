#include "CBus.h"

CBus::CBus(std::size_t placeCount)
	: CVehicleImpl<IBus, IPerson>(placeCount)
{
}
