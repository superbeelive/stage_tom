EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Amplifier_Operational:LM324 U1
U 1 1 62878349
P 4600 2400
F 0 "U1" H 4600 2767 50  0000 C CNN
F 1 "LM324" H 4600 2676 50  0000 C CNN
F 2 "" H 4550 2500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 4650 2600 50  0001 C CNN
	1    4600 2400
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM324A U2
U 1 1 628793A5
P 5700 2400
F 0 "U2" H 5700 2767 50  0000 C CNN
F 1 "LM324A" H 5700 2676 50  0000 C CNN
F 2 "" H 5650 2500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 5750 2600 50  0001 C CNN
	1    5700 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2300 5400 2300
Wire Wire Line
	4900 2400 4900 2500
Wire Wire Line
	4900 2500 5400 2500
$Comp
L Device:R R2
U 1 1 6288D516
P 5400 3050
F 0 "R2" H 5470 3096 50  0000 L CNN
F 1 "1kOhm" H 5470 3005 50  0000 L CNN
F 2 "" V 5330 3050 50  0001 C CNN
F 3 "~" H 5400 3050 50  0001 C CNN
	1    5400 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 6288DBB9
P 6300 2550
F 0 "R1" H 6370 2596 50  0000 L CNN
F 1 "130kOhm" H 6370 2505 50  0000 L CNN
F 2 "" V 6230 2550 50  0001 C CNN
F 3 "~" H 6300 2550 50  0001 C CNN
	1    6300 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 2900 5400 2700
Connection ~ 5400 2500
Wire Wire Line
	5400 2700 6300 2700
Connection ~ 5400 2700
Wire Wire Line
	5400 2700 5400 2500
Wire Wire Line
	6000 2400 6300 2400
$Comp
L Device:C C1
U 1 1 6288FC0D
P 6700 2400
F 0 "C1" V 6448 2400 50  0000 C CNN
F 1 "C" V 6539 2400 50  0000 C CNN
F 2 "" H 6738 2250 50  0001 C CNN
F 3 "~" H 6700 2400 50  0001 C CNN
	1    6700 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 2400 6550 2400
Connection ~ 6300 2400
$Comp
L MCU_Module:Arduino_UNO_R2 A1
U 1 1 62891EAE
P 7550 2400
F 0 "A1" H 7550 3581 50  0000 C CNN
F 1 "Arduino_UNO_R2" H 7550 3490 50  0000 C CNN
F 2 "Module:Arduino_UNO_R2" H 7550 2400 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 7550 2400 50  0001 C CNN
	1    7550 2400
	-1   0    0    -1  
$EndComp
$Comp
L Sensor_Pressure:MPXH6115A U3
U 1 1 62895A8B
P 3700 2300
F 0 "U3" H 3270 2346 50  0000 R CNN
F 1 "MPXH6115A" H 3270 2255 50  0000 R CNN
F 2 "" H 3200 1950 50  0001 C CNN
F 3 "http://www.nxp.com/files/sensors/doc/data_sheet/MPXA6115A.pdf" H 3700 2900 50  0001 C CNN
	1    3700 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 2300 4300 2300
Wire Wire Line
	5400 3200 5400 3250
Wire Wire Line
	3700 2600 3700 3250
Wire Wire Line
	3700 3250 5400 3250
Connection ~ 5400 3250
Wire Wire Line
	6850 2400 7050 2400
$Comp
L Sensor_Humidity:Si7020-A20 U4
U 1 1 628CCA3E
P 6200 3050
F 0 "U4" H 6644 3096 50  0000 L CNN
F 1 "Si7020-A20" H 6644 3005 50  0000 L CNN
F 2 "Package_DFN_QFN:DFN-6-1EP_3x3mm_P1mm_EP1.5x2.4mm" H 6200 2650 50  0001 C CNN
F 3 "https://www.silabs.com/documents/public/data-sheets/Si7020-A20.pdf" H 6000 3350 50  0001 C CNN
	1    6200 3050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5400 3250 5400 3500
Wire Wire Line
	5400 3500 6300 3500
Wire Wire Line
	6700 2950 6900 2950
Wire Wire Line
	6900 2950 6900 2800
Wire Wire Line
	6900 2800 7050 2800
Wire Wire Line
	6700 3150 7050 3150
Wire Wire Line
	7050 3150 7050 2900
Wire Wire Line
	6200 2750 6200 1400
Wire Wire Line
	6200 1400 7350 1400
Wire Wire Line
	6300 3350 6300 3500
Connection ~ 6300 3500
Wire Wire Line
	6300 3500 7450 3500
Wire Wire Line
	5300 2000 5300 2300
Wire Wire Line
	4300 2000 5300 2000
Wire Wire Line
	4300 2000 4300 2500
$EndSCHEMATC
