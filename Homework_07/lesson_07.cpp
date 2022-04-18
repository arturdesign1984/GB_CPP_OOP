#include <iostream>
#include <ctime>
#include <memory>

// 01 //////////////////////////////

class Date
{
private:
    int day;
    int month;
    int year;
public:
    void setDay(int day) { this->day = day; }
    void setMonth(int month) { this->month = month; }
    void setYear(int year) { this->year = year; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

};

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.getDay() << '.';
    if(date.getMonth() < 10)
    {
        os << '0' << date.getMonth() << '.';
    }
    else
    {
        os << date.getMonth() << '.';
    }
    os << date.getYear();
    return os;
}

// 02 //////////////////////////////

std::shared_ptr<Date> compareDates(std::shared_ptr<Date> p1, std::shared_ptr<Date> p2)
{
    if(p1->getYear() > p2->getYear())
    {
        return p1;
    }
    else if((p1->getYear() == p2->getYear()) && (p1->getMonth() > p2->getMonth()))
    {
        return p1;
    }
    else if((p1->getYear() == p2->getYear()) && (p1->getMonth() == p2->getMonth())  && (p1->getDay() > p2->getDay()))
    {
        return p1;
    }
    return p2;
}

void swapDates(std::shared_ptr<Date>& p1, std::shared_ptr<Date>& p2)
{
    p1.swap(p2);
}

// ////////////////////////////////


int main()
{
// 01 //////////////////////////////
    std::cout << "######\n# 01 #\n######\n\nClass Date:\n\n";

    std::shared_ptr<Date> today(new Date);
    std::shared_ptr<Date> date(new Date);
    time_t now = time(0);
    tm* locTime = localtime(&now);
    today->setDay(locTime->tm_mday);
    today->setMonth(1 + locTime->tm_mon);
    today->setYear(1900 + locTime->tm_year);
    std::cout << *today << std::endl;

    date = move(today);

    std::cout << "today = " << today << " | date = " << date << std::endl;

    std::cout << std::endl;

// 02  /////////////////////////////
    std::cout << "######\n# 02 #\n######\n\nClass Date:\n\n";

    std::shared_ptr<Date> date1(new Date);
    date1->setDay(12);
    date1->setMonth(1);
    date1->setYear(2022);
    std::shared_ptr<Date> date2(new Date);
    date2->setDay(20);
    date2->setMonth(1);
    date2->setYear(2022);

    std::cout << "date1 - " <<*date1 << " | date2 - " << *date2 << std::endl;
    swapDates(date1, date2);
    std::cout << "date1 - " <<*date1 << " | date2 - " << *date2 << std::endl;

    std::cout << *(compareDates(date1, date2)) << std::endl;

    std::cout << std::endl;

    return 0;
}

