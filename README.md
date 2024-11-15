# Code for 6Sens Project : simple "Hello World!" test for my own MAMWLExx (based on STM32WLEx) board

## Overview
This application contains example code to allow testing of LoRa radios (point to point communications). This is useful for validating your LoRa radio is working correctly before trying to connect to LoRaWAN networks. The version of Zephyr RTOS used is the version v3.6.0.

Please check the frequency/channel configuration prior to use and ensure you are transmitting on a permitted band for your country.

**First Board used** :  Cicerone board by Move-X 

**Second Board used** : Original MAMWLExx board, powered by battery/solar panel. (see 6sens_project repository/hardware part, for more information.)

## Building and Running
The following commands clean build folder, build and flash the sample:

**Command to use**

west build -p always -b stm32wl_dw1000_iot_board applications/stm32wle5_rtos_lora

west flash --runner pyocd