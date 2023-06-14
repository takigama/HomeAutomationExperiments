EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ESP8266
LIBS:irremote-cache
EELAYER 25 0
EELAYER END
$Descr A3 16535 11693
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
L ESP-12E U1
U 1 1 58BC334B
P 3100 2000
F 0 "U1" H 3100 1900 50  0000 C CNN
F 1 "ESP-12E" H 3100 2100 50  0000 C CNN
F 2 "ESP8266:ESP-12E" H 3100 2000 50  0001 C CNN
F 3 "" H 3100 2000 50  0001 C CNN
	1    3100 2000
	1    0    0    -1  
$EndComp
$Comp
L AP1117 U2
U 1 1 58BC33EF
P 5550 3600
F 0 "U2" H 5650 3350 50  0000 C CNN
F 1 "AP1117" H 5550 3850 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 5550 3600 50  0001 C CNN
F 3 "" H 5550 3600 50  0000 C CNN
	1    5550 3600
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 58BC35A8
P 5050 3850
F 0 "C2" H 5075 3950 50  0000 L CNN
F 1 "C" H 5075 3750 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5088 3700 50  0001 C CNN
F 3 "" H 5050 3850 50  0000 C CNN
	1    5050 3850
	1    0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 58BC35ED
P 4800 3850
F 0 "C1" H 4825 3950 50  0000 L CNN
F 1 "CP" H 4825 3750 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeB_EIA-3528_Reflow" H 4838 3700 50  0001 C CNN
F 3 "" H 4800 3850 50  0000 C CNN
	1    4800 3850
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 58BC366A
P 5950 3850
F 0 "C3" H 5975 3950 50  0000 L CNN
F 1 "C" H 5975 3750 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5988 3700 50  0001 C CNN
F 3 "" H 5950 3850 50  0000 C CNN
	1    5950 3850
	1    0    0    -1  
$EndComp
$Comp
L CP C4
U 1 1 58BC36CB
P 6200 3850
F 0 "C4" H 6225 3950 50  0000 L CNN
F 1 "CP" H 6225 3750 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeB_EIA-3528_Reflow" H 6238 3700 50  0001 C CNN
F 3 "" H 6200 3850 50  0000 C CNN
	1    6200 3850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 58BC3861
P 5550 4150
F 0 "#PWR01" H 5550 3900 50  0001 C CNN
F 1 "GND" H 5550 4000 50  0000 C CNN
F 2 "" H 5550 4150 50  0000 C CNN
F 3 "" H 5550 4150 50  0000 C CNN
	1    5550 4150
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR02
U 1 1 58BC38AD
P 6350 3600
F 0 "#PWR02" H 6350 3450 50  0001 C CNN
F 1 "+3.3V" H 6350 3740 50  0000 C CNN
F 2 "" H 6350 3600 50  0000 C CNN
F 3 "" H 6350 3600 50  0000 C CNN
	1    6350 3600
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR03
U 1 1 58BC38D1
P 4600 3600
F 0 "#PWR03" H 4600 3450 50  0001 C CNN
F 1 "+5V" H 4600 3740 50  0000 C CNN
F 2 "" H 4600 3600 50  0000 C CNN
F 3 "" H 4600 3600 50  0000 C CNN
	1    4600 3600
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR04
U 1 1 58BC3E12
P 4550 2600
F 0 "#PWR04" H 4550 2350 50  0001 C CNN
F 1 "GND" H 4550 2450 50  0000 C CNN
F 2 "" H 4550 2600 50  0000 C CNN
F 3 "" H 4550 2600 50  0000 C CNN
	1    4550 2600
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR05
U 1 1 58BC3E35
P 2000 2500
F 0 "#PWR05" H 2000 2350 50  0001 C CNN
F 1 "+3.3V" H 2000 2640 50  0000 C CNN
F 2 "" H 2000 2500 50  0000 C CNN
F 3 "" H 2000 2500 50  0000 C CNN
	1    2000 2500
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 58BC435D
P 8000 2450
F 0 "R1" V 8080 2450 50  0000 C CNN
F 1 "25" V 8000 2450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 7930 2450 50  0001 C CNN
F 3 "" H 8000 2450 50  0000 C CNN
	1    8000 2450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 58BC43F9
P 5950 1700
F 0 "#PWR06" H 5950 1450 50  0001 C CNN
F 1 "GND" H 5950 1550 50  0000 C CNN
F 2 "" H 5950 1700 50  0000 C CNN
F 3 "" H 5950 1700 50  0000 C CNN
	1    5950 1700
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR07
U 1 1 58BC455F
P 7750 2200
F 0 "#PWR07" H 7750 2050 50  0001 C CNN
F 1 "+5V" H 7750 2340 50  0000 C CNN
F 2 "" H 7750 2200 50  0000 C CNN
F 3 "" H 7750 2200 50  0000 C CNN
	1    7750 2200
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X03 P2
U 1 1 58BC467C
P 7750 3900
F 0 "P2" H 7750 4100 50  0000 C CNN
F 1 "TL1838_PINHEADER" V 7850 3900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 7750 3900 50  0001 C CNN
F 3 "" H 7750 3900 50  0000 C CNN
	1    7750 3900
	1    0    0    -1  
$EndComp
Text GLabel 5900 950  0    60   Input ~ 0
LED_DR
Text GLabel 4150 1900 2    60   Input ~ 0
LED_DR
$Comp
L GND #PWR08
U 1 1 58BC492A
P 7300 3700
F 0 "#PWR08" H 7300 3450 50  0001 C CNN
F 1 "GND" H 7300 3550 50  0000 C CNN
F 2 "" H 7300 3700 50  0000 C CNN
F 3 "" H 7300 3700 50  0000 C CNN
	1    7300 3700
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR09
U 1 1 58BC49D6
P 7400 3550
F 0 "#PWR09" H 7400 3400 50  0001 C CNN
F 1 "+3.3V" H 7400 3690 50  0000 C CNN
F 2 "" H 7400 3550 50  0000 C CNN
F 3 "" H 7400 3550 50  0000 C CNN
	1    7400 3550
	1    0    0    -1  
$EndComp
Text GLabel 7400 4000 0    60   Input ~ 0
IR_IN
Text GLabel 4600 2000 2    60   Input ~ 0
IR_IN
$Comp
L Q_NPN_BEC Q2
U 1 1 58BC4E69
P 6250 1250
F 0 "Q2" H 6550 1300 50  0000 R CNN
F 1 "Q_NPN_BEC (MMBT2222ALT1G, 1459098 on E14)" V 5600 2200 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 6450 1350 50  0001 C CNN
F 3 "" H 6250 1250 50  0000 C CNN
	1    6250 1250
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 58BC4E75
P 8150 2450
F 0 "R2" V 8230 2450 50  0000 C CNN
F 1 "25" V 8150 2450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 8080 2450 50  0001 C CNN
F 3 "" H 8150 2450 50  0000 C CNN
	1    8150 2450
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P3
U 1 1 58BC52EE
P 8000 4950
F 0 "P3" H 8000 5150 50  0000 C CNN
F 1 "DS18B20_PINHEADER_TO92" V 8100 4950 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Narrow_Oval" H 8000 4950 50  0001 C CNN
F 3 "" H 8000 4950 50  0000 C CNN
	1    8000 4950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 58BC52F4
P 7650 5200
F 0 "#PWR010" H 7650 4950 50  0001 C CNN
F 1 "GND" H 7650 5050 50  0000 C CNN
F 2 "" H 7650 5200 50  0000 C CNN
F 3 "" H 7650 5200 50  0000 C CNN
	1    7650 5200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR011
U 1 1 58BC52FA
P 7650 4600
F 0 "#PWR011" H 7650 4450 50  0001 C CNN
F 1 "+3.3V" H 7650 4740 50  0000 C CNN
F 2 "" H 7650 4600 50  0000 C CNN
F 3 "" H 7650 4600 50  0000 C CNN
	1    7650 4600
	1    0    0    -1  
$EndComp
Text GLabel 7400 4950 0    60   Input ~ 0
TEMP_READ
Text GLabel 2000 2200 0    60   Input ~ 0
TEMP_READ
$Comp
L R R3
U 1 1 58BC5859
P 7250 4750
F 0 "R3" V 7330 4750 50  0000 C CNN
F 1 "4.7k" V 7250 4750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 7180 4750 50  0001 C CNN
F 3 "" H 7250 4750 50  0000 C CNN
	1    7250 4750
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 58C22194
P 7850 2450
F 0 "R4" V 7930 2450 50  0000 C CNN
F 1 "25" V 7850 2450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 7780 2450 50  0001 C CNN
F 3 "" H 7850 2450 50  0000 C CNN
	1    7850 2450
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 58C2225F
P 8300 2450
F 0 "R5" V 8380 2450 50  0000 C CNN
F 1 "25" V 8300 2450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 8230 2450 50  0001 C CNN
F 3 "" H 8300 2450 50  0000 C CNN
	1    8300 2450
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X04 P4
U 1 1 58C250C9
P 7500 2850
F 0 "P4" H 7500 3100 50  0000 C CNN
F 1 "CONN_02X04" H 7500 2600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x04" H 7500 1650 50  0001 C CNN
F 3 "" H 7500 1650 50  0000 C CNN
	1    7500 2850
	1    0    0    -1  
$EndComp
$Comp
L Q_NPN_BEC Q1
U 1 1 58C25AF4
P 6850 1250
F 0 "Q1" H 7150 1300 50  0000 R CNN
F 1 "Q_NPN_BEC (MMBT2222ALT1G, 1459098 on E14)" V 6300 2250 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 7050 1350 50  0001 C CNN
F 3 "" H 6850 1250 50  0000 C CNN
	1    6850 1250
	0    1    1    0   
$EndComp
$Comp
L Q_NPN_BEC Q3
U 1 1 58C25C16
P 7450 1250
F 0 "Q3" H 7750 1300 50  0000 R CNN
F 1 "Q_NPN_BEC (MMBT2222ALT1G, 1459098 on E14)" V 7000 2250 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 7650 1350 50  0001 C CNN
F 3 "" H 7450 1250 50  0000 C CNN
	1    7450 1250
	0    1    1    0   
$EndComp
$Comp
L Q_NPN_BEC Q4
U 1 1 58C25C76
P 8050 1250
F 0 "Q4" H 8350 1300 50  0000 R CNN
F 1 "Q_NPN_BEC (MMBT2222ALT1G, 1459098 on E14)" V 7700 2250 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 8250 1350 50  0001 C CNN
F 3 "" H 8050 1250 50  0000 C CNN
	1    8050 1250
	0    1    1    0   
$EndComp
Text GLabel 7050 2500 1    60   Input ~ 0
LED_DR_5
Text GLabel 8450 1750 2    60   Input ~ 0
LED_DR_5
Text GLabel 4100 1000 1    60   Input ~ 0
TXD_UA_1
Text GLabel 4250 1000 1    60   Input ~ 0
RXD_UA_1
$Comp
L CONN_01X04 P5
U 1 1 58C2D4F6
P 4700 5500
F 0 "P5" H 4700 5750 50  0000 C CNN
F 1 "CONN_01X04" V 4800 5500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 4700 5500 50  0001 C CNN
F 3 "" H 4700 5500 50  0000 C CNN
	1    4700 5500
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR012
U 1 1 58C2D5B7
P 4450 5150
F 0 "#PWR012" H 4450 5000 50  0001 C CNN
F 1 "+3.3V" H 4450 5290 50  0000 C CNN
F 2 "" H 4450 5150 50  0000 C CNN
F 3 "" H 4450 5150 50  0000 C CNN
	1    4450 5150
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR013
U 1 1 58C2D60A
P 4900 5150
F 0 "#PWR013" H 4900 4900 50  0001 C CNN
F 1 "GND" H 4900 5000 50  0000 C CNN
F 2 "" H 4900 5150 50  0000 C CNN
F 3 "" H 4900 5150 50  0000 C CNN
	1    4900 5150
	0    -1   -1   0   
$EndComp
Text GLabel 4550 4950 0    60   Input ~ 0
TXD_UA_1
Text GLabel 4850 4950 2    60   Input ~ 0
RXD_UA_1
$Comp
L R R9
U 1 1 58C2E741
P 1900 1900
F 0 "R9" V 1980 1900 50  0000 C CNN
F 1 "4.7k" V 1900 1900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1830 1900 50  0001 C CNN
F 3 "" H 1900 1900 50  0000 C CNN
	1    1900 1900
	0    1    1    0   
$EndComp
$Comp
L R R8
U 1 1 58C2E7E2
P 1900 1700
F 0 "R8" V 1980 1700 50  0000 C CNN
F 1 "4.7k" V 1900 1700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1830 1700 50  0001 C CNN
F 3 "" H 1900 1700 50  0000 C CNN
	1    1900 1700
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR014
U 1 1 58C2E848
P 1650 1600
F 0 "#PWR014" H 1650 1450 50  0001 C CNN
F 1 "+3.3V" H 1650 1740 50  0000 C CNN
F 2 "" H 1650 1600 50  0000 C CNN
F 3 "" H 1650 1600 50  0000 C CNN
	1    1650 1600
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 58C2E9EB
P 2500 1050
F 0 "SW1" H 2650 1160 50  0000 C CNN
F 1 "SW_PUSH" H 2500 970 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_FSMSM" H 2500 1050 50  0001 C CNN
F 3 "" H 2500 1050 50  0000 C CNN
	1    2500 1050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 58C2EADC
P 2900 1050
F 0 "#PWR015" H 2900 800 50  0001 C CNN
F 1 "GND" H 2900 900 50  0000 C CNN
F 2 "" H 2900 1050 50  0000 C CNN
F 3 "" H 2900 1050 50  0000 C CNN
	1    2900 1050
	0    -1   -1   0   
$EndComp
$Comp
L R R10
U 1 1 58C2FA5E
P 4250 2300
F 0 "R10" V 4330 2300 50  0000 C CNN
F 1 "4.7k" V 4250 2300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4180 2300 50  0001 C CNN
F 3 "" H 4250 2300 50  0000 C CNN
	1    4250 2300
	0    1    1    0   
$EndComp
$Comp
L R R11
U 1 1 58C2FF00
P 4600 2200
F 0 "R11" V 4680 2200 50  0000 C CNN
F 1 "4.7k" V 4600 2200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4530 2200 50  0001 C CNN
F 3 "" H 4600 2200 50  0000 C CNN
	1    4600 2200
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR016
U 1 1 58C2FF8D
P 5300 2350
F 0 "#PWR016" H 5300 2200 50  0001 C CNN
F 1 "+3.3V" H 5300 2490 50  0000 C CNN
F 2 "" H 5300 2350 50  0000 C CNN
F 3 "" H 5300 2350 50  0000 C CNN
	1    5300 2350
	-1   0    0    1   
$EndComp
$Comp
L R R12
U 1 1 58C3000C
P 5050 2100
F 0 "R12" V 5130 2100 50  0000 C CNN
F 1 "4.7k" V 5050 2100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4980 2100 50  0001 C CNN
F 3 "" H 5050 2100 50  0000 C CNN
	1    5050 2100
	0    1    1    0   
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 58C30450
P 4050 2850
F 0 "SW2" H 4200 2960 50  0000 C CNN
F 1 "SW_PUSH" H 4050 2770 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_FSMSM" H 4050 2850 50  0001 C CNN
F 3 "" H 4050 2850 50  0000 C CNN
	1    4050 2850
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR017
U 1 1 58C3055D
P 4150 3250
F 0 "#PWR017" H 4150 3000 50  0001 C CNN
F 1 "GND" H 4150 3100 50  0000 C CNN
F 2 "" H 4150 3250 50  0000 C CNN
F 3 "" H 4150 3250 50  0000 C CNN
	1    4150 3250
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X03 P8
U 1 1 58C30AF4
P 6600 2800
F 0 "P8" H 6600 3000 50  0000 C CNN
F 1 "TEMP6000" V 6700 2800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 6600 2800 50  0001 C CNN
F 3 "" H 6600 2800 50  0000 C CNN
	1    6600 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 58C30AFA
P 6150 2600
F 0 "#PWR018" H 6150 2350 50  0001 C CNN
F 1 "GND" H 6150 2450 50  0000 C CNN
F 2 "" H 6150 2600 50  0000 C CNN
F 3 "" H 6150 2600 50  0000 C CNN
	1    6150 2600
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR019
U 1 1 58C30B00
P 6250 2450
F 0 "#PWR019" H 6250 2300 50  0001 C CNN
F 1 "+3.3V" H 6250 2590 50  0000 C CNN
F 2 "" H 6250 2450 50  0000 C CNN
F 3 "" H 6250 2450 50  0000 C CNN
	1    6250 2450
	1    0    0    -1  
$EndComp
Text GLabel 6250 2900 0    60   Input ~ 0
TEMT
Text GLabel 1400 1800 0    60   Input ~ 0
TEMT
$Comp
L CONN_01X04 P7
U 1 1 58C312F3
P 3200 3450
F 0 "P7" H 3200 3700 50  0000 C CNN
F 1 "CONN_01X04" V 3300 3450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 3200 3450 50  0001 C CNN
F 3 "" H 3200 3450 50  0000 C CNN
	1    3200 3450
	0    1    1    0   
$EndComp
$Comp
L CONN_01X05 P6
U 1 1 58C3191F
P 2300 3450
F 0 "P6" H 2300 3750 50  0000 C CNN
F 1 "CONN_01X05" V 2400 3450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05" H 2300 3450 50  0001 C CNN
F 3 "" H 2300 3450 50  0000 C CNN
	1    2300 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	5550 3900 5550 4150
Wire Wire Line
	6200 4100 6200 4000
Wire Wire Line
	4800 4100 6200 4100
Connection ~ 5550 4100
Wire Wire Line
	4800 4000 4800 4100
Wire Wire Line
	5050 4000 5050 4100
Connection ~ 5050 4100
Wire Wire Line
	5950 4000 5950 4100
Connection ~ 5950 4100
Wire Wire Line
	4600 3600 5250 3600
Wire Wire Line
	5850 3600 6350 3600
Wire Wire Line
	6200 3600 6200 3700
Connection ~ 6200 3600
Wire Wire Line
	5950 3700 5950 3600
Connection ~ 5950 3600
Wire Wire Line
	5050 3700 5050 3600
Connection ~ 5050 3600
Wire Wire Line
	4800 3700 4800 3600
Connection ~ 4800 3600
Wire Wire Line
	2200 2400 2000 2400
Wire Wire Line
	2000 2400 2000 2500
Wire Wire Line
	7400 3550 7400 3800
Wire Wire Line
	7400 3800 7550 3800
Wire Wire Line
	7300 3700 7300 3900
Wire Wire Line
	7300 3900 7550 3900
Wire Wire Line
	7400 4000 7550 4000
Wire Wire Line
	4000 2000 4600 2000
Wire Wire Line
	4000 1900 4150 1900
Wire Wire Line
	7650 4600 7650 4850
Wire Wire Line
	7650 4850 7800 4850
Wire Wire Line
	7650 5200 7650 5050
Wire Wire Line
	7650 5050 7800 5050
Wire Wire Line
	2000 2200 2200 2200
Wire Wire Line
	7400 4950 7800 4950
Wire Wire Line
	7400 4750 7500 4750
Wire Wire Line
	7500 4750 7500 4950
Connection ~ 7500 4950
Wire Wire Line
	7100 4750 7050 4750
Wire Wire Line
	7050 4750 7050 4650
Wire Wire Line
	7050 4650 7550 4650
Wire Wire Line
	7550 4650 7550 4700
Wire Wire Line
	7550 4700 7650 4700
Connection ~ 7650 4700
Wire Wire Line
	7750 2700 7850 2700
Wire Wire Line
	7850 2700 7850 2600
Wire Wire Line
	7750 2800 8000 2800
Wire Wire Line
	8000 2800 8000 2600
Wire Wire Line
	8150 2600 8150 2900
Wire Wire Line
	8150 2900 7750 2900
Wire Wire Line
	7750 3000 8300 3000
Wire Wire Line
	8300 3000 8300 2600
Wire Wire Line
	8300 2200 8300 2300
Wire Wire Line
	7750 2200 8300 2200
Wire Wire Line
	7850 2300 7850 2200
Connection ~ 7850 2200
Wire Wire Line
	8000 2300 8000 2200
Connection ~ 8000 2200
Wire Wire Line
	8150 2300 8150 2200
Connection ~ 8150 2200
Wire Wire Line
	7050 3000 7250 3000
Wire Wire Line
	7050 2500 7050 3000
Wire Wire Line
	7250 2900 7050 2900
Connection ~ 7050 2900
Wire Wire Line
	7050 2800 7250 2800
Connection ~ 7050 2800
Wire Wire Line
	7250 2700 7050 2700
Connection ~ 7050 2700
Wire Wire Line
	5900 950  8050 950 
Wire Wire Line
	8050 950  8050 1050
Wire Wire Line
	7450 950  7450 1050
Connection ~ 7450 950 
Wire Wire Line
	6850 950  6850 1050
Connection ~ 6850 950 
Wire Wire Line
	6250 1050 6250 950 
Connection ~ 6250 950 
Wire Wire Line
	6050 1350 5950 1350
Wire Wire Line
	5950 1350 5950 1700
Wire Wire Line
	6650 1350 6600 1350
Wire Wire Line
	6600 1350 6600 1600
Wire Wire Line
	5950 1600 7800 1600
Connection ~ 5950 1600
Wire Wire Line
	7250 1350 7200 1350
Wire Wire Line
	7200 1350 7200 1600
Connection ~ 6600 1600
Wire Wire Line
	7850 1350 7800 1350
Wire Wire Line
	7800 1350 7800 1600
Connection ~ 7200 1600
Wire Wire Line
	6450 1350 6500 1350
Wire Wire Line
	6500 1350 6500 1750
Wire Wire Line
	6500 1750 8450 1750
Wire Wire Line
	7050 1350 7100 1350
Wire Wire Line
	7100 1350 7100 1750
Connection ~ 7100 1750
Wire Wire Line
	7650 1350 7700 1350
Wire Wire Line
	7700 1350 7700 1750
Connection ~ 7700 1750
Wire Wire Line
	8250 1350 8300 1350
Wire Wire Line
	8300 1350 8300 1750
Connection ~ 8300 1750
Wire Wire Line
	4250 1700 4000 1700
Wire Wire Line
	4250 1000 4250 1700
Wire Wire Line
	4100 1800 4000 1800
Wire Wire Line
	4100 1000 4100 1800
Wire Wire Line
	4450 5150 4550 5150
Wire Wire Line
	4550 5150 4550 5300
Wire Wire Line
	4550 4950 4650 4950
Wire Wire Line
	4650 4950 4650 5300
Wire Wire Line
	4900 5150 4850 5150
Wire Wire Line
	4850 5150 4850 5300
Wire Wire Line
	4750 5300 4750 4950
Wire Wire Line
	4750 4950 4850 4950
Wire Wire Line
	1650 1600 1650 1900
Wire Wire Line
	1650 1900 1750 1900
Wire Wire Line
	1750 1700 1650 1700
Connection ~ 1650 1700
Wire Wire Line
	2050 1700 2200 1700
Wire Wire Line
	2200 1900 2050 1900
Wire Wire Line
	2100 1700 2100 1050
Wire Wire Line
	2100 1050 2200 1050
Connection ~ 2100 1700
Wire Wire Line
	2800 1050 2900 1050
Wire Wire Line
	4000 2300 4100 2300
Wire Wire Line
	4550 2300 4550 2600
Wire Wire Line
	4550 2300 4400 2300
Wire Wire Line
	4000 2400 4550 2400
Connection ~ 4550 2400
Wire Wire Line
	5200 2100 5300 2100
Wire Wire Line
	5300 2100 5300 2350
Wire Wire Line
	4000 2100 4900 2100
Wire Wire Line
	4000 2200 4450 2200
Wire Wire Line
	4750 2200 5300 2200
Connection ~ 5300 2200
Wire Wire Line
	4050 2550 4050 2100
Connection ~ 4050 2100
Wire Wire Line
	4050 3150 4050 3250
Wire Wire Line
	4050 3250 4150 3250
Wire Wire Line
	6250 2450 6250 2700
Wire Wire Line
	6250 2700 6400 2700
Wire Wire Line
	6150 2600 6150 2800
Wire Wire Line
	6150 2800 6400 2800
Wire Wire Line
	6250 2900 6400 2900
Wire Wire Line
	1400 1800 2200 1800
Wire Wire Line
	3350 2900 3350 3250
Wire Wire Line
	3250 2900 3250 3250
Wire Wire Line
	2950 2900 2950 3100
Wire Wire Line
	2950 3100 3150 3100
Wire Wire Line
	3150 3100 3150 3250
Wire Wire Line
	3050 3250 3050 3150
Wire Wire Line
	3050 3150 2850 3150
Wire Wire Line
	2850 3150 2850 2900
Wire Wire Line
	3050 2900 3050 2950
Wire Wire Line
	3050 2950 2500 2950
Wire Wire Line
	2500 2950 2500 3250
Wire Wire Line
	3150 2900 3150 3000
Wire Wire Line
	3150 3000 2400 3000
Wire Wire Line
	2400 3000 2400 3250
Wire Wire Line
	2200 2300 2150 2300
Wire Wire Line
	2150 2300 2150 2650
Wire Wire Line
	2150 2650 2300 2650
Wire Wire Line
	2300 2650 2300 3250
Wire Wire Line
	2200 2100 1400 2100
Wire Wire Line
	1400 2100 1400 2800
Wire Wire Line
	1400 2800 2200 2800
Wire Wire Line
	2200 2800 2200 3250
Wire Wire Line
	2200 2000 1300 2000
Wire Wire Line
	1300 2000 1300 2900
Wire Wire Line
	1300 2900 2100 2900
Wire Wire Line
	2100 2900 2100 3250
$Comp
L GND #PWR020
U 1 1 58C2E738
P 10100 3350
F 0 "#PWR020" H 10100 3100 50  0001 C CNN
F 1 "GND" H 10100 3200 50  0000 C CNN
F 2 "" H 10100 3350 50  0000 C CNN
F 3 "" H 10100 3350 50  0000 C CNN
	1    10100 3350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR021
U 1 1 58C2E7AC
P 10200 2500
F 0 "#PWR021" H 10200 2350 50  0001 C CNN
F 1 "+5V" H 10200 2640 50  0000 C CNN
F 2 "" H 10200 2500 50  0000 C CNN
F 3 "" H 10200 2500 50  0000 C CNN
	1    10200 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 2600 10200 2600
Wire Wire Line
	10200 2600 10200 2500
$Comp
L USB_OTG P1
U 1 1 58E5A42E
P 10600 2800
F 0 "P1" H 10925 2675 50  0000 C CNN
F 1 "USB_OTG" H 10600 3000 50  0000 C CNN
F 2 "MyKiCadLibs:USB_Micro-B-OshPark" V 10550 2700 50  0001 C CNN
F 3 "" V 10550 2700 50  0000 C CNN
	1    10600 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	10300 3000 10100 3000
Wire Wire Line
	10100 3000 10100 3350
Wire Wire Line
	10700 3200 10700 3250
Wire Wire Line
	10700 3250 10100 3250
Connection ~ 10100 3250
$EndSCHEMATC