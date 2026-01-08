#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <stddef.h>

#define MAX_DEVICES 4
#define MAX_DATAPOINTS 4

typedef struct {
    const char *timestamp;       // format: "YYYY-MM-DD hh:mm"
    const char *meter_datetime;  // format: "YYYY-MM-DD hh:mm"
    float total_m3;              // numeric, not string
    const char *status;          // e.g. "OK"
} DataPoint;

typedef struct {
    const char *media;           // e.g. "water"
    const char *meter;           // e.g. "waterstarm"
    const char *deviceId;        // e.g. "stromleser_50898527"
    const char *unit;            // e.g. "m3"
    DataPoint data[MAX_DATAPOINTS];
    int data_count;
} DeviceReading;

typedef struct {
    const char *gatewayId;       // e.g. "gateway_1234"
    const char *date;            // format: "YYYY-MM-DD"
    const char *deviceType;      // e.g. "stromleser"
    int interval_minutes;
    int total_readings;

    int device_count;
    DeviceReading devices[MAX_DEVICES];
} GatewayData;

typedef enum {
    SERIALIZE_OK = 0,
    SERIALIZE_BUFFER_TOO_SMALL,
    SERIALIZE_INVALID_INPUT
} SerializeResult;

// Serialize input structure into the caller-provided output buffer.
// Returns SERIALIZE_OK on success, or an explicit error code.
SerializeResult serialize_to_json(
    const GatewayData *input,
    char *output,
    size_t output_size
);

#endif // SERIALIZER_H
