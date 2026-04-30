
#include "Exception.hpp"
#include "OutOfRangeException.hpp"


OutOfRangeException::OutOfRangeException(std::string prob) : Exception("OUT OF RANGE", prob)
{

}