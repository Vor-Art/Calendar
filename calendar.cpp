#include "calendar.h"

Calendar_DS::iterator Calendar_DS::it() const
{
    return Calendar_DS::iterator (this->date);
}

/*
 * return the iterator to event
 */
Calendar_DS::iterator Calendar_DS::itEvent(const std::vector<std::pair<Date, std::string>>::iterator &it) const
{
    return Calendar_DS::iterator (it->first);
}

Calendar_DS::iterator Calendar_DS::itEvent(size_t index) const
{
    return Calendar_DS::iterator (events.at(index).first);
}

void Calendar_DS::set(const Calendar_DS::iterator &value)
{
    this->date = (*value);
}

std::string Calendar_DS::printEvents(){
    std::stringstream list;
    list << std::endl << "List of events:" << std::endl;
    for (auto [date,name]: events)
        list << "\t["<< date<<"] : '"<< name <<"' - "<< date - this->date <<" days left"<< std::endl;
    list << std::endl;
    return list.str();
}

Calendar_DS::operator std::string() const
{
    return static_cast<std::string>(date);
}

std::ostream &operator<< (std::ostream &out, const Calendar_DS &calendar)
{
    return out << calendar.date;
}

std::istream &operator >> (std::istream &in, Calendar_DS& calendar)
{
    Date date;
    in >> date;
    calendar.date = date;
    return in;
}

Calendar_DS::Calendar_DS(const std::string &str)
    :date(str), events()
{ }

Calendar_DS::Calendar_DS(const Date  & date)
    :date(date), events()
{ }

Calendar_DS::Calendar_DS(const Calendar_DS &oteher)
    : date(oteher.date), events()
{ }

Calendar_DS::iterator::iterator(const Calendar_DS::iterator &it)
    : p(it.p)
{ }

bool Calendar_DS::iterator::operator!=(const Calendar_DS::iterator &other) const
{
    return p != other.p;
}

bool Calendar_DS::iterator::operator==(const Calendar_DS::iterator &other) const
{
    return p == other.p;
}

bool Calendar_DS::iterator::operator<(const Calendar_DS::iterator &other) const
{
    return p < other.p;
}

bool Calendar_DS::iterator::operator<=(const Calendar_DS::iterator &other) const
{
    return p < other.p || p == other.p;
}

bool Calendar_DS::iterator::operator>(const Calendar_DS::iterator &other) const
{
    return other.p < p;
}

bool Calendar_DS::iterator::operator>=(const Calendar_DS::iterator &other) const
{
    return !(p < other.p);
}

const Calendar_DS::iterator &Calendar_DS::iterator::operator=(const Calendar_DS::iterator  &other)
{
    p = other.p;
    return other;
}

Date &Calendar_DS::iterator::operator*()
{
    return p;
}

const Date Calendar_DS::iterator::operator*() const
{
    return p;
}

const Calendar_DS::iterator &Calendar_DS::iterator::operator+=(size_t shift)
{
    p += shift;
    return *this;
}

const Calendar_DS::iterator &Calendar_DS::iterator::operator-=(size_t shift)
{
    p += -shift;
    return *this;
}

const Calendar_DS::iterator &Calendar_DS::iterator::operator++()
{
    p += 1;
    return *this;
}

const Calendar_DS::iterator &Calendar_DS::iterator::operator--()
{
    p += 1;
    return *this;
}

const Calendar_DS::iterator Calendar_DS::iterator::operator++(int)
{
    const Calendar_DS::iterator tmp(p);
    p += 1;
    return tmp;
}

const Calendar_DS::iterator Calendar_DS::iterator::operator--(int)
{
    Calendar_DS::iterator tmp(*this);
    p += -1;
    return tmp;
}

const Calendar_DS::iterator Calendar_DS::iterator::operator+(size_t shift) const
{
    Calendar_DS::iterator tmp(p);
    return tmp+=shift;
}

const Calendar_DS::iterator Calendar_DS::iterator::operator-(size_t shift) const
{
    Calendar_DS::iterator tmp(*this);
    return tmp -= shift;
}

int64_t Calendar_DS::iterator::operator-(const Calendar_DS::iterator &other) const
{
    return p - other.p;
}

Calendar_DS::iterator::iterator(const Date &p)
    : p(p)
{}
