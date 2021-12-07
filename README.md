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

