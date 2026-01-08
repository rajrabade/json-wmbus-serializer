#include <stdio.h>
#include "../include/serializer.h"

int main(void) {
    char json_buffer[1024];

    GatewayData gw = {
        .gatewayId = "gateway_1234",
        .date = "1970-01-01",
        .deviceType = "stromleser",
        .interval_minutes = 15,
        .total_readings = 1,
        .device_count = 1
    };

    gw.devices[0].media = "water";
    gw.devices[0].meter = "waterstarm";
    gw.devices[0].deviceId = "stromleser_50898527";
    gw.devices[0].unit = "m3";
    gw.devices[0].data_count = 1;

    gw.devices[0].data[0] = (DataPoint){
        .timestamp = "1970-01-01 00:00",
        .meter_datetime = "1970-01-01 00:00",
        .total_m3 = 107.752f,
        .status = "OK"
    };

    SerializeResult res = serialize_to_json(&gw, json_buffer, sizeof(json_buffer));

    if (res == SERIALIZE_OK) {
        printf("%s\n", json_buffer);
        return 0;
    } else {
        fprintf(stderr, "Serialization error: %d\n", res);
        return 2;
    }
}
