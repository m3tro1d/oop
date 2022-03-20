#pragma once

#include "../Point/CPoint.h"
#include <cstdint>
#include <vector>

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void DrawLine(CPoint from, CPoint to, uint32_t lineColor) = 0;
	virtual void DrawPolygon(const std::vector<CPoint>& points, uint32_t outlineColor, uint32_t fillColor) = 0;
	virtual void DrawCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor) = 0;
};
