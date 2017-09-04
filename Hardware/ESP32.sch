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
LIBS:STM32F042C6T6
LIBS:Hex-Beacons-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
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
L ESP32-WROOM U?
U 1 1 59AC5727
P 5800 3700
F 0 "U?" H 5100 4950 60  0000 C CNN
F 1 "ESP32-WROOM" H 6300 4950 60  0000 C CNN
F 2 "ESP32-footprints-Lib:ESP32-WROOM" H 6150 5050 60  0001 C CNN
F 3 "" H 5350 4150 60  0001 C CNN
	1    5800 3700
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 59AC5D70
P 4400 2850
F 0 "#PWR?" H 4400 2700 50  0001 C CNN
F 1 "+3V3" H 4400 2990 50  0000 C CNN
F 2 "" H 4400 2850 50  0001 C CNN
F 3 "" H 4400 2850 50  0001 C CNN
	1    4400 2850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59AC6014
P 6850 4950
F 0 "#PWR?" H 6850 4700 50  0001 C CNN
F 1 "GND" H 6850 4800 50  0000 C CNN
F 2 "" H 6850 4950 50  0001 C CNN
F 3 "" H 6850 4950 50  0001 C CNN
	1    6850 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 4250 6850 4250
Wire Wire Line
	6850 4250 6850 4950
Wire Wire Line
	6700 4350 6850 4350
Connection ~ 6850 4350
Wire Wire Line
	5350 4750 5350 4850
Wire Wire Line
	4700 4850 6850 4850
Connection ~ 6850 4850
Wire Wire Line
	4850 4400 4700 4400
Wire Wire Line
	4700 4400 4700 4850
Connection ~ 5350 4850
Wire Wire Line
	4850 3100 4400 3100
Wire Wire Line
	4400 3100 4400 2850
$Comp
L SW_DPST SW?
U 1 1 59AC60FC
P 1750 6800
F 0 "SW?" H 1750 7000 50  0000 C CNN
F 1 "SW_DPST" H 1750 6600 50  0000 C CNN
F 2 "" H 1750 6800 50  0001 C CNN
F 3 "" H 1750 6800 50  0001 C CNN
	1    1750 6800
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 59AC628F
P 2300 6300
F 0 "#PWR?" H 2300 6150 50  0001 C CNN
F 1 "+3V3" H 2300 6440 50  0000 C CNN
F 2 "" H 2300 6300 50  0001 C CNN
F 3 "" H 2300 6300 50  0001 C CNN
	1    2300 6300
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 59AC62B3
P 2300 6500
F 0 "R?" V 2380 6500 50  0000 C CNN
F 1 "10k" V 2300 6500 50  0000 C CNN
F 2 "" V 2230 6500 50  0001 C CNN
F 3 "" H 2300 6500 50  0001 C CNN
	1    2300 6500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59AC6351
P 1300 7100
F 0 "#PWR?" H 1300 6850 50  0001 C CNN
F 1 "GND" H 1300 6950 50  0000 C CNN
F 2 "" H 1300 7100 50  0001 C CNN
F 3 "" H 1300 7100 50  0001 C CNN
	1    1300 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 6900 1300 6900
Wire Wire Line
	1300 6700 1300 7100
Wire Wire Line
	1550 6700 1300 6700
Connection ~ 1300 6900
Wire Wire Line
	1950 6700 3100 6700
Wire Wire Line
	2300 6700 2300 6650
Wire Wire Line
	2300 6350 2300 6300
Connection ~ 2300 6700
Text Label 2650 6700 0    60   ~ 0
ESP_RESET
Wire Wire Line
	3850 3200 4850 3200
Text Label 4350 3200 2    60   ~ 0
ESP_RESET
$Comp
L C C?
U 1 1 59AC6527
P 2500 6950
F 0 "C?" H 2525 7050 50  0000 L CNN
F 1 "1uF" H 2525 6850 50  0000 L CNN
F 2 "" H 2538 6800 50  0001 C CNN
F 3 "" H 2500 6950 50  0001 C CNN
	1    2500 6950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59AC65A3
P 2500 7200
F 0 "#PWR?" H 2500 6950 50  0001 C CNN
F 1 "GND" H 2500 7050 50  0000 C CNN
F 2 "" H 2500 7200 50  0001 C CNN
F 3 "" H 2500 7200 50  0001 C CNN
	1    2500 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 7200 2500 7100
Wire Wire Line
	2500 6800 2500 6700
Connection ~ 2500 6700
$Comp
L CONN_01X06 J?
U 1 1 59AC67C1
P 10650 1350
F 0 "J?" H 10650 1700 50  0000 C CNN
F 1 "CONN_01X06" V 10750 1350 50  0000 C CNN
F 2 "" H 10650 1350 50  0001 C CNN
F 3 "" H 10650 1350 50  0001 C CNN
	1    10650 1350
	1    0    0    1   
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 59AC6967
P 10200 1000
F 0 "#PWR?" H 10200 850 50  0001 C CNN
F 1 "+3V3" H 10200 1140 50  0000 C CNN
F 2 "" H 10200 1000 50  0001 C CNN
F 3 "" H 10200 1000 50  0001 C CNN
	1    10200 1000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59AC6A53
P 10200 1750
F 0 "#PWR?" H 10200 1500 50  0001 C CNN
F 1 "GND" H 10200 1600 50  0000 C CNN
F 2 "" H 10200 1750 50  0001 C CNN
F 3 "" H 10200 1750 50  0001 C CNN
	1    10200 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 1750 10200 1600
Wire Wire Line
	10200 1600 10450 1600
Wire Wire Line
	10200 1400 10450 1400
Wire Wire Line
	10200 1400 10200 1000
Wire Wire Line
	10450 1500 9800 1500
Wire Wire Line
	10450 1300 9800 1300
Wire Wire Line
	10450 1200 9800 1200
Wire Wire Line
	10450 1100 9800 1100
Text Label 9800 1500 0    60   ~ 0
CTS
Text Label 9800 1300 0    60   ~ 0
TXD
Text Label 9800 1200 0    60   ~ 0
RXD
Text Label 9800 1100 0    60   ~ 0
DTR
Text Notes 9700 700  0    60   ~ 0
FTDI Programming Header
Text Notes 2950 6050 0    60   ~ 0
ESP32 Reset Circuit
$Comp
L Q_NPN_BCE Q?
U 1 1 59AC6F40
P 4450 6550
F 0 "Q?" H 4650 6600 50  0000 L CNN
F 1 "Q_NPN_BCE" H 4650 6500 50  0000 L CNN
F 2 "" H 4650 6650 50  0001 C CNN
F 3 "" H 4450 6550 50  0001 C CNN
	1    4450 6550
	1    0    0    -1  
$EndComp
$Comp
L Q_NPN_BCE Q?
U 1 1 59AC6F9F
P 4450 7250
F 0 "Q?" H 4650 7300 50  0000 L CNN
F 1 "Q_NPN_BCE" H 4650 7200 50  0000 L CNN
F 2 "" H 4650 7350 50  0001 C CNN
F 3 "" H 4450 7250 50  0001 C CNN
	1    4450 7250
	1    0    0    1   
$EndComp
Wire Wire Line
	4550 7450 4550 7550
Wire Wire Line
	4550 7550 5050 7550
Wire Wire Line
	4550 6750 4550 6850
Wire Wire Line
	3850 7550 3600 7550
Wire Wire Line
	4550 7050 4550 6950
Wire Wire Line
	4550 6950 3850 6950
Wire Wire Line
	3850 6950 3850 6350
Wire Wire Line
	3850 6350 3650 6350
Wire Wire Line
	4550 6850 4450 6850
Wire Wire Line
	4450 6850 4450 7050
Wire Wire Line
	4450 7050 3850 7050
Wire Wire Line
	3850 7050 3850 7550
$Comp
L R R?
U 1 1 59AC7428
P 4050 6550
F 0 "R?" V 4130 6550 50  0000 C CNN
F 1 "10k" V 4050 6550 50  0000 C CNN
F 2 "" V 3980 6550 50  0001 C CNN
F 3 "" H 4050 6550 50  0001 C CNN
	1    4050 6550
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59AC74B4
P 4050 7250
F 0 "R?" V 4130 7250 50  0000 C CNN
F 1 "10k" V 4050 7250 50  0000 C CNN
F 2 "" V 3980 7250 50  0001 C CNN
F 3 "" H 4050 7250 50  0001 C CNN
	1    4050 7250
	-1   0    0    1   
$EndComp
Wire Wire Line
	4200 7250 4250 7250
Wire Wire Line
	3900 7250 3850 7250
Connection ~ 3850 7250
Wire Wire Line
	4200 6550 4250 6550
Wire Wire Line
	3900 6550 3850 6550
Connection ~ 3850 6550
Text Label 3650 6350 0    60   ~ 0
RTS
Text Label 3600 7550 0    60   ~ 0
DTR
Text Label 5050 7550 0    60   ~ 0
ESP_RESET
Wire Wire Line
	4550 6350 4550 6250
Wire Wire Line
	4550 6250 5050 6250
Text Label 5050 6250 0    60   ~ 0
GPIO0
Wire Wire Line
	6700 4150 7600 4150
Text Label 7600 4150 2    60   ~ 0
GPIO0
Wire Wire Line
	3550 3500 4850 3500
Wire Wire Line
	3550 3600 4850 3600
Wire Wire Line
	3550 3700 4850 3700
Wire Wire Line
	3550 3800 4850 3800
Wire Bus Line
	3450 3800 3450 3300
Entry Wire Line
	3450 3400 3550 3500
Entry Wire Line
	3450 3500 3550 3600
Entry Wire Line
	3450 3600 3550 3700
Entry Wire Line
	3450 3700 3550 3800
Text HLabel 3450 3300 1    60   BiDi ~ 0
ESP_SPI
Text Label 3850 3500 0    60   ~ 0
ESP_MOSI
Text Label 3850 3600 0    60   ~ 0
ESP_MISO
Text Label 3850 3700 0    60   ~ 0
ESP_SCLK
Text Label 3850 3800 0    60   ~ 0
ESP_SS
Wire Wire Line
	6700 3150 7600 3150
Wire Wire Line
	6700 3250 7600 3250
Text Label 7600 3150 2    60   ~ 0
RXD
Text Label 7600 3250 2    60   ~ 0
TXD
$Comp
L LED D?
U 1 1 59ADB312
P 9850 5000
F 0 "D?" H 9850 5100 50  0000 C CNN
F 1 "LED" H 9850 4900 50  0000 C CNN
F 2 "" H 9850 5000 50  0001 C CNN
F 3 "" H 9850 5000 50  0001 C CNN
	1    9850 5000
	0    -1   -1   0   
$EndComp
$Comp
L LED D?
U 1 1 59ADB507
P 10350 5000
F 0 "D?" H 10350 5100 50  0000 C CNN
F 1 "LED" H 10350 4900 50  0000 C CNN
F 2 "" H 10350 5000 50  0001 C CNN
F 3 "" H 10350 5000 50  0001 C CNN
	1    10350 5000
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 59ADB627
P 9850 5450
F 0 "R?" V 9930 5450 50  0000 C CNN
F 1 "R" V 9850 5450 50  0000 C CNN
F 2 "" V 9780 5450 50  0001 C CNN
F 3 "" H 9850 5450 50  0001 C CNN
	1    9850 5450
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 59ADB694
P 10350 5450
F 0 "R?" V 10430 5450 50  0000 C CNN
F 1 "R" V 10350 5450 50  0000 C CNN
F 2 "" V 10280 5450 50  0001 C CNN
F 3 "" H 10350 5450 50  0001 C CNN
	1    10350 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 4850 9850 4750
Wire Wire Line
	9850 4750 9600 4750
Wire Wire Line
	10350 4850 10350 4500
Wire Wire Line
	10350 4500 9600 4500
Wire Wire Line
	9850 5300 9850 5150
Wire Wire Line
	10350 5300 10350 5150
$Comp
L GND #PWR?
U 1 1 59ADB821
P 10050 5800
F 0 "#PWR?" H 10050 5550 50  0001 C CNN
F 1 "GND" H 10050 5650 50  0000 C CNN
F 2 "" H 10050 5800 50  0001 C CNN
F 3 "" H 10050 5800 50  0001 C CNN
	1    10050 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 5600 9850 5700
Wire Wire Line
	9850 5700 10350 5700
Wire Wire Line
	10350 5700 10350 5600
Wire Wire Line
	10050 5800 10050 5700
Connection ~ 10050 5700
Text Label 9600 4750 2    60   ~ 0
GRN_LED
Text Label 9600 4500 2    60   ~ 0
RED_LED
Wire Wire Line
	6700 3650 7600 3650
Wire Wire Line
	6700 3550 7600 3550
Text Label 7600 3550 2    60   ~ 0
RED_LED
Text Label 7600 3650 2    60   ~ 0
GRN_LED
$EndSCHEMATC
