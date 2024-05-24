namespace MerlinDisassembleNamespace
{
    const std::string merlinCodes[] =
    {
         "G0,  LINEAR MOVE,             XX, YY, ZZ, EE, FSpeed, SPower"
        ,"G1,  LINEAR MOVE,             XX, YY, ZZ, EE, FSpeed, SPower"
        ,"M20, LIST SD CARD,            FBin Files, LLong File Name, TTimestamp"
        ,"G28, AUTO HOME,               LRestore Leveling State, OSkip Homing, RRaise Nozzle, XX Axis, YY Axis, ZZ Axis"
        ,"M80, POWER ON,                SReport Power Supply State"
        ,"G90, ABSOLUTE POSITIONING"
        ,"G91, RELATIVE POSITIONING"
        ,"G92, SET POSITION,            XX, YY, ZZ, EE"
        ,"M82, E ABSOLUTE"
        ,"M84, DISABLE STEPPERS,        SSeconds, XX Axis,YY Axis, ZZ Axis, EExtruder, AA Axis, BB Axis, CC Axis, UU Axis, VV Axis, WW Axis"
        ,"M104,START HOTEND TEMP,       BMaxAutoTemp, FAutoTemp Flag, IMaterial Preset Index, STemp, THotend"
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
        ,"M220,SET FEED RATE %,         Backup Factor, Restore Factor, SPercentage"
        ,"M221,SET FLOW RATE %,         SFlow%, TExtruder"
        ,"T0,  SELECT/REPORT TOOL"

        // DEFFERED BUG more G/M codes as needed.
    };

    std::size_t merlinCodesCount = sizeof(merlinCodes) / sizeof(merlinCodes[0]);

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
                    lineNumber++;
                    std::ostringstream oss;
                    oss << std::setw(6) << lineNumber << " ";

                    {
                        trim(line);
                    }

                    {
                        // Maybe this is a log file instead of a gcode file.
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
                            // Blank commands aren't interesting.
                        }
                        else
                        {
                            oss << std::left << std::setw(5) << command << "unknown at line " << lineNumber;
                        }
                    }
                    else
                    {
                        // Attempt to display the line in a more human readable form.
                        std::istringstream merlinCodeStream (merlinCodes[z]);
                        std::getline(merlinCodeStream, command, ',');
                        oss << std::left << std::setw(5) << command;

                        std::string description;
                        std::getline(merlinCodeStream, description, ',');
                        trim(description);
                        oss << std::left << std::setw(23) << description;

                        if (command == "M117")
                        {
                            // It is literally just a set of strings.
                            for (auto &argument : arguments)
                            {
                                oss << argument << " ";
                            }
                        }
                        else
                        {
                            bool showActualExtrusion = false;
                            if (command == "G0" || command == "G1")
                            {
                                showActualExtrusion = true;
                            }
                            else
                            {
                                // We don't need to show anything for this Merlin code.
                            }

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
                                        if (showActualExtrusion && referenceArgumentType == "E")
                                        {
                                            // Show E value with calculated extrusion
                                            double extrusionAmount = atof(actualArgumentValue.c_str()) - lastExtrusion;
                                            lastExtrusion = atof(actualArgumentValue.c_str());

                                            oss << referenceArgumentName << ":" << actualArgumentValue << "(" << extrusionAmount << "), ";
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

                            // Hide the last comma.
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

                    size_t commentColumn = 100;
                    size_t ossSize = oss.str().size();

                    if (commentColumn < ossSize)
                    {
                    }
                    else
                    {
                        std::string rightFill (commentColumn - oss.str().size(), ' ');
                        oss << rightFill;
                    }

                    oss << comment;

                    out << oss.str() << std::endl;
                }

                return returnStatus;
            }

        protected :

            void trim
            (
                std::string &line
            )
            {
                line.erase(line.find_last_not_of("\n\r ") + 1);
                line.erase(0, line.find_first_not_of("\n\r "));
            }

            void uppercase
            (
                std::string &value
            )
            {
                for (auto &c: value) c = (char) toupper(c);
            }
    };
}
