#include <iostream>
#include <iomanip>
#include <fstream>
#include <exception>
#include <string>
#include <sstream>
#include <vector>

#include "MerlinDisassemble.hpp"
using namespace MerlinDisassembleNamespace;

const char *helpText =
    "\n                                                       "
    "\n  MerlinDisassemble -h                                 "
    "\n  MerlinDisassemble [-l] [-c:100]                      "
    "\n  MerlinDisassemble [-l] [-c:100] input.txt            "
    "\n  MerlinDisassemble [-l] [-c:100] input.txt output.txt "
    "\n                                                       "
    "\n   -h to print this text                               "
    "\n   -l to put line numbers on the output                "
    "\n   -c:x to start the comments in column x              "
    "\n   -c:0 to suppress comments                           "
    "\n                                                       "
    "\n  returns 0 on success                                 "
    "\n  returns 1 on failure                                 "
    "\n                                                       ";

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

        bool showLineNumbers = false;
        int commentColumn    = 100;

        int firstArgument = 0;

        std::size_t z = 1;
        for (; z < (std::size_t) argC; z++)
        {
            if (argV[z][0] == '-')
            {
                std::cout << "argV[" << z << "] is " << argV[z] << std::endl;
                std::string argument = argV[z];
                trim(argument);
                uppercase(argument);

                if (argument.substr(0, 2) == "-L")
                {
                    showLineNumbers = true;
                    firstArgument = (int) z + 1;
                }
                else
                {
                    if (argument.substr(0, 3) == "-C:")
                    {
                        commentColumn = std::stoi(argument.substr(3));
                        firstArgument = (int) z + 1;
                    }
                    else
                    {
                        if (argument.substr(0, 2) == "-H")
                        {
                            std::cerr << helpText << std::endl;
                            throw 1;
                        }
                        else
                        {
                            std::cerr << "Argument <" << argument
                                      << "> is not recognized." << std::endl;
                            throw 1;
                        }
                    }
                }
            }
            else
            {
            }
        }

        int argumentCount = argC - firstArgument - 1;

        if (argumentCount == 0)
        {
            // MerlinDisassemble

            std::istream &in = std::cin;
            std::ostream &out = std::cout;
            returnStatus = merlinDisassemble.process(in, out);
        }
        else
        {
            if (argumentCount == 1)
            {
                // MerlinDisassemble input.txt

                std::ifstream in (argV[firstArgument + 1]);
                std::ostream &out = std::cout;
                returnStatus = merlinDisassemble.process(in, out);
            }
            else
            {
                if (argumentCount == 2)
                {
                    // MerlinDisassemble input.txt output.txt

                    std::ifstream in (argV[firstArgument + 1]);
                    std::ofstream out (argV[firstArgument + 2]);
                    returnStatus = merlinDisassemble.process(in, out);
                }
                else
                {
                    std::cerr << "argumentCount is " << argumentCount << std::endl;
                    throw(1);
                }
            }
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
