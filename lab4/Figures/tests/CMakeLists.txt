add_executable(FiguresTest
               ../Point/CPoint.h
               ../Point/CPoint.cpp
               ../Shapes/IShape.h
               ../Shapes/CShape.h
               ../Shapes/CShape.cpp
               ../Shapes/LineSegment/CLineSegment.h
               ../Shapes/LineSegment/CLineSegment.cpp
               ../Shapes/SolidShapes/ISolidShape.h
               ../Shapes/SolidShapes/CSolidShape.h
               ../Shapes/SolidShapes/CSolidShape.cpp
               ../Shapes/SolidShapes/Circle/CCircle.h
               ../Shapes/SolidShapes/Circle/CCircle.cpp
               ../Shapes/SolidShapes/Rectangle/CRectangle.h
               ../Shapes/SolidShapes/Rectangle/CRectangle.cpp
               ../Shapes/SolidShapes/Triangle/CTriangle.h
               ../Shapes/SolidShapes/Triangle/CTriangle.cpp
               ../ShapeProcessor.h
               ../ShapeProcessor.cpp
               Figures.test.cpp)
target_link_libraries(FiguresTest PUBLIC catch2)
add_test(NAME FiguresTest COMMAND CarTest)
