#include "People/CPoliceMan.h"
#include "People/CRacer.h"
#include "Vehicles/Cars/CPoliceCar.h"
#include "Vehicles/Cars/CTaxi.h"
#include <iostream>

int main()
{
	std::shared_ptr<IPoliceMan> johnSmith = std::make_shared<CPoliceMan>("John Smith", "NWPD");

	std::shared_ptr<IPoliceCar> policeFord = std::make_shared<CPoliceCar>(5, MakeOfTheCar::FORD);
	policeFord->AddPassenger(johnSmith);

	std::shared_ptr<IPoliceMan> jimClark = std::make_shared<CPoliceMan>("Jim Clark", "SEPD");
	policeFord->AddPassenger(jimClark);

	std::cout << "Policemen in the car:\n";
	for (std::size_t i = 0; i < policeFord->GetPassengerCount(); i++)
	{
		auto const& policeman = policeFord->GetPassenger(i);
		std::cout << "  Name: " << policeman.GetName() << '\n'
				  << "  Department: " << policeman.GetDepartmentName() << '\n';
	}
	std::cout << '\n';

	policeFord->RemovePassenger(1);

	std::shared_ptr<IPerson> rajaGhandi = std::make_shared<CPerson>("Raja Ghandi");
	std::shared_ptr<IRacer> michaelSchumacher = std::make_shared<CRacer>("Michael Schumacher", 12);
	std::shared_ptr<ITaxi> toyotaTaxi = std::make_shared<CTaxi>(2, MakeOfTheCar::TOYOTA);
	toyotaTaxi->AddPassenger(rajaGhandi);
	toyotaTaxi->AddPassenger(michaelSchumacher);

	toyotaTaxi->RemovePassenger(0);
	toyotaTaxi->AddPassenger(jimClark);

	try
	{
		toyotaTaxi->AddPassenger(rajaGhandi);
	}
	catch (std::logic_error const& e)
	{
		std::cout << "Raja can't return.. Cause: " << e.what() << '\n';
	}

	return EXIT_SUCCESS;
}
