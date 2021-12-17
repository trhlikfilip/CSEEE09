This is the repositary of CSEEE09 team for the UCL engineering challenge 2.
All 3 subsystems have here a dedicated codes, which handle their fanctioning through Arduiono UNO (thus they all have .ino file format)

Apart from this, the protocols and the Arduiono-ESP32 & ESP32-ThingsBoard is defined in the 2 folders (uno_slave, esp32_master)

To use, create a file called keys.h in the esp32_master directory, with this content

```c
#ifndef KEYS_H
#define KEYS_H

// WiFi control for ESP32
//wpa2 library for connections to Enterprise networks
#define EAP_IDENTITY "<UCL EMAIL>"
#define EAP_PASSWORD "<UCL PASSWORD>"

// See https://thingsboard.io/docs/getting-started-guides/helloworld/
#define TOKEN               "<THINGSBOARD TOKEN>"
#define THINGSBOARD_SERVER  "<THINGSBOARD SERVER>"

#endif
```

Replace the content in the angled brackets with the correct information.

