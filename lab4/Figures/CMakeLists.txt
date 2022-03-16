add_executable(Figures
               Point/CPoint.h
               Point/CPoint.cpp
               Shapes/IShape.h
               Shapes/SolidShapes/ISolidShape.h
               Shapes/SolidShapes/Circle/CCircle.h
               Shapes/SolidShapes/Circle/CCircle.cpp
               Shapes/SolidShapes/Rectangle/CRectangle.h
               Shapes/SolidShapes/Rectangle/CRectangle.cpp
               Shapes/SolidShapes/Triangle/CTriangle.h
               Shapes/SolidShapes/Triangle/CTriangle.cpp
               main.cpp)

add_subdirectory(tests)
