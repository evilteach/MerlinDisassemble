    ;Generated with Cura_SteamEngine 15.01
  M117 ********** START BEGINS      

  G28 ; Home extruder
G1 Z15 F100
Jan
M107 ; Turn off fan
G90 ; Absolute positioning
M82 ; Extruder in absolute mode
M190 S50
; Activate all used extruder
M104 T0 S210
G92 E0 ; Reset extruder position
; Wait for all used extruders to reach temperature
M109 T0 S210
M117 ********** START ENDS
;Layer count: 1
;LAYER:0
M107
G0 F9000 X97.094 Y97.094 Z0.300
;TYPE:SKIRT
G1 F1800 X202.905 Y97.094 E5.27893
G1 X202.905 Y202.905 E10.55786
G1 X97.094 Y202.905 E15.83680
G1 X97.094 Y97.094 E21.11573
G1 F2400 E17.11573
G0 F9000 X100.494 Y100.494
;TYPE:WALL-OUTER
G1 F2400 E21.11573
G1 F1800 X199.505 Y100.494 E26.05541
G1 X199.505 Y199.505 E30.99509
G1 X100.494 Y199.505 E35.93477
G1 X100.494 Y100.494 E40.87444
G0 F9000 X100.752 Y100.878
G1 F1800 X100.505 Y100.980 E40.88778
G1 X100.505 Y199.018 E45.77891
G1 X100.752 Y199.120 E45.79224
G1 X149.872 Y150.000 E49.25793
G1 X100.752 Y100.878 E52.72368
G0 F9000 X100.878 Y100.752
G1 F1800 X150.000 Y149.872 E56.18943
G1 X199.120 Y100.752 E59.65511
G1 X199.018 Y100.505 E59.66844
G1 X100.980 Y100.505 E64.55958
G1 X100.878 Y100.752 E64.57291
G1 F2400 E60.57291
G0 F9000 X150.127 Y150.000
G1 F2400 E64.57291
G1 F1800 X199.247 Y199.120 E68.03859
G1 X199.494 Y199.018 E68.05192
G1 X199.494 Y100.980 E72.94306
G1 X199.247 Y100.878 E72.95639
G1 X150.127 Y150.000 E76.42214
G0 F9000 X150.000 Y150.127
G1 F1800 X100.878 Y199.247 E79.88790
G1 X100.980 Y199.494 E79.90123
G1 X199.018 Y199.494 E84.79236
G1 X199.120 Y199.247 E84.80570
G1 X150.000 Y150.127 E88.27138
G1 F2400 E84.27138
G0 F9000 X150.000 Y150.127 Z5.200
M117 *********************** END BEGINS
G1 z130 y280 x0
M107 ; Turn off fan
; Disable all extruder
G91 ; Relative positioning
T0
G1 E-1 ; Reduce filament pressure
M104 T0 S0
G90 ; Absolute positioning
G92 E0 ; Reset extruder position
;M140 S0 ; Disable heated bed
M84 ; Turn steppers off
m117 *********************** END ENDS