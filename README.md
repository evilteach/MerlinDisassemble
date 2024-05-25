# MerlinDisassemble

This is a work-in-progress to make a filter that will take a Merlin gcode file
and turn it into something human-readable.

It also has the ability to process Repetier Logs that have the command button
turned on.  It cuts away the chaff, and processes the gcodes that get send
to your printer/cnc.

Invocation options look a bit like this.

                                                       
  MerlinDisassemble -h                                 
  MerlinDisassemble [-l] [-c:100]                      
  MerlinDisassemble [-l] [-c:100] input.txt            
  MerlinDisassemble [-l] [-c:100] input.txt output.txt 
                                                       
   -h to print this text                               
   -l to put line numbers on the output                
   -c:x to start the comments in column x              
   -c:0 to suppress comments                           
                                                       
  returns 0 on success                                 
  returns 1 on failure                                 
                                                       

A small test run ..

    MerlinDisassemble -l input.txt output.txt

processes this input file...

    G1 E10
    G1 E12
    M117 ********** START BEGINS 
    M104            S207
    M140            S57
    G28                                    ; Home extruder
    G1 Z15 F100
    M107                                   ; Turn off fan
    G90                                    ; Absolute positioning
    M82                                    ; Extruder in absolute mode
    M190            s57
    M109            S207
    G92 E0                                 ; Reset extruder position
    M117 ********** START ENDS

Yields output like this.

     1 G1   LINEAR MOVE            E:10(10)                                                         
     2 G1   LINEAR MOVE            E:12(2)                                                          
     3 M117 SET LCD MESSAGE        ********** START BEGINS                                          
     4 M104 START HOTEND TEMP      Temp:207                                                         
     5 M140 START BED TEMP         Temp:57                                                          
     6 G28  AUTO HOME                                                                               ; Home extruder
     7 G1   LINEAR MOVE            Z:15, Speed:100                                                  
     8 M107 FAN OFF                                                                                 ; Turn off fan
     9 G90  ABSOLUTE POSITIONING                                                                    ; Absolute positioning
    10 M82  E ABSOLUTE                                                                              ; Extruder in absolute mode
    11 M190 WAIT BED TEMP          Temp:57                                                          
    12 M109 WAIT HOTEND TEMP       Temp:207                                                         
    13 G92  SET POSITION           E:0                                                              ; Reset extruder position
    14 M117 SET LCD MESSAGE        ********** START ENDS                                            
