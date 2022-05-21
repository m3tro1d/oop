add_executable(Vehicle
               Vehicles/IBasicVehicle.h
               Vehicles/IVehicle.h
               Vehicles/IBus.h
               Vehicles/Cars/ICar.h
               Vehicles/Cars/IPoliceCar.h
               Vehicles/Cars/IRacingCar.h
               Vehicles/Cars/ITaxi.h
               People/IPerson.h
               People/IPoliceMan.h
               People/IRacer.h
               main.cpp)

add_subdirectory(tests)
