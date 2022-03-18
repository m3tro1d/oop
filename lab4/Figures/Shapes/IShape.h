#pragma once

#include <string>

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0; // TODO: encapsulate working with outline and fill colors in an abstract class

	virtual ~IShape() = default;
};
