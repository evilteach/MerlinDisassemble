#include <iostream>
#include <iomanip>
#include <fstream>
#include <exception>
#include <string>
#include <sstream>
#include <vector>

#include "Merlindisassemble.hpp"
using namespace MerlinDisassembleNamespace;

//  
//  MerlinDisassemble < input.txt > output.txt
//  cat input.txt | MerlinDisassemble
//  cat input.txt | MerlinDisassemble > output.txt
//  MerlinDisassemble input.txt
//  MerlinDisassemble input.txt output.txt
//  
//  returns 0 on success
//  returns 1 on failure
//  
int main
(
    int argC,
    const char *argV[]
)
{
    int returnStatus = 0;

    try
    {
        MerlinDisassemble merlinDisassemble;

        if (argC == 2)
        {
            // MerlinDisassemble input.txt

            std::ifstream in (argV[1]);
            std::ostream &out = std::cout;
            returnStatus = merlinDisassemble.process(in, out);
        }
        else
        {
            int y = 3;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception " << e.what() << std::endl;
        returnStatus = 1;
    }
    catch (...)
    {
        std::cerr << "Unexpected Exception " << std::endl;
        returnStatus = 1;
    }

    return returnStatus;
}
