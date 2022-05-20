add_executable(Vehicle
               Vehicles/IBasicVehicle.h
               Vehicles/IVehicle.h
               Vehicles/Cars/ICar.h
               Vehicles/Cars/IPoliceCar.h
               Vehicles/Cars/IRacingCar.h
               Vehicles/Cars/ITaxi.h
               main.cpp)

add_subdirectory(tests)
