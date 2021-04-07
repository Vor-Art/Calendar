#ifndef DATE_H
#define DATE_H

#include <sstream>
#include <string>
#include <QDate>
#include <istream>


class Date
{
    enum class Month : size_t {
        JANUARY = 1,
        FEBRUARY,
        MARCH,
        APRIL,
        MAY,
        JUNE,
        JULY,
        AUGUST,
        SEPTEMBER,
        OCTOBER,
        NOVEMBER,
        DECEMBER = 12,
        COUNT = 12,
    };
    enum class DayOfWeek : int {
        MONDAY= 1,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY = 7,
        COUNT = 7,
    };

public:
    size_t year;
    Month month;
    size_t day;

    explicit Date(const std::string& str);
    explicit Date(size_t year = 1970, size_t month = 1, size_t day = 1);
    Date(const Date &other);

    Date::DayOfWeek static getDayOfWeek(const Date &date);
    Date::DayOfWeek getDayOfWeek() const;

    size_t static getMaxNumberDay(const Date& date);
    size_t static getMaxNumberDay(Month month);
    size_t getMaxNumberDay() const;

    bool static isLeap (size_t year);

    friend std::ostream &operator << (std::ostream& out, const Date::Month& month);
    friend std::ostream &operator << (std::ostream& out, const Date::DayOfWeek& day);
    friend std::ostream &operator << (std::ostream& out, const Date& date);
    friend std::istream &operator >> (std::istream& in, Date& date);

    bool operator!=(const Date & other) const;
    bool operator==(const Date & other) const;
    bool operator<(const Date & other) const;

    Date &operator+=(int shift);
    Date &operator-=(int shift);
    const Date &operator = (const Date & other);
    int64_t operator-(const Date & other) const;
    explicit operator std::string() const;
};




#endif // DATE_H
