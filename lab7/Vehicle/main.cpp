#include "People/CPoliceMan.h"
#include "People/CRacer.h"
#include "Vehicles/Cars/CPoliceCar.h"
#include "Vehicles/Cars/CTaxi.h"
#include <iostream>

int main()
{
	std::shared_ptr<IPoliceCar> policeCar = std::make_shared<CPoliceCar>(5, MakeOfTheCar::FORD);
	std::shared_ptr<IPoliceMan> johnSmith = std::make_shared<CPoliceMan>("John Smith", "NWPD");
	std::shared_ptr<IPoliceMan> jimClark = std::make_shared<CPoliceMan>("Jim Clark", "SEPD");

	std::shared_ptr<ITaxi> taxi = std::make_shared<CTaxi>(2, MakeOfTheCar::TOYOTA);
	std::shared_ptr<IPerson> rajaGhandi = std::make_shared<CPerson>("Raja Ghandi");
	std::shared_ptr<IRacer> michaelSchumacher = std::make_shared<CRacer>("Michael Schumacher", 12);

	std::cout << "John: Tis' a fine day for some patrolling!\n"
				 "*John gets in the car*\n";
	policeCar->AddPassenger(johnSmith);

	std::cout << "Jim: Hey, partner! Seems like I'll be joining you on today's patrol.\n"
				 "John: Sounds great! Hop in.\n"
				 "*Jim gets in the car*\n\n";
	policeCar->AddPassenger(jimClark);

	std::cout << "Policemen in the car:\n";
	for (std::size_t i = 0; i < policeCar->GetPassengerCount(); i++)
	{
		auto const& policeman = policeCar->GetPassenger(i);
		std::cout << "  Name: " << policeman.GetName() << '\n'
				  << "  Department: " << policeman.GetDepartmentName() << '\n';
	}
	std::cout << '\n';

	std::cout << "John: You know, Jim, I always thought that you are a dickhead! Take this!\n"
				 "Jim: What the hell are you talking about?! That's it! I'm out!\n"
				 "*Jim gets out of the car and slams the door*\n\n";
	policeCar->RemovePassenger(1);

	std::cout << "*Meanwhile...*\n"
				 "Michael: What takes you so long? We have 15 minutes left!\n"
				 "Raja (heavy indian accent): Do not worry good sir, we'll be there in no time!\n\n";
	taxi->AddPassenger(rajaGhandi);
	taxi->AddPassenger(michaelSchumacher);

	std::cout << "Jim: STOP RIGHT THERE! GET OUT OF THE CAR YOU FUCKING SPERG OR I'LL SPLAT YOUR BRAINS ON THE BACK OF YOUR GODDAMN NICE TOYOTA!!!\n"
				 "Raja: OH WHAT THE HELL MAN!! OKAY, OKAY, CHILL!\n"
				 "*Raja gets out of the car, Jim hops in and locks the doors*\n\n";
	taxi->RemovePassenger(0);
	taxi->AddPassenger(jimClark);

	std::cout << "Michael: WHAT IN THE GODDAMN IS HAPPENING OUT THERE?!! I'M GONNA BE LATE!\n"
				 "Jim: Wha.. Are you Michael Schumacher?! You're my favorite racer! Don't worry, we'll get there in time. Faster your belt!\n"
				 "Michael: You're fucking crazy, man...\n\n";

	std::cout << "Raja: What the hell?! I left my lunch in the car!\n"
				 "*Raja tries to get in the car*\n";
	try
	{
		taxi->AddPassenger(rajaGhandi);
	}
	catch (std::logic_error const& e)
	{
		std::cout << "*Raja can't get in the car! Cause: " << e.what() << "*\n"
				  << "Raja: OH FOR FUCKS SAKE!!!\n\n";
	}

	std::cout << "The end.\n"
				 "Starring, in order of appearance:\n"
				 "  John Smith: Ryan Gosling\n"
				 "  Jim Clark: Vinnie Jones\n"
				 "  Raja Ghandi: Kumail Nanjiani\n"
				 "  Michael Schumacher: Jason Flemyng\n";
	return EXIT_SUCCESS;
}
