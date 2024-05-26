//                                                                                  
//  MerlinDisassemble.cpp                                                           
//                                                                                  
// MIT License                                                                      
//                                                                                  
// Copyright (c) 2024 EvilTeach                                                     
//                                                                                  
// Permission is hereby granted, free of charge, to any person obtaining a copy     
// of this software and associated documentation files (the "Software"), to deal    
// in the Software without restriction, including without limitation the rights     
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        
// copies of the Software, and to permit persons to whom the Software is            
// furnished to do so, subject to the following conditions:                         
//                                                                                  
// The above copyright notice and this permission notice shall be included in all   
// copies or substantial portions of the Software.                                  
//                                                                                  
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR       
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,         
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE      
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER           
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,    
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE    
// SOFTWARE.                                                                        

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

    MerlinDisassemble merlinDisassemble;

    try
    {
        int firstArgument = 1;

        std::size_t z = 1;
        for (; z <= (std::size_t) argC; z++)
        {
            if (argV[z][0] == '-')
            {
                firstArgument = (int) z + 1;
                std::string argument = argV[z];
                trim(argument);
                uppercase(argument);

                if (argument.substr(0, 2) == "-L")
                {
                    merlinDisassemble.show_line_numbers();
                }
                else
                {
                    if (argument.substr(0, 3) == "-C:")
                    {
                        merlinDisassemble.set_comment_column(std::stoi(argument.substr(3)));
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
                // Command line switches must be on the front.
                // In this case there aren't any more.

                break;
            }
        }


        int argumentCount = argC - firstArgument;
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

                std::ifstream in (argV[firstArgument + 0]);
                std::ostream &out = std::cout;

                returnStatus = merlinDisassemble.process(in, out);
            }
            else
            {
                if (argumentCount == 2)
                {
                    // MerlinDisassemble input.txt output.txt

                    std::ifstream in (argV[firstArgument  + 0]);
                    std::ofstream out (argV[firstArgument + 1], std::ofstream::out);
                    returnStatus = merlinDisassemble.process(in, out);
                }
                else
                {
                    std::cerr << "argumentCount is " << argumentCount << std::endl;
                    std::cerr << "Something must be odd about the command line" << std::endl;

                    for (int y = 0; y < argC; y++)
                    {
                        std::cerr << y << " <" << argV[y] << ">" << std::endl;
                    }

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
