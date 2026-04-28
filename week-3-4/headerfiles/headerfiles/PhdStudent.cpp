

#include "GraduateStudent.hpp"
#include "PhdStudent.hpp"
#include <string>

PhdStudent::PhdStudent(std::string name, double fines, double fees, bool fullTime) : GraduateStudent(name, fines, fees, fullTime)
{
}

double PhdStudent::MoneyOwed() const
{
    return 0.0; // they are graduate and they dont pay libaray fees either 
}