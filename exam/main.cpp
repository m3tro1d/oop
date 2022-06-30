// Task08.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/*
Интерфейс объектов, способных сохранять (SaveTo) и
восстанавливать (RestoreFrom) своё состояние из/в стандартных потоков чтения/записи
В случае ошибки выбрасывают исключения runtime_error
*/
class ISerializable
{
public:
	virtual void SaveTo(std::ostream& stream) const = 0;
	virtual void RestoreFrom(std::istream& stream) = 0;

	virtual ~ISerializable() = default;
};

struct Point
{
	int x = 0;
	int y = 0;
};

/* Интерфейс холста. Позволяет рисовать отрезки прямых линий и эллипсы */
class ICanvas
{
public:
	virtual void DrawLine(Point const& begin, Point const& end) = 0;
	virtual void DrawEllipse(Point const& center, unsigned int radiusX, unsigned int radiusY) = 0;

	virtual ~ICanvas() = default;
};

/* Интерфейс объектов, которые могут быть нарисованы (Draw) на холсте (canvas) */
class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;

	virtual ~ICanvasDrawable() = default;
};

/* Интерфейс объектов, умеющих говорить (Speak). */
class ISpeakable
{
public:
	virtual void Speak(std::ostream& out) const = 0;

	virtual ~ISpeakable() = default;
};

/* Прямоугольник. Может быть нарисован на холсте, а также является сериализуемым */
class Rectangle : public ICanvasDrawable
	, public ISerializable
{
public:
	Rectangle(Point const& topLeft, unsigned int width, unsigned int height)
		: m_topLeft(topLeft)
		, m_width(width)
		, m_height(height)
	{
	}

	void Draw(ICanvas& canvas) const override
	{
		Point topRight{ m_topLeft.x + static_cast<int>(m_width), m_topLeft.y };
		Point bottomRight{ m_topLeft.x + static_cast<int>(m_width), m_topLeft.y + static_cast<int>(m_height) };
		Point bottomLeft{ m_topLeft.x, m_topLeft.y + static_cast<int>(m_height) };

		canvas.DrawLine(m_topLeft, topRight);
		canvas.DrawLine(topRight, bottomRight);
		canvas.DrawLine(bottomRight, bottomLeft);
		canvas.DrawLine(bottomLeft, m_topLeft);
	}

	void SaveTo(std::ostream& stream) const override
	{
		stream << TYPE << ' '
			   << m_topLeft.x << ' ' << m_topLeft.y << ' '
			   << m_width << ' ' << m_height << ' ';
	}

	void RestoreFrom(std::istream& stream) override
	{
		std::string type;
		if (!(stream >> type) || type != TYPE)
		{
			throw std::runtime_error("invalid rectangle");
		}

		Point topLeft;
		unsigned int width;
		unsigned int height;

		if (!(stream >> topLeft.x >> topLeft.y >> width >> height))
		{
			throw std::runtime_error("invalid rectangle");
		}

		m_topLeft = topLeft;
		m_width = width;
		m_height = height;
	}

private:
	static constexpr std::string_view TYPE = "rectangle";

	Point m_topLeft;
	unsigned int m_width;
	unsigned int m_height;
};

/* Эллипс. Может быть нарисован на холсте, а также является сериализуемым */
class Ellipse : public ICanvasDrawable
	, public ISerializable
{
public:
	Ellipse(Point center, unsigned int radiusX, unsigned int radiusY)
		: m_center(center)
		, m_radiusX(radiusX)
		, m_radiusY(radiusY)
	{
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawEllipse(m_center, m_radiusX, m_radiusY);
	}

	void SaveTo(std::ostream& stream) const override
	{
		stream << TYPE << ' '
			   << m_center.x << ' ' << m_center.y << ' '
			   << m_radiusX << ' ' << m_radiusY << ' ';
	}

	void RestoreFrom(std::istream& stream) override
	{
		std::string type;
		if (!(stream >> type) || type != TYPE)
		{
			throw std::runtime_error("invalid ellipse");
		}

		Point center;
		unsigned int radiusX;
		unsigned int radiusY;

		if (!(stream >> center.x >> m_center.y >> radiusX >> radiusY))
		{
			throw std::runtime_error("invalid ellipse");
		}

		m_center = center;
		m_radiusX = radiusX;
		m_radiusY = radiusY;
	}

private:
	static constexpr std::string_view TYPE = "ellipse";

	Point m_center;
	unsigned int m_radiusX;
	unsigned int m_radiusY;
};

/* Треугольник. Может быть нарисован на холсте, а также является сериализуемым */
class Triangle : public ICanvasDrawable
	, public ISerializable
{
public:
	Triangle(Point const& point1, Point const& point2, Point const& point3)
		: m_point1(point1)
		, m_point2(point2)
		, m_point3(point3)
	{
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawLine(m_point1, m_point2);
		canvas.DrawLine(m_point2, m_point3);
		canvas.DrawLine(m_point3, m_point1);
	}

	void SaveTo(std::ostream& stream) const override
	{
		stream << TYPE << ' '
			   << m_point1.x << ' ' << m_point1.y << ' '
			   << m_point2.x << ' ' << m_point2.y << ' '
			   << m_point3.x << ' ' << m_point3.y << ' ';
	}

	void RestoreFrom(std::istream& stream) override
	{
		std::string type;
		if (!(stream >> type) || type != TYPE)
		{
			throw std::runtime_error("invalid triangle");
		}

		Point point1;
		Point point2;
		Point point3;

		if (!(stream >> point1.x >> point1.y
				>> point2.x >> point2.y
				>> point3.x >> point3.y))
		{
			throw std::runtime_error("invalid triangle");
		}

		m_point1 = point1;
		m_point2 = point2;
		m_point3 = point3;
	}

private:
	static constexpr std::string_view TYPE = "triangle";

	Point m_point1;
	Point m_point2;
	Point m_point3;
};

/* Холст. Вместо фактического рисования выводит в cout команды рисования и их параметры */
class CoutCanvas : public ICanvas
{
public:
	void DrawLine(Point const& begin, Point const& end) override
	{
		std::cout << "Draw line from (" << begin.x << ", " << begin.y << ") to "
				  << "(" << end.x << ", " << end.y << ")\n";
	}

	void DrawEllipse(Point const& center, unsigned int radiusX, unsigned int radiusY) override
	{
		std::cout << "Draw ellipse in (" << center.x << ", " << center.y << ") "
				  << "with x radius " << radiusX << " and y radius " << radiusY << "\n";
	}
};

/* Кот. Обладает координатами (в центре головы). Может быть нарисован на холсте
 может говорить (мяукая) */
class Cat : public ICanvasDrawable
	, public ISpeakable
{
public:
	explicit Cat(Point const& headCoordinates)
		: m_headCoordinates(headCoordinates)
	{
	}

	void Speak(std::ostream& out) const override
	{
		out << "Meow meow? Meow, meow meow: meow meow!\n";
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawEllipse(m_headCoordinates, RADIUS, RADIUS);
	}

private:
	static constexpr unsigned int RADIUS = 2;

	Point m_headCoordinates;
};

/* Человек. Обладает именем и годом рождения.
может говорить (называет своё имя и год рождения) */
class Person : public ISpeakable
{
public:
	Person(std::string const& name, int birthYear)
		: m_name(name)
		, m_birthYear(birthYear)
	{
	}

	void Speak(std::ostream& out) const override
	{
		out << "Hello, I am " << m_name << ". I was born in " << m_birthYear << "! OooWeee, how old I am!\n";
	}

private:
	std::string m_name;
	int m_birthYear;
};

/* Ведёт разговор с набором объектов, с которыми можно побеседовать */
void SmallTalk(std::ostream& out, std::vector<ISpeakable*> const& talkers)
{
	std::cout << "Let's talk, folks!\n\n";
	for (auto const& talker : talkers)
	{
		if (talker != nullptr)
		{
			out << "Hey, little fella! What do you have on your mind?\n";
			talker->Speak(out);
			out << "Just as I thought...\n\n";
		}
	}
}

/* Рисует набор объектов, которые можно нарисовать на переданном холсте (принимает объекты и холст) */
void Draw(ICanvas& canvas, std::vector<ICanvasDrawable*> const& drawables)
{
	for (auto const& drawable : drawables)
	{
		if (drawable != nullptr)
		{
			drawable->Draw(canvas);
		}
	}
}

/* Копирует состояние из одного сериализуемого объекта в другой */
void CopyState(const ISerializable& from, ISerializable& to)
{
	std::stringstream stream;
	from.SaveTo(stream);
	to.RestoreFrom(stream);
}

template <typename T>
void SortThree(T& a, T& b, T& c)
{
	if (a > b)
	{
		if (b > c) // a > b, b > c
		{
			std::swap(a, b);
			std::swap(b, c);
		}
		else // a > b, b < c
		{
			std::swap(a, b);
		}
	}
	else // a <= b
	{
		if (b > c) // // a <= b, b > c
		{
			std::swap(b, c);
		}
	}
}

int main()
{
	/*
	Нарисовать при помощи функции Draw домик с котиком рядом с ним:
		/\
	   /  \
	  / O  \
	 --------
	  |    |
	  |    |
	  ------
	  до 8 баллов (8-6-4)
	*/
	Triangle roof({ 2, 0 }, { 0, 3 }, { 2, 3 });
	Rectangle house({ 1, 3 }, 2, 2);
	Cat kitty({ 2, 2 });

	CoutCanvas canvas;
	Draw(canvas, { &roof, &house, &kitty });
	std::cout << '\n';

	/* Создать прямоугольник.
	 Скопировать в него при помощи CopyState состояние из прямоугольника,
	 задающего стены дома
	  до 6 баллов (6-5-3)
	*/
	Rectangle otherRect({ 1, 1 }, 12, 13);
	CopyState(house, otherRect);

	/*
	Создать человека по имени Ivanov Ivan 1980 года рождения.
	При помощи SmallTalk побеседовать с этим человеом и вышесозданным котом
	  до 6 баллов (6-5-3)
	*/
	Person ivanovIvan("Ivanov Ivan", 1980);
	SmallTalk(std::cout, { &kitty, &ivanovIvan });

	int a = 3;
	int b = 2;
	int c = 8;
	SortThree(a, b, c);
	std::cout << a << ' ' << b << ' ' << c << '\n';

	std::string aStr = "apple";
	std::string bStr = "cat";
	std::string cStr = "banana";
	SortThree(aStr, bStr, cStr);
	std::cout << aStr << ' ' << bStr << ' ' << cStr << '\n';

	return 0;
}
