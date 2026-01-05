#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <cstring>
#include <cstdio>
#include <cstdint>

struct ReadingData {
    const char* timestamp;
    const char* meterDatetime;
    double totalM3;
    const char* status;
};

struct Device {
    const char* media;
    const char* meterType;
    const char* deviceId;
    const char* unit;
    ReadingData reading;
};

struct GatewayData {
    const char* gatewayId;
    const char* date;
    const char* deviceType;
    int intervalMinutes;
    int totalReadings;
    Device device;
};

class JsonSerializer {
public:
    static bool serialize(const GatewayData& data, char* buffer, size_t maxLen) {
        buffer[0] = '\0';
        char temp[512]; 

        // Part 1: Gateway Info
        // FIX: "interval minutes" (with space) instead of underscore
        int written = snprintf(temp, sizeof(temp), 
            "[\n"
            "  {\n"
            "    \"gatewayId\": \"%s\",\n"
            "    \"date\": \"%s\",\n"
            "    \"deviceType\": \"%s\",\n"
            "    \"interval minutes\": %d,\n"  
            "    \"total_readings\": %d,\n"
            "    \"values\": {\n"
            "      \"device_count\": 1,\n"
            "      \"readings\": [\n",
            data.gatewayId, data.date, data.deviceType, 
            data.intervalMinutes, data.totalReadings
        );

        if (strlen(buffer) + written >= maxLen) return false;
        strcat(buffer, temp);

        // Part 2: Device & Reading Data
        // FIX: "meter datetime" and "total m3" (with space)
        written = snprintf(temp, sizeof(temp), 
            "        {\n"
            "          \"media\": \"%s\",\n"
            "          \"meter\": \"%s\",\n"
            "          \"deviceId\": \"%s\",\n"
            "          \"unit\": \"%s\",\n"
            "          \"data\": [\n"
            "            {\n"
            "              \"timestamp\": \"%s\",\n"
            "              \"meter datetime\": \"%s\",\n"
            "              \"total m3\": %.3f,\n"
            "              \"status\": \"%s\"\n"
            "            }\n"
            "          ]\n"
            "        }\n",
            data.device.media, data.device.meterType, data.device.deviceId, data.device.unit,
            data.device.reading.timestamp, data.device.reading.meterDatetime, 
            data.device.reading.totalM3, data.device.reading.status
        );

        if (strlen(buffer) + written >= maxLen) return false;
        strcat(buffer, temp);

        // Part 3: Closing Brackets
        written = snprintf(temp, sizeof(temp), 
            "      ]\n"
            "    }\n"
            "  }\n"
            "]"
        );

        if (strlen(buffer) + written >= maxLen) return false;
        strcat(buffer, temp);

        return true;
    }
};

#endif