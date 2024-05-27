
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
            TEST_CASE (M220);  // "M220,SET FEED RATE %,         Backup Factor, Restore Factor, SPercentage"
            TEST_CASE (M221);  // "M221,SET FLOW RATE %,         SFlow%, TExtruder"
            TEST_CASE (T0  );  // "T0,  SELECT/REPORT TOOL"
        }

    void G0(void)
    {
    }

    void G1(void)
    {
    }

    void G2(void)
    {
    }

    void G3(void)
    {
    }

    void G4(void)
    {
    }

    void G28(void)
    {
    }

    void G90(void)
    {
    }

    void G91(void)
    {
    }

    void G92(void)
    {
    }

    void M20(void)
    {
    }

    void M80(void)
    {
    }

    void M82(void)
    {
    }

    void M83(void)
    {
    }

    void M84(void)
    {
    }

    void M104(void)
    {
    }

    void M105(void)
    {
    }

    void M106(void)
    {
    }

    void M107(void)
    {
    }

    void M109(void)
    {
    }

    void M110(void)
    {
    }

    void M111(void)
    {
    }

    void M114(void)
    {
    }

    void M115(void)
    {
    }

    void M117(void)
    {
    }

    void M140(void)
    {
    }

    void M155(void)
    {
    }

    void M190(void)
    {
    }

    void M220(void)
    {
    }

    void M221(void)
    {
    }

    void T0(void)
    {
    }
};

REGISTER_FIXTURE( MerlinGCodeTests );

