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
LIBS:crumpschemes
LIBS:Hex-Beacons-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 6
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
L GND #PWR?
U 1 1 59B3605D
P 3800 4200
F 0 "#PWR?" H 3800 3950 50  0001 C CNN
F 1 "GND" H 3800 4050 50  0000 C CNN
F 2 "" H 3800 4200 50  0001 C CNN
F 3 "" H 3800 4200 50  0001 C CNN
	1    3800 4200
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 59B36063
P 4050 2400
F 0 "C?" H 4075 2500 50  0000 L CNN
F 1 ".1uF" H 4075 2300 50  0000 L CNN
F 2 "" H 4088 2250 50  0001 C CNN
F 3 "" H 4050 2400 50  0001 C CNN
	1    4050 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59B3606A
P 4050 2550
F 0 "#PWR?" H 4050 2300 50  0001 C CNN
F 1 "GND" H 4050 2400 50  0000 C CNN
F 2 "" H 4050 2550 50  0001 C CNN
F 3 "" H 4050 2550 50  0001 C CNN
	1    4050 2550
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 59B36070
P 3800 2100
F 0 "#PWR?" H 3800 1950 50  0001 C CNN
F 1 "+3V3" H 3800 2240 50  0000 C CNN
F 2 "" H 3800 2100 50  0001 C CNN
F 3 "" H 3800 2100 50  0001 C CNN
	1    3800 2100
	1    0    0    -1  
$EndComp
$Comp
L 74HC244 U?
U 1 1 59B36076
P 3800 3350
F 0 "U?" H 3500 4000 50  0000 L CNN
F 1 "74HC244" H 4050 2700 50  0000 L CNN
F 2 "" H 3800 3350 50  0000 C CNN
F 3 "" H 3800 3350 50  0000 C CNN
	1    3800 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4200 3800 4050
Connection ~ 3800 2250
Wire Wire Line
	3800 2100 3800 2250
Wire Wire Line
	3800 2250 3800 2650
Wire Wire Line
	4050 2250 3800 2250
Wire Wire Line
	4300 2850 4700 2850
Wire Wire Line
	4300 2950 4700 2950
Wire Wire Line
	4300 3050 4700 3050
Wire Wire Line
	3300 3150 2950 3150
Wire Wire Line
	4300 3150 4700 3150
Wire Wire Line
	3300 3050 2950 3050
Wire Wire Line
	3300 2950 2950 2950
Wire Wire Line
	2950 2850 3300 2850
Text HLabel 4700 2850 2    60   Output ~ 0
ESP_MOSI
Text HLabel 2950 2950 0    60   Input ~ 0
ESP_MISO
Text HLabel 4700 3050 2    60   Output ~ 0
ESP_SCLK
Text HLabel 4700 3150 2    60   Output ~ 0
ESP_SS
$EndSCHEMATC
