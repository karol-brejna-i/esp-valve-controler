


## Configuration

In order for the project to build and run properly, some configuration information needs to be provided.

### WiFi setup
The code connect to an existing WiFi network. Network name and password can be delivered in a few ways:


1. Environment variable:
```
export ADDITIONAL_BUILD_FLAGS='-DWIFI_SSID=\"My ssid name\" -DWIFI_PASS=\"My password\"'
```

(For my WSL setup I needed to add the line to .bashrc, because the IDE didn't recognize the variables.)

2. Build flag in platform.ini, for example:
```
[env]
build_flags =
  -DWIFI_SSID="\"My ssid name\""
  -DWIFI_PASS="\"My password\""
  ...
```

3. Explicit definition in the code (main.cpp):

Remove:
```
#ifndef WIFI_SSID
#error wifi not defined
#endif
```
Add:
```
#ifndef WIFI_SSID
#define WIFI_SSID "My ssid name"
#define WIFI_PASS "My password"
#endif
```

## Communication
In my environment, I use port `COM10` (that uses CP210x driver for my ESP devices). The equivalent port for WSL is `/dev/ttyS10`.
(Please, take a look at https://www.instructables.com/id/ESP32-Development-on-Windows-Subsystem-for-Linux/ for more details, if needed.)


Set up the port for firmware uploads and serial monitor according to your needs in `platform.ini`, for example:
```
[env]
; upload_port = COM10
; monitor_port = COM10
upload_port = /dev/ttyS10
monitor_port = /dev/ttyS10
monitor_speed = 115200
```

## Build versioning
The project uses PlatformIO mechanisms (scirpts) to automatically create `./include/build.h` file which contains code version number and build number and timestamp.

You can set required version number in `./versioning_version` file (project's root directory). Build number is generated based on the value stored in `./versioning_build` (if the file doesn't exist's, it is created automatically with build number 1).

This way you have better control over builds/testing.

build.h contains the following macro definitions:
* `VERSION` - version number (preffered format 'x.y.z')
* `BUILD_TIMESTAMP` - (i.e. "2020-10-03 19:32:34")
* `BUILD_NUMBER` - consecutive build numer (int)
* `BUILD_VERSION` - in for of \<version\>.\<short build timestamp\>.\<build number\> (short build timestamp is YYMMDD) --  for example "0.0.0.201003.1"
* `VERSION_JSON` - useful when returning the version through REST API -- for example {\"version\": \"0.0.0\", \"buildVersion\": \"0.0.0.201003.1\", \"timestamp\": \"2020-10-03 19:32:34\"}

# Roadmap

## Implemented features
* Connect to given WiFi
* Prototype web ui to press/release remote control button
* Automatically turn off the controler after given timeout (not drain bateries in case of a bug)

## To be implemented
* Add responsive web ui
* Add websocket/server side events communication -- inform the clients about state changes
