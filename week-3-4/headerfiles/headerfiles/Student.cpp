

#include "Student.hpp"
#include <string>

Student::Student()
{
    name = "";
    library_fines = 0.0;
    tuition_fees = 0.0;
};


Student::Student(std::string name, double fines, double fees)
{
    this->name = name;
    SetLibraryFines(fines);
    tuition_fees = fees;
}



void Student::SetLibraryFines(double amount)
{
    if(amount > 0.0)
    {
        library_fines = amount;
    }

}




double Student::GetLibraryFines() const
{
    return library_fines;
}

double Student::MoneyOwed() const
{
   return library_fines + tuition_fees;
}