#include <iostream>
#include <iomanip>
#include <fstream>
#include <exception>
#include <string>
#include <sstream>
#include <vector>

#include "MerlinDisassemble.hpp"
using namespace MerlinDisassembleNamespace;

//                                                                             
//  MerlinDisassemble < input.txt > output.txt                                 
//  cat input.txt | MerlinDisassemble                                          
//  cat input.txt | MerlinDisassemble > output.txt                             
//  MerlinDisassemble input.txt                                                
//  MerlinDisassemble input.txt output.txt                                     
//                                                                             
//  Maybe --line_number:width --comment_column:start                           
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
            // DEFERRED BUG output file/no file
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
