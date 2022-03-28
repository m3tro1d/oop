#pragma once

#include "../Drawing/ICanvas.h"
#include <string>

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;

	virtual void Draw(ICanvas& canvas) const = 0;

	virtual ~IShape() = default;
};
