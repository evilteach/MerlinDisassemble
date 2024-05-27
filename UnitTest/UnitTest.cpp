
#include "MiniCppUnit.hxx"
#include <fstream>
#include "UnitTest.hpp"

int main
(
    void
)
{
    return TestFixtureFactory::theInstance().runTests() ? 0 : -1;
}