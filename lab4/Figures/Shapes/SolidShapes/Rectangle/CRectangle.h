#pragma once

#include "../../../Point/CPoint.h"
#include "../../../Utils.h"
#include "../CSolidShape.h"
#include <iomanip>
#include <sstream>

class CRectangle : public CSolidShape
{
public:
	CRectangle(CPoint leftTop, CPoint rightBottom, uint32_t outlineColor, uint32_t fillColor);
	CRectangle(CPoint leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
};
