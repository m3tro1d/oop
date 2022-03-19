#pragma once

#include "../../../Point/CPoint.h"
#include "../CSolidShape.h"
#include "../../../Utils.h"
#include <cmath>
#include <iomanip>
#include <sstream>

class CCircle : public CSolidShape
{
public:
	CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	CPoint GetCenter() const;
	double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
};
