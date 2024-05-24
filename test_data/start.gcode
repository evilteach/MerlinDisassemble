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
