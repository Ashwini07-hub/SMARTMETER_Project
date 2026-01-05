# Embedded JSON Serializer Library

## 1. Project Overview
This project implements a lightweight, embedded-friendly C++ library to serialize meter data into a specific JSON format. It is designed to be transport-agnostic and does not rely on any external JSON parsing libraries, making it suitable for resource-constrained microcontrollers like STM32.

## 2. Chosen Platform & Language
* **Language:** C++
    * *Justification:* C++ was chosen for its strong type safety and Object-Oriented features (encapsulation), which helps in maintaining a clean architecture while keeping memory usage low.
* **Platform:** STM32 (STM32CubeIDE preferred) / Generic C++
    * *Justification:* The code is written in standard C++ and is platform-agnostic. It can be easily integrated into STM32 HAL projects or ESP-IDF.

## 3. Project Structure
The project follows a modular structure:
```text
/
├── JsonSerializer.h   # Core library logic (Header-only)
├── main.cpp           # Demo application to generate sample data
└── README.md          # Project documentation
```
## 4. Build and Run Instructions
Using G++ (Terminal/Command Line)
Open a terminal in the project folder.
Compile the code: g++ main.cpp -o app
Run the application: ./app (or app.exe on Windows)
Using STM32 / Arduino
Copy JsonSerializer.h into your project's src or include folder.
Include the header: #include "JsonSerializer.h"
Call JsonSerializer::serialize(...) in your main loop.

## 5. Library API Description
The library exposes a single static method:
static bool serialize(const GatewayData& data, char* buffer, size_t maxLen);
Parameters:
data: Struct containing the populated meter/gateway data.
buffer: Pointer to the character array where JSON will be written.
maxLen: Maximum size of the buffer to prevent overflow.
Return Value: Returns true if successful, false if the buffer is too small.

## 6. Example JSON Output
The library generates the following exact output structure:
[
  {
    "gatewayId": "gateway_1234",
    "date": "2025-01-05",
    "deviceType": "stromleser",
    "interval minutes": 15,
    "total_readings": 1,
    "values": {
      "device_count": 1,
      "readings": [
        {
          "media": "water",
          "meter": "water_meter_v1",
          "deviceId": "stromleser_50898527",
          "unit": "m3",
          "data": [
            {
              "timestamp": "2025-01-05 10:00",
              "meter datetime": "2025-01-05 10:00",
              "total m3": 107.752,
              "status": "OK"
            }
          ]
        }
      ]
    }
  }
]
## 7. Design Decisions & Assumptions
No Dynamic Memory: The library uses stack allocation and caller-provided buffers. No malloc or new is used inside the serialization logic to avoid heap fragmentation.
Safety: snprintf is used strictly to prevent buffer overflows.
Data Model: C++ structs are used to mimic the data hierarchy (Gateway -> Device -> Reading).

## 8. Possible Extensions
Multiple Devices: Currently, the struct supports one device per gateway. This can be extended to use std::vector or arrays for multiple devices.
Checksum: A CRC field could be added to the JSON for data integrity verification during transmission.

