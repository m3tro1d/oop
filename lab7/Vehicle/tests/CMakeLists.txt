add_executable(VehicleTest
               ../Vehicles/IBasicVehicle.h
               ../Vehicles/IVehicle.h
               ../Vehicles/Cars/ICar.h
               ../Vehicles/Cars/IPoliceCar.h
               ../Vehicles/Cars/IRacingCar.h
               ../Vehicles/Cars/ITaxi.h
               Vehicle.test.cpp)
target_link_libraries(VehicleTest PUBLIC catch2)
add_test(NAME VehicleTest COMMAND VehicleTest)
