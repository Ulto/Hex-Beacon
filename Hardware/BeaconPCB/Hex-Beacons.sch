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
Sheet 1 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 3000 2300 1400 1300
U 59AC571E
F0 "ESP32" 60
F1 "ESP32.sch" 60
F2 "ESP_MOSI" O R 4400 2450 60 
F3 "ESP_MISO" I R 4400 2600 60 
F4 "ESP_SCLK" O R 4400 2750 60 
F5 "ESP_SS" O R 4400 2900 60 
$EndSheet
$Sheet
S 5950 2300 1450 1300
U 59AC5A80
F0 "STM32" 60
F1 "STM32.sch" 60
F2 "ESP_SS" I L 5950 2900 60 
F3 "ESP_SCLK" I L 5950 2750 60 
F4 "ESP_MISO" O L 5950 2600 60 
F5 "ESP_MOSI" I L 5950 2450 60 
F6 "SPI2_MOSI" O R 7400 3050 60 
F7 "SPI2_SCK" O R 7400 3200 60 
$EndSheet
$Sheet
S 3350 4950 2150 1000
U 59ADA955
F0 "PSU" 60
F1 "PSU.sch" 60
$EndSheet
$Sheet
S 7000 4650 2250 1250
U 59ADAAF7
F0 "APA102" 60
F1 "APA102.sch" 60
$EndSheet
Wire Wire Line
	4400 2450 5950 2450
Wire Wire Line
	5950 2600 4400 2600
Wire Wire Line
	4400 2750 5950 2750
Wire Wire Line
	5950 2900 4400 2900
$EndSCHEMATC
