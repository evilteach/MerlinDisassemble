
#include "MiniCppUnit.hxx"
#include "UnitTest.hpp"

int main
(
    void
)
{
    return TestFixtureFactory::theInstance().runTests() ? 0 : -1;

    return 0;
}