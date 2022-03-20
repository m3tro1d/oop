#pragma once

#include "../Drawing/ICanvasDrawable.h"
#include <string>

class IShape : public ICanvasDrawable
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;

	virtual ~IShape() = default;
};
