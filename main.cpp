#include <iostream>

#include "Headers/calendar.h"

#include <ctime>

#include <sstream>
#include <iomanip>

int main()
{

    time_t t = std::time(0);
    std::tm * local = std::localtime(&t);
    std::stringstream time;
    time << std::put_time(local, "%F");

    Date today(time.str());
    Calendar_DS Outlook(today);

    std::cout << "Today is “"<< Outlook <<"”. " << std::endl;

    Date my_next_birthday("2021,09,06");
    std::cout << "My next Birthday will be in “"<<my_next_birthday<<"”. " << std::endl;

    Outlook.events.emplace_back(my_next_birthday, "My Next Birthday");
    Calendar_DS::iterator begin = Outlook.it();
    Calendar_DS::iterator end = Outlook.itEvent(0);

    std::cout << Outlook.printEvents();
    std::cout <<".\n.\n."<< std::endl;
    std::cout << "After '"<<(end - begin)<<"' days..." << std::endl << std::endl;

    Outlook.set(begin += (end - begin));
    std::cout << "Today is “"<< Outlook <<"”. " << std::endl;
    std::cout << "Days to Birthday:'"<<(end - begin)<<"'. " << std::endl;

    return 0;
}
