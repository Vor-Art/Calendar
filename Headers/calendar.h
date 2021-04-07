#ifndef CALENDAR_DS_H
#define CALENDAR_DS_H
#include <string>
#include <iterator>
#include <memory>
#include <vector>
#include <sstream>
#include "date.h"

class Calendar_DS
{
    Date date;
public:
    std::vector<std::pair<Date, std::string>> events;

    class iterator;
    friend class iterator;

    explicit Calendar_DS(const std::string& str);
    explicit Calendar_DS(const Date& date);
    Calendar_DS(const Calendar_DS& oteher);

    iterator it() const;
    iterator itEvent(const std::vector<std::pair<Date, std::string>>::iterator& it) const;
    iterator itEvent(size_t index) const;

    void set( iterator const &value);

    std::string printEvents();

    friend std::ostream &operator << (std::ostream& out, const Calendar_DS& calendar);
    friend std::istream &operator >> (std::istream &in, Calendar_DS& calendar);
    explicit operator std::string() const;
};

class Calendar_DS::iterator: public std::iterator < std::random_access_iterator_tag, Date, size_t>
{
    Date p;
public:
    friend  iterator Calendar_DS::it() const;
    friend  iterator Calendar_DS::itEvent(const std::vector<std::pair<Date, std::string>>::iterator& it) const;
    friend  iterator Calendar_DS::itEvent(size_t index) const;

    iterator(const iterator &it);

    Date &operator*();
    const Date operator*() const;

    bool operator!=(iterator const& other) const;
    bool operator==(iterator const& other) const;
    bool operator< (iterator const& other) const;
    bool operator<=(iterator const& other) const;
    bool operator> (iterator const& other) const;
    bool operator>=(iterator const& other) const;
    const iterator &operator=(iterator const& other);
    const iterator &operator+=(size_t shift);
    const iterator &operator-=(size_t shift);
    const iterator &operator++();
    const iterator &operator--();
    const iterator operator++(int);
    const iterator operator--(int);
    const iterator operator+(size_t shift) const;
    const iterator operator-(size_t shift) const;
    int64_t operator-(const iterator & other) const;;

private:
    explicit iterator(const Date& p);
};


#endif // CALENDAR_DS_H
