#nrf5-ble-tutorial-characteristic
 
# Requirements

* nRF52 DK
* nRF52840 Dongle or an additional development kit
* nRF Connect Bluetooth low energy app for Desktop. You can also use nRF Connect for mobile found in both Google Play on Android and App Store for iPhone.
* Keil uVision v5.xx or SEGGER Embedded Studio (SES)
* SDK v15.0.0.
* SoftDevice S140 V6.x.x
* Example files.

Other kits, dongles and software versions might work as well, but this will not be covered here.

# About this project
This project uses these features ; BLE GAP, GATT, Services and Characteristics, Serial UART, SAADC, TIMER and GPIO


I used Advertising, Services, Characteristics and Timer tutorials on Nordic DevZone. Here is the link https://devzone.nordicsemi.com/nordic/

I created two services and three characteristics.

Service_1 = It contains a Characteristic which shows the Analog-Digital conversion results on AIN0.

 * Characteristic_1 = It shows digital output of AIN0 pin.
 
Service_2 = It contains two characteristics. Characteristic_2 and Characteristic_3

 * Characteristic_2 = It contains CPU Temperature value and notify it.

 * Characteristic_3 = It holds a value(a byte). I used this value for blinking led. (You can use whatever you want)

The application is built to be used with the official nRF5 SDK, that can be downloaded from http://developer.nordicsemi.com/.
