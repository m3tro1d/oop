add_executable(Figures
               Point/CPoint.h
               Point/CPoint.cpp
               Shapes/IShape.h
               Shapes/CShape.h
               Shapes/CShape.cpp
               Shapes/LineSegment/CLineSegment.h
               Shapes/LineSegment/CLineSegment.cpp
               Shapes/SolidShapes/ISolidShape.h
               Shapes/SolidShapes/CSolidShape.h
               Shapes/SolidShapes/CSolidShape.cpp
               Shapes/SolidShapes/Circle/CCircle.h
               Shapes/SolidShapes/Circle/CCircle.cpp
               Shapes/SolidShapes/Rectangle/CRectangle.h
               Shapes/SolidShapes/Rectangle/CRectangle.cpp
               Shapes/SolidShapes/Triangle/CTriangle.h
               Shapes/SolidShapes/Triangle/CTriangle.cpp
               ShapeProcessor.h
               ShapeProcessor.cpp
               Utils.h
               Utils.cpp
               main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

target_compile_definitions(Figures PRIVATE SFML_STATIC)

target_link_libraries(Figures ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${JPEG_LIBRARIES} ${FREETYPE_LIBRARIES})
target_include_directories(Figures PUBLIC ${SFML_INCLUDE_DIR})

add_subdirectory(tests)
