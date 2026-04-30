
#include "Exception.hpp"
#include "FileNotOpenException.hpp"


FileNotOpenException::FileNotOpenException(std::string prob) : Exception("FILE NOT OPEN", prob)
{
    
}