#include "CStringStackUnderflowError.h"

CStringStackUnderflowError::CStringStackUnderflowError()
	: std::runtime_error(MESSAGE)
{
}
