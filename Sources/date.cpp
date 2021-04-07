#include "Headers/date.h"

#include <stdexcept>

std::istream& operator>> (std::istream &in, Date& date)
{
    char ch;
    std::string year;
    std::string month;
    std::string day;
    while (in >> ch && (ch >= '0') && (ch <= '9'))
        year += ch;
    while (in >> ch && (ch >= '0') && (ch <= '9'))
        month += ch;
    while (in >> ch && (ch >= '0') && (ch <= '9'))
        day += ch;
    date = Date(std::stoul(year), std::stoul(month), std::stoul(day));
    return in;
}

std::ostream &operator << (std::ostream& out, const Date& date)
{
    return out << date.getDayOfWeek() << " " << date.day << " "<< date.month << " " << date.year;
}

std::ostream &operator << (std::ostream& out, const Date::DayOfWeek& day)
{
    switch (day) {
    case Date::DayOfWeek::MONDAY    : return out << "Monday";
    case Date::DayOfWeek::TUESDAY   : return out << "Tuesday";
    case Date::DayOfWeek::THURSDAY  : return out << "Thursday";
    case Date::DayOfWeek::WEDNESDAY : return out << "Wednesday";
    case Date::DayOfWeek::SATURDAY  : return out << "Saturday";
    case Date::DayOfWeek::FRIDAY    : return out << "Friday";
    case Date::DayOfWeek::SUNDAY    : return out << "Sunday";
    }
    return out;
}

std::ostream &operator << (std::ostream& out, const Date::Month& month)
{
    switch (month) {
    case Date::Month::JANUARY   : return out << "January";
    case Date::Month::FEBRUARY  : return out << "February";
    case Date::Month::MARCH     : return out << "March";
    case Date::Month::APRIL     : return out << "April";
    case Date::Month::MAY       : return out << "May";
    case Date::Month::JUNE      : return out << "June";
    case Date::Month::JULY      : return out << "July";
    case Date::Month::AUGUST    : return out << "August";
    case Date::Month::SEPTEMBER : return out << "September";
    case Date::Month::OCTOBER   : return out << "October";
    case Date::Month::NOVEMBER  : return out << "November";
    case Date::Month::DECEMBER  : return out << "December";
    }
    return out;
}

size_t Date::getMaxNumberDay(const Date & date)
{
    switch (date.month) {

    case Month::FEBRUARY : return Date::isLeap(date.year)? 29: 28;

    case Month::APRIL :
    case Month::JUNE :
    case Month::SEPTEMBER :
    case Month::NOVEMBER : return 30;

    case Month::JANUARY :
    case Month::MARCH :
    case Month::MAY :
    case Month::JULY :
    case Month::AUGUST :
    case Month::OCTOBER :
    case Month::DECEMBER :
    default: return 31;
    }
}

/*
 * Assuming the year is not a leap year
 */
size_t Date::getMaxNumberDay(Date::Month month)
{
    return Date::getMaxNumberDay(Date{1970, static_cast<size_t> (month)});
}

size_t Date::getMaxNumberDay() const
{
    return Date::getMaxNumberDay(*this);
}

Date::Date(const std::string &str)
{
    std::stringstream stream(str);
    stream >> (*this);
}

Date::Date(size_t year, size_t month, size_t day)
    : year(year)
{
    if (month > static_cast<size_t> (Month::COUNT))
        throw std::runtime_error({"Month '%u'  out of range '%u'",month, static_cast<size_t> (Month::COUNT)});

    this->month = static_cast<Month>(month);

    if (day > getMaxNumberDay() && day)
        throw std::runtime_error({"Day '%u'  out of range '[1,%u]'",day, getMaxNumberDay()});

    this->day = day;
}

Date::Date(const Date &other)
    : year(other.year),month(other.month),day(other.day)
{ }

Date::DayOfWeek Date::getDayOfWeek(const Date &date)
{
    //cheating
    QDate d(date.year, static_cast<size_t> (date.month), date.day);
    return static_cast<Date::DayOfWeek>(d.dayOfWeek());
}

Date::DayOfWeek Date::getDayOfWeek() const
{
    return getDayOfWeek(*this);
}


bool Date::isLeap(size_t year){
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

bool Date::operator!=(const Date &other) const
{
    return  (year != other.year) ||
            (month != other.month) ||
            (day != other.day);
}

bool Date::operator==(const Date &other) const
{
    return  (year == other.year) &&
            (month == other.month) &&
            (day == other.day);
}

bool Date::operator<(const Date &other) const
{
    return  (year < other.year) ||
            ((year == other.year) && (month < other.month)) ||
            ((year == other.year) && (month == other.month) && (day < other.day));
}

Date &Date::operator+=(int shift)
{
    if (shift < 0) return this->operator-=(-shift);
    day += shift;
    size_t count = 0;
    while (day > getMaxNumberDay()){
        day -= getMaxNumberDay();
        size_t index_of_next_month = static_cast<size_t>(month) % static_cast<size_t>(Month::COUNT) + 1;
        if (index_of_next_month == 1)
            count++;
        month = static_cast <Month> (index_of_next_month);
    }
    year += count;
    return *this;
}

Date &Date::operator-=(int shift)
{
    if (shift < 0) return this->operator+=(-shift);
    size_t count = 0;
    while (day <= shift){
        shift -= day;
        size_t index_of_next_month = (static_cast<size_t>(month) + static_cast<size_t>(Month::COUNT) - 2) % static_cast<size_t>(Month::COUNT) + 1;
        if (index_of_next_month == static_cast<size_t>(Month::COUNT))
            count ++;
        month = static_cast <Month> (index_of_next_month);

        day = getMaxNumberDay();
    }
    day -= shift;
    year -= count;
    return *this;
}

const Date &Date::operator=(const Date &other){
    this->day   = other.day;
    this->month = other.month;
    this->year  = other.year;
    return other;
}

int64_t Date::operator-(const Date &other) const
{
    //cheating
    QDate d1(year, static_cast<size_t> (month), day);
    QDate d2(other.year, static_cast<size_t> (other.month), other.day);
    return d2.daysTo(d1);
}

Date::operator std::string() const
{
    std::stringstream out;
    out << (*this);
    return out.str();
}

