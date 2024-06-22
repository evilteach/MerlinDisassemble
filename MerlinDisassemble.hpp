//                                                                                   
//  MerlinDisassemble.hpp                                                            
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
//                                                                                   


void uppercase
(
    std::string &value
)
{
    for (auto &c: value) c = (char) toupper(c);
}


void trim
(
    std::string &line
)
{
    line.erase(line.find_last_not_of("\n\r ") + 1);
    line.erase(0, line.find_first_not_of("\n\r "));
}


namespace MerlinDisassembleNamespace
{
    const std::string merlinCodes[] =
    {
         "G0,  LINEAR MOVE,             XX, YY, ZZ, EE, FSpeed, SPower"
        ,"G1,  LINEAR MOVE,             XX, YY, ZZ, EE, FSpeed, SPower"
        ,"G2,  ARC/CIRCLE MOVE,         XX, YY, ZZ, EE, FSpeed, IX Arc Center, JY Arc Center, PComplete Circle, RRadius, SPower"
        ,"G3,  ARC/CIRCLE MOVE,         XX, YY, ZZ, EE, FSpeed, IX Arc Center, JY Arc Center, PComplete Circle, RRadius, SPower"
        ,"G4,  DWELL,                   PMilliseconds, SSeconds"
        ,"G21, Millimeter Units"
        ,"G28, AUTO HOME,               LRestore Leveling State, OSkip Homing, RRaise Nozzle, XX Axis, YY Axis, ZZ Axis"
        ,"G90, ABSOLUTE POSITIONING"
        ,"G91, RELATIVE POSITIONING"
        ,"G92, SET POSITION,            XX, YY, ZZ, EE"
        ,"M20, LIST SD CARD,            FBin Files, LLong File Name, TTimestamp"
        ,"M80, POWER ON,                SReport Power Supply State"
        ,"M82, E ABSOLUTE"
        ,"M83, E RELATIVE"
        ,"M84, DISABLE STEPPERS,        SSeconds, XX Axis,YY Axis, ZZ Axis, EExtruder, AA Axis, BB Axis, CC Axis, UU Axis, VV Axis, WW Axis"
        ,"M104,START HOTEND TEMP,       BMaxAutoTemp, FAutoTemp Flag, IMaterial Preset Index, STemp, THotEnd"
        ,"M105,REPORT TEMP,             RRedundant Temp, THotEnd"
        ,"M106,SET FAN SPEED,           IMaterial preset, PFan, SSpeed, TSecondary Speed"
        ,"M107,FAN OFF,                 PIndex"
        ,"M109,WAIT HOTEND TEMP,        BMax Auto Temp, FAuto Temp Flag, IMaterial preset index, RHotCool Wait, STemp, THotEnd"
        ,"M110,SET/GET LINE NUMBER,     NLineNumber"
        ,"M111,SET DEBUG LEVEL,         SFlags"
        ,"M114,GET CURRENT POS,         DDetailed, EStepper, RReal"
        ,"M115,SHOW FIRMWARE INFO"
        ,"M117,SET LCD MESSAGE"
        ,"M140,START BED TEMP,          IIndex, STemp"
        ,"M155,TEMP AUTO REPORT,        SSeconds"
        ,"M190,WAIT BED TEMP,           IIndex, RTemp, STemp, TSeconds"
        ,"M204,SET STARTING ACCEL,      PPrinting Acceleration, RRetraction Acceleration, SLegacy Acceleration, TTravelAcceleration"
        ,"M205,SET ADVANCED SETTINGS,   BMinimum Segement Time, EE Max Jerks, JJunction Deviation, SPrint Feedrate, TTravel Feedrate, XXJerk, YYJerk, ZZJerk"
        ,"M220,SET FEED RATE %,         BBackup Factor, RRestore Factor, SPercentage"
        ,"M221,SET FLOW RATE %,         SFlow%, TExtruder"
        ,"T0,  SELECT/REPORT TOOL"

        // DEFERRED TODO add more G/M codes as needed.
    };

    std::size_t merlinCodesCount = sizeof(merlinCodes) / sizeof(merlinCodes[0]);


    //
    //
    //
    class MerlinDisassemble
    {
        public:


            MerlinDisassemble
            (
                void
            )
            {
            }


            ~MerlinDisassemble
            (
                void
            )
            {
            }


            void show_line_numbers
            (
                void
            )
            {
                showLineNumbers = 1;
            }


            void set_comment_column
            (
                int iCommentColumn
            )
            {
                commentColumn = iCommentColumn;
            }


            int process
            (
                std::istream &in,
                std::ostream &out
            )
            {
                int returnStatus = 0;

                double lastExtrusion = 0;

                std::string line;
                std::vector<std::string> arguments;
                std::string comment;
                std::string command;

                int lineNumber = 0;

                while(std::getline(in, line))
                {
                    std::ostringstream oss;

                    if (showLineNumbers)
                    {
                        lineNumber++;
                        oss << std::setw(6) << lineNumber << " ";
                    }
                    else
                    {
                        // Do not show line numbers.
                    }

                    {
                        trim(line);
                    }

                    {
                        // Maybe this is a Repetier log file.
                        // If so pull the background noise out of it
                        // so all we are left with is the G/M codes.
                        if
                        (
                            isdigit(line[0]) &&
                            isdigit(line[1]) &&
                            isdigit(line[3]) &&
                            isdigit(line[4]) &&
                            isdigit(line[6]) &&
                            isdigit(line[7])
                        )
                        {
                            // This is a log file.

                            if (line.find(" : N") == std::string::npos)
                            {
                                continue;   // This line does not need disassembled
                            }
                            else
                            {
                                // Turn this into a line we can process

                                // Skip the prefix
                                line = line.substr(15);

                                // Find the end of the number
                                std::size_t pos = line.find(" ");
                                line = line.substr(pos + 1);

                                // Find the trailing *
                                pos = line.rfind("*");
                                line = line.substr(0, pos);
                            }
                        }
                        else
                        {
                            // Not a log file, treat it normally.
                        }
                    }

                    {
                        // Get the comment if there is one.
                        comment = "";
                        std::size_t foundAt = line.find(";");
                        if (foundAt != std::string::npos)
                        {
                            comment = line.substr(foundAt);
                            line = line.substr(0, foundAt);
                        }
                        else
                        {
                        }
                    }

                    {
                        // Get the command and any arguments it has.
                        std::string tmp;
                        std::istringstream iss (line);
                        std::getline(iss, command, ' ');
                        uppercase(command);

                        arguments.clear();

                        while (std::getline(iss, tmp, ' '))
                        {
                            if (tmp.empty())
                            {
                                // We don't really care about blanks
                            }
                            else
                            {
                                arguments.push_back(tmp);
                            }
                        }
                    }

                    // Try to find the merlinCode for this one.
                    size_t z = 0;
                    for (; z < merlinCodesCount; z++)
                    {
                        std::size_t commaAt = merlinCodes[z].find(",");
                        if (commaAt != std::string::npos)
                        {
                            std::string match = merlinCodes[z].substr(0, commaAt);
                            if (command == match)
                            {
                                break;
                            }
                            else
                            {
                            }
                        }
                        else
                        {
                        }
                    }

                    if (z == merlinCodesCount)
                    {
                        if (command == "")
                        {
                            // Blank commands aren't interesting so ignore them.
                        }
                        else
                        {
                            // Make unsupported commands stand out like a sore thumb.
                            oss << "*********************************** <"  << command << "> "
                                << " is not recognized on line " << lineNumber;
                        }
                    }
                    else
                    {
                        // Attempt to display the line in a more human readable form.
                        // Note in this implementation we are forcing the arguments into a fixed known order.

                        std::istringstream merlinCodeStream (merlinCodes[z]);
                        std::getline(merlinCodeStream, command, ',');
                        oss << std::left << std::setw(5) << command;

                        std::string description;
                        std::getline(merlinCodeStream, description, ',');
                        trim(description);
                        oss << std::left << std::setw(23) << description;

                        if (command == "M117")
                        {
                            // This gcode just displays some strings
                            for (auto &argument : arguments)
                            {
                                oss << argument << " ";
                            }
                        }
                        else
                        {
                            // Check all of the arguments that this Merlin Code supports.
                            std::string referenceArgument;
                            while (std::getline(merlinCodeStream, referenceArgument, ','))
                            {
                                trim(referenceArgument);
                                for (auto &argument : arguments)
                                {
                                    trim(argument);

                                    // Get the actual argument info.
                                    std::string actualArgumentType  = argument.substr(0, 1);
                                    std::string actualArgumentValue = argument.substr(1);
                                    uppercase(actualArgumentType);

                                    // Get the reference argument info.
                                    std::string referenceArgumentType = referenceArgument.substr(0, 1);
                                    std::string referenceArgumentName = referenceArgument.substr(1);
                                    uppercase(referenceArgumentType);

                                    // If they are the same we can display something
                                    if (actualArgumentType == referenceArgumentType)
                                    {
                                        if (actualArgumentType == "E")
                                        {
                                            // For extrusions we need to do a few things to make the actual
                                            // extrusion amounts easier to understand.

                                            if (command == "M92")
                                            {
                                                // Reset the extruder start point.
                                                lastExtrusion = 0;
                                                oss << referenceArgumentName << ":" << actualArgumentValue << ", ";
                                            }
                                            else
                                            {
                                                if (command == "G0" || command == "G1" ||
                                                    command == "G2" || command == "G3")
                                                {
                                                    // This is a gcode which also include an extrusion.
                                                    // Show it with the calculated amount.
                                                    double extrusionAmount = atof(actualArgumentValue.c_str()) -
                                                                             lastExtrusion;
                                                    lastExtrusion = atof(actualArgumentValue.c_str());

                                                    // A precision of 6 seems to maintain the values that come
                                                    // out of the file
                                                    oss << referenceArgumentName << ":" << actualArgumentValue 
                                                        << "(" << std::setprecision(6) << extrusionAmount << "), ";
                                                }
                                                else
                                                {
                                                    // Just show what ever the value is.
                                                    oss << referenceArgumentName << ":" << actualArgumentValue << ", ";
                                                }
                                            }
                                        }
                                        else
                                        {
                                            // Just show what ever the value is.
                                            oss << referenceArgumentName << ":" << actualArgumentValue << ", ";
                                        }
                                    }
                                    else
                                    {
                                        // This argument is not used.
                                    }
                                }
                            }

                            // Replace the last commas by spaces.
                            std::string tmp = oss.str();
                            tmp.pop_back();
                            tmp.pop_back();
                            tmp.push_back(' ');
                            tmp.push_back(' ');

                            oss.clear();
                            oss.str("");
                            oss << tmp;
                        }
                    }

                    size_t ossSize = oss.str().size();

                    if (commentColumn > 0)
                    {
                        if (commentColumn < (int) ossSize)
                        {
                            // No padding is needed.
                            // Just plop it on the end.
                        }
                        else
                        {
                            std::string rightFill (commentColumn - oss.str().size(), ' ');
                            oss << rightFill;
                        }

                        oss << comment;
                    }
                    else
                    {
                        // The command line switch requested no comments.
                    }

                    out << oss.str() << std::endl;
                }

                return returnStatus;
            }

        protected :

            // By default don't show line numbers.
            int showLineNumbers = 0;

            // By default put comments in column 100.
            int commentColumn   = 100;
    };
}
