#include <iostream>
#include "JsonSerializer.h"

int main() {
    ReadingData myReading = {
        "2025-01-05 10:00", 
        "2025-01-05 10:00", 
        107.752, 
        "OK"
    };

    Device myDevice = {
        "water", 
        "water_meter_v1", 
        "stromleser_50898527", 
        "m3", 
        myReading
    };

    GatewayData myGateway = {
        "gateway_1234", 
        "2025-01-05", 
        "stromleser", 
        15, 
        1, 
        myDevice
    };

    char jsonBuffer[2048]; 

    if (JsonSerializer::serialize(myGateway, jsonBuffer, sizeof(jsonBuffer))) {
        std::cout << jsonBuffer << std::endl;
    } else {
        std::cerr << "Error: Buffer too small!" << std::endl;
    }

    return 0;
}