
//  TODO - comment vs no comment
//  TODO - move comment to a different column
//  TODO - line numbers
//  TODO - bad command line switch


class MerlinGCodeTests : public TestFixture<MerlinGCodeTests>
{
    public:

        TEST_FIXTURE( MerlinGCodeTests )
        {
            TEST_CASE (G0  );  // "G0,  LINEAR MOVE,             XX, YY, ZZ, EE, FSpeed, SPower"
            TEST_CASE (G1  );  // "G1,  LINEAR MOVE,             XX, YY, ZZ, EE, FSpeed, SPower"
            TEST_CASE (G2  );  // "G2,  ARC/CIRCLE MOVE,         XX, YY, ZZ, EE, FSpeed, IX Arc Center, JY Arc Center, PComplete Circle, RRadius, SPower"
            TEST_CASE (G3  );  // "G3,  ARC/CIRCLE MOVE,         XX, YY, ZZ, EE, FSpeed, IX Arc Center, JY Arc Center, PComplete Circle, RRadius, SPower"
            TEST_CASE (G4  );  // "G4,  DWELL,                   PMilliseconds, SSeconds"
            TEST_CASE (G28 );  // "G28, AUTO HOME,               LRestore Leveling State, OSkip Homing, RRaise Nozzle, XX Axis, YY Axis, ZZ Axis"
            TEST_CASE (G90 );  // "G90, ABSOLUTE POSITIONING"
            TEST_CASE (G91 );  // "G91, RELATIVE POSITIONING"
            TEST_CASE (G92 );  // "G92, SET POSITION,            XX, YY, ZZ, EE"
            TEST_CASE (M20 );  // "M20, LIST SD CARD,            FBin Files, LLong File Name, TTimestamp"
            TEST_CASE (M80 );  // "M80, POWER ON,                SReport Power Supply State"
            TEST_CASE (M82 );  // "M82, E ABSOLUTE"
            TEST_CASE (M83 );  // "M83, E RELATIVE"
            TEST_CASE (M84 );  // "M84, DISABLE STEPPERS,        SSeconds, XX Axis,YY Axis, ZZ Axis, EExtruder, AA Axis, BB Axis, CC Axis, UU Axis, VV Axis, WW Axis"
            TEST_CASE (M104);  // "M104,START HOTEND TEMP,       BMaxAutoTemp, FAutoTemp Flag, IMaterial Preset Index, STemp, THotEnd"
            TEST_CASE (M105);  // "M105,REPORT TEMP,             RRedundant Temp, THotEnd"
            TEST_CASE (M106);  // "M106,SET FAN SPEED,           IMaterial preset, PFan, SSpeed, TSecondary Speed"
            TEST_CASE (M107);  // "M107,FAN OFF,                 PIndex"
            TEST_CASE (M109);  // "M109,WAIT HOTEND TEMP,        BMax Auto Temp, FAuto Temp Flag, IMaterial preset index, RHotCool Wait, STemp, THotEnd"
            TEST_CASE (M110);  // "M110,SET/GET LINE NUMBER,     NLineNumber"
            TEST_CASE (M111);  // "M111,SET DEBUG LEVEL,         SFlags"
            TEST_CASE (M114);  // "M114,GET CURRENT POS,         DDetailed, EStepper, RReal"
            TEST_CASE (M115);  // "M115,SHOW FIRMWARE INFO"
            TEST_CASE (M117);  // "M117,SET LCD MESSAGE"
            TEST_CASE (M140);  // "M140,START BED TEMP,          IIndex, STemp"
            TEST_CASE (M155);  // "M155,TEMP AUTO REPORT,        SSeconds"
            TEST_CASE (M190);  // "M190,WAIT BED TEMP,           IIndex, RTemp, STemp, TSeconds"
            TEST_CASE (M220);  // "M220,SET FEED RATE %,         BBackup Factor, RRestore Factor, SPercentage"
            TEST_CASE (M221);  // "M221,SET FLOW RATE %,         SFlow%, TExtruder"
            TEST_CASE (T0  );  // "T0,  SELECT/REPORT TOOL"
        }


        //                                                                     
        //  This function does the work for the passed in test.                
        //                                                                     
        void test
        (
            const char *iSendThis,
            const char *iExpectThis
        )
        {
            std::ofstream out ("sent.txt");
            out << iSendThis << std::endl;

            std::string command = "..\\Debug\\MerlinDisassemble.exe ";
                        command += "sent.txt";

            FILE *fp = _popen(command.c_str(), "r");
            if (fp)
            {
                char buffer[1000] = "";
                while (fgets(buffer, sizeof(buffer), fp) != nullptr)
                {
                    std::size_t len = strlen(buffer);
                    if (len > 0)
                    {
                        buffer[len - 1] = '\0';
                    }
                    else
                    {
                    }

                    ASSERT_EQUALS(iExpectThis, buffer);
                }

                fclose(fp);
            }
            else
            {
                FAIL("The command did not run");
            }
        }

        void G0(void)
        {
            const char *sent        = "g0 x10 y20 z30 e40 f100 s200";
            const char *expected    = "G0   LINEAR MOVE            X:10, Y:20, Z:30, E:40(40), Speed:100, Power:200                        ";
            test(sent, expected);
        }

        void G1(void)
        {
            const char *sent        = "g1 x10 y20 z30 e40 f100 s200";
            const char *expected    = "G1   LINEAR MOVE            X:10, Y:20, Z:30, E:40(40), Speed:100, Power:200                        ";
            test(sent, expected);
        }

        void G2(void)
        {
            const char *sent        = "g2 x10 y20 z30 e40 f100 s200 i12 jy13 p7 r92";
            const char *expected    = "G2   ARC/CIRCLE MOVE        X:10, Y:20, Z:30, E:40(40), Speed:100, X Arc Center:12, Y Arc Center:y13, Complete Circle:7, Radius:92, Power:200  ";
            test(sent, expected);
        }

        void G3(void)
        {
            const char *sent        = "g3 x10 y20 z30 e40 f100 s200 i12 jy13 p7 r92";
            const char *expected    = "G3   ARC/CIRCLE MOVE        X:10, Y:20, Z:30, E:40(40), Speed:100, X Arc Center:12, Y Arc Center:y13, Complete Circle:7, Radius:92, Power:200  ";
            test(sent, expected);
        }

        void G4(void)
        {
            const char *sent        = "g4 P111 S222";
            const char *expected    = "G4   DWELL                  Milliseconds:111, Seconds:222                                           ";
            test(sent, expected);
        }

        void G28(void)
        {
            const char *sent        = "g28 L1 O2 R3 X4 Y5 Z6";
            const char *expected    = "G28  AUTO HOME              Restore Leveling State:1, Skip Homing:2, Raise Nozzle:3, X Axis:4, Y Axis:5, Z Axis:6  ";
            test(sent, expected);
        }

        void G90(void)
        {
            const char *sent        = "g90";
            const char *expected    = "G90  ABSOLUTE POSITIONING                                                                           ";
            test(sent, expected);
        }

        void G91(void)
        {
            const char *sent        = "g91";
            const char *expected    = "G91  RELATIVE POSITIONING                                                                           ";
            test(sent, expected);
        }

        void G92(void)
        {
            const char *sent        = "g92 x1 y2 z3 e4";
            const char *expected    = "G92  SET POSITION           X:1, Y:2, Z:3, E:4                                                      ";
            test(sent, expected);
        }

        void M20(void)
        {
            // "M20, LIST SD CARD,            FBin Files, LLong File Name, TTimestamp"
            const char *sent        = "m20 f1 l2 t3";
            const char *expected    = "M20  LIST SD CARD           Bin Files:1, Long File Name:2, Timestamp:3                              ";
            test(sent, expected);
        }

        void M80(void)
        {
            // "M80, POWER ON,                SReport Power Supply State"
            const char *sent        = "m80 s1";
            const char *expected    = "M80  POWER ON               Report Power Supply State:1                                             ";
            test(sent, expected);
        }

        void M82(void)
        {
            // "M82, E ABSOLUTE"
            const char *sent        = "m82";
            const char *expected    = "M82  E ABSOLUTE                                                                                     ";
            test(sent, expected);
        }

        void M83(void)
        {
            // "M83, E RELATIVE"
            const char *sent        = "m83";
            const char *expected    = "M83  E RELATIVE                                                                                     ";
            test(sent, expected);
        }

        void M84(void)
        {
            // "M84, DISABLE STEPPERS,        SSeconds, XX Axis,YY Axis, ZZ Axis, EExtruder, AA Axis, BB Axis, CC Axis, UU Axis, VV Axis, WW Axis"
            const char *sent        = "m84 S1 X2 Y3 E4 A5 B6 C7 U8 V9 W10";
            const char *expected    = "M84  DISABLE STEPPERS       Seconds:1, X Axis:2, Y Axis:3, Extruder:4, A Axis:5, B Axis:6, C Axis:7, U Axis:8, V Axis:9, W Axis:10  ";
            test(sent, expected);
        }

        void M104(void)
        {
            // "M104,START HOTEND TEMP,       BMaxAutoTemp, FAutoTemp Flag, IMaterial Preset Index, STemp, THotEnd"
            const char *sent        = "m104 B1 F2 I3 S4 T5";
            const char *expected    = "M104 START HOTEND TEMP      MaxAutoTemp:1, AutoTemp Flag:2, Material Preset Index:3, Temp:4, HotEnd:5  ";
            test(sent, expected);
        }

        void M105(void)
        {
            // "M105,REPORT TEMP,             RRedundant Temp, THotEnd"
            const char *sent        = "M105 R1 T2";
            const char *expected    = "M105 REPORT TEMP            Redundant Temp:1, HotEnd:2                                              ";
            test(sent, expected);
        }

        void M106(void)
        {
            // "M106,SET FAN SPEED,           IMaterial preset, PFan, SSpeed, TSecondary Speed"
            const char *sent        = "m106 i1 p2 s3 t4";
            const char *expected    = "M106 SET FAN SPEED          Material preset:1, Fan:2, Speed:3, Secondary Speed:4                    ";
            test(sent, expected);
        }

        void M107(void)
        {
            // "M107,FAN OFF,                 PIndex"
            const char *sent        = "m107 p100";
            const char *expected    = "M107 FAN OFF                Index:100                                                               ";
            test(sent, expected);
        }

        void M109(void)
        {
            // "M109,WAIT HOTEND TEMP,        BMax Auto Temp, FAuto Temp Flag, IMaterial preset index, RHotCool Wait, STemp, THotEnd"
            const char *sent        = "M109 B1 F2 I3 R4 S5 T6";
            const char *expected    = "M109 WAIT HOTEND TEMP       Max Auto Temp:1, Auto Temp Flag:2, Material preset index:3, HotCool Wait:4, Temp:5, HotEnd:6  ";
            test(sent, expected);
        }

        void M110(void)
        {
            // "M110,SET/GET LINE NUMBER,     NLineNumber"
            const char *sent        = "m110 n111";
            const char *expected    = "M110 SET/GET LINE NUMBER    LineNumber:111                                                          ";
            test(sent, expected);
        }

        void M111(void)
        {
            // "M111,SET DEBUG LEVEL,         SFlags"
            const char *sent        = "m111 s111";
            const char *expected    = "M111 SET DEBUG LEVEL        Flags:111                                                               ";
            test(sent, expected);
        }

        void M114(void)
        {
            // "M114,GET CURRENT POS,         DDetailed, EStepper, RReal"
            const char *sent        = "m114 d1 e2 r3";
            const char *expected    = "M114 GET CURRENT POS        Detailed:1, Stepper:2, Real:3                                           ";
            test(sent, expected);
        }

        void M115(void)
        {
            // "M115,SHOW FIRMWARE INFO"
            const char *sent        = "m115";
            const char *expected    = "M115 SHOW FIRMWARE INFO                                                                             ";
            test(sent, expected);
        }

        void M117(void)
        {
            // "M117,SET LCD MESSAGE"
            const char *sent        = "m117 abc DEF      123 )(*&^%$#@!";
            const char *expected    = "M117 SET LCD MESSAGE        abc DEF 123 )(*&^%$#@!                                                  ";
            test(sent, expected);
        }

        void M140(void)
        {
            // "M140,START BED TEMP,          IIndex, STemp"
            const char *sent        = "m140 i1 s2";
            const char *expected    = "M140 START BED TEMP         Index:1, Temp:2                                                         ";
            test(sent, expected);
        }

        void M155(void)
        {
            // "M155,TEMP AUTO REPORT,        SSeconds"
            const char *sent        = "m155 s155";
            const char *expected    = "M155 TEMP AUTO REPORT       Seconds:155                                                             ";
            test(sent, expected);
        }

        void M190(void)
        {
            // "M190,WAIT BED TEMP,           IIndex, RTemp, STemp, TSeconds"
            const char *sent        = "m190 i1 r2 s3 t4";
            const char *expected    = "M190 WAIT BED TEMP          Index:1, Temp:2, Temp:3, Seconds:4                                      ";
            test(sent, expected);
        }

        void M220(void)
        {
            // "M220,SET FEED RATE %,         BBackup Factor, RRestore Factor, SPercentage"
            const char *sent        = "m220 b1 r2 s3";
            const char *expected    = "M220 SET FEED RATE %        Backup Factor:1, Restore Factor:2, Percentage:3                         ";
            test(sent, expected);
        }

        void M221(void)
        {
            // "M221,SET FLOW RATE %,         SFlow%, TExtruder"
            const char *sent        = "M221 s1 t2";
            const char *expected    = "M221 SET FLOW RATE %        Flow%:1, Extruder:2                                                     ";
            test(sent, expected);
        }

        void T0(void)
        {
            // "T0,  SELECT/REPORT TOOL"
            const char *sent        = "t0";
            const char *expected    = "T0   SELECT/REPORT TOOL                                                                             ";
            test(sent, expected);
        }
};

REGISTER_FIXTURE( MerlinGCodeTests );

