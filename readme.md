# Azure IoTHub MQTT Client using mbed OS 5.x

This is an Azure IoTHub MQTT client example for mbed enabled board running on latest mbed OS.


## Introduction

When I learned [Azure IoT Device SDK for C], I wanted to try it on a mbed enabled board running latest [mbed OS]. After searched the web, I found this  [iothub_client_sample_mqtt - a mercurial repository | Mbed](https://developer.mbed.org/users/AzureIoTClient/code/iothub_client_sample_mqtt/). However, that example uses an older version of [mbed OS] and [wolfSSL]. Since my goal was using latest [mbed OS], and [mbed OS] also comes with another SSL/TLS library - [mbed TLS], so I decided to modify [iothub_client_sample_mqtt - a mercurial repository | Mbed](https://developer.mbed.org/users/AzureIoTClient/code/iothub_client_sample_mqtt/) example to use [mbed OS] 5.x and switch the used SSL/TLS library to [mbed TLS].


## Prerequisites

To try the example, you need these:

1. Obtain one mbed enabled board with Ethernet - I mainly used [ST NUCLEO-F429ZI](https://developer.mbed.org/platforms/ST-Nucleo-F429ZI/) board for the porting. I also tried the example successfully with an [NXP/Freescal FRDM-K64F](https://developer.mbed.org/platforms/FRDM-K64F/) board.
2. I used [GNU ARM Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads) as the compiler, the version I used is [6-2017-q2-update](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads).
3. Install `mbed CLI` - Refer [mbed CLI | mbed OS 5 Handbook](https://docs.mbed.com/docs/mbed-os-handbook/en/5.1/dev_tools/cli/) about installation and usages.
4. Obtain Azure IoTHub device credentails - Refer [The Azure IoT device SDK for C | Microsoft Docs](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-device-sdk-c-intro) for the details.


## How to build the example

### Steps:

1. Clone the example to a local folder as follows:
   ```sh
   mbed import https://github.com/maxpeng/mbedos_iothub_client_sample_mqtt.git
   ```
2. Modify the device connection string defined in `iothub_client_sample_mqtt.c`
   ```C
   static const char* connectionString = "[device connection string]";
   ```
   to the one of your device.
3. Change the working directory to `mbedos_iothub_client_sample_mqtt`, type following
command to build the example for `ST Nucleo F429ZI board`:
   ```sh
   mbed compile --profile azure_debug.json -t GCC_ARM -m NUCLEO_F429ZI
   ```
   To build the example for `NXP/Freescale K64F board`, then use this command:
   ```sh
   mbed compile --profile azure_debug.json -t GCC_ARM -m K64F
   ```
4. Copy the built application `mbedos_iothub_client_sample_mqtt\BUILD\NUCLEO_F429ZI\GCC_ARM\mbedos_iothub_client_sample_mqtt.bin` to the board.
5. Use [putty](http://www.putty.org/) to connect to the serial port of the board to
monitor the debug messages. The default serial port setting is 9600 8N1.

   Example of communication log:
   ```
   IoTHubClient_LL_SetMessageCallback...successful.
   IoTHubClient_LL_SendEventAsync accepted message [0] for transmission to IoT Hub.
   Info: handshake is done, result: 0x00000000.
   -> 15:10:30 CONNECT | VER: 4 | KEEPALIVE: 240 | FLAGS: 192 | USERNAME: xxxx.azure-devices.net/devce_id/api-version=2016-11-14&DeviceClientType=iothubclient%2f1.1.29%20(mbed) | PWD: XXXX | CLEAN: 0
   IoTHubClient_LL_SendEventAsync accepted message [1] for transmission to IoT Hub.
   <- 15:10:31 CONNACK | SESSION_PRESENT: true | RETURN_CODE: 0x0
   IoTHubClient_LL_SendEventAsync accepted message [2] for transmission to IoT Hub.
   -> 15:10:31 SUBSCRIBE | PACKET_ID: 2 | TOPIC_NAME: devices/dev01/messages/devicebound/# | QOS: 1
   IoTHubClient_LL_SendEventAsync accepted message [3] for transmission to IoT Hub.
   IoTHubClient_LL_SendEventAsync accepted message [4] for transmission to IoT Hub.
   -> 15:10:31 PUBLISH | IS_DUP: false | RETAIN: 0 | QOS: DELIVER_AT_LEAST_ONCE | TOPIC_NAME: devices/dev01/messages/events/temperatureAlert=false&%24.cid=CORE_ID&%24.mid=MSG_ID | PACKET_ID: 3 | PAYLOAD_LEN: 83
   -> 15:10:31 PUBLISH | IS_DUP: false | RETAIN: 0 | QOS: DELIVER_AT_LEAST_ONCE | TOPIC_NAME: devices/dev01/messages/events/temperatureAlert=true&%24.cid=CORE_ID&%24.mid=MSG_ID | PACKET_ID: 4 | PAYLOAD_LEN: 83
   -> 15:10:31 PUBLISH | IS_DUP: false | RETAIN: 0 | QOS: DELIVER_AT_LEAST_ONCE | TOPIC_NAME: devices/dev01/messages/events/temperatureAlert=false&%24.cid=CORE_ID&%24.mid=MSG_ID | PACKET_ID: 5 | PAYLOAD_LEN: 83
   -> 15:10:32 PUBLISH | IS_DUP: false | RETAIN: 0 | QOS: DELIVER_AT_LEAST_ONCE | TOPIC_NAME: devices/dev01/messages/events/temperatureAlert=false&%24.cid=CORE_ID&%24.mid=MSG_ID | PACKET_ID: 6 | PAYLOAD_LEN: 83
   -> 15:10:32 PUBLISH | IS_DUP: false | RETAIN: 0 | QOS: DELIVER_AT_LEAST_ONCE | TOPIC_NAME: devices/dev01/messages/events/temperatureAlert=true&%24.cid=CORE_ID&%24.mid=MSG_ID | PACKET_ID: 7 | PAYLOAD_LEN: 83
   <- 15:10:32 SUBACK | PACKET_ID: 2 | RETURN_CODE: 1
   <- 15:10:32 PUBACK | PACKET_ID: 3
   Confirmation[0] received for message tracking id = 0 with result = IOTHUB_CLIENT_CONFIRMATION_OK
   <- 15:10:32 PUBACK | PACKET_ID: 4
   Confirmation[1] received for message tracking id = 1 with result = IOTHUB_CLIENT_CONFIRMATION_OK
   <- 15:10:32 PUBACK | PACKET_ID: 5
   Confirmation[2] received for message tracking id = 2 with result = IOTHUB_CLIENT_CONFIRMATION_OK
   <- 15:10:33 PUBACK | PACKET_ID: 6
   Confirmation[3] received for message tracking id = 3 with result = IOTHUB_CLIENT_CONFIRMATION_OK
   <- 15:10:33 PUBACK | PACKET_ID: 7
   Confirmation[4] received for message tracking id = 4 with result = IOTHUB_CLIENT_CONFIRMATION_OK

   ```

## References:

1. [Azure IoT Device SDK for C](https://github.com/Azure/azure-iot-sdk-c)
2. [The Azure IoT device SDK for C | Microsoft Docs](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-device-sdk-c-intro)
3. [iothub_client_sample_mqtt - a mercurial repository | Mbed](https://developer.mbed.org/users/AzureIoTClient/code/iothub_client_sample_mqtt/)
4. [mbed OS 5 Handbook](https://docs.mbed.com/docs/mbed-os-handbook/en/latest/)
5. [mbed TLS tutorial - Knowledge Base](https://tls.mbed.org/kb/how-to/mbedtls-tutorial)


[Azure IoT Device SDK for C]: https://github.com/Azure/azure-iot-sdk-c
[mbed OS]: https://developer.mbed.org/
[wolfSSL]: https://www.wolfssl.com/wolfSSL/Products-wolfssl.html
[mbed TLS]: https://tls.mbed.org/


[![Build Status](https://travis-ci.org/maxpeng/mbedos_iothub_client_sample_mqtt.svg?branch=master)](https://travis-ci.org/maxpeng/mbedos_iothub_client_sample_mqtt)
