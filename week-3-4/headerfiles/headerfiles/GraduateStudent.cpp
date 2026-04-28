
#include "GraduateStudent.hpp"
#include "Student.hpp"
#include <string>

// default constructor
GraduateStudent::GraduateStudent() : Student()
{
    fullTime = true;
}

GraduateStudent::GraduateStudent(std::string name, double fines, double fees, bool fullTime)
    : Student(name , fines, fees )  // this builds the parent constructor first (list initizialisaztion gg)
{
    this->fullTime = fullTime;
}

// since they dont pay tuition fees
double GraduateStudent::MoneyOwed() const
{
    return GetLibraryFines();

}