# PlatformIO ESP32 Webserver

This project is a simple webserver for the ESP32 microcontroller. It uses the PlatformIO build system with the [Arduino as a component](https://docs.espressif.com/projects/arduino-esp32/en/latest/esp-idf_component.html) configuration.

Debugging capabilities for ESP32-S3 are already enabled in `platformio.ini` file.

## Quickstart
```shell
# Build project
$ pio run

# Upload firmware
$ pio run --target upload

# Build specific environment
$ pio run -e esp32dev

# Upload firmware for the specific environment
$ pio run -e esp32dev --target upload

# Clean build files
$ pio run --target clean
```