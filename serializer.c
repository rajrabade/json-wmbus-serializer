#include "../include/serializer.h"
#include <stdio.h>

SerializeResult serialize_to_json(
    const GatewayData *in,
    char *out,
    size_t size
) {
    if (!in || !out || size == 0)
        return SERIALIZE_INVALID_INPUT;

    int written = 0;
    int remaining = (int)size;
    int ret;

    // Start outer array + gateway object
    ret = snprintf(out + written, remaining,
        "[{\"gatewayId\":\"%s\",\"date\":\"%s\",\"deviceType\":\"%s\","
        "\"interval_minutes\":%d,\"total_readings\":%d,\"values\":{\"device_count\":%d,\"readings\":[",
        in->gatewayId ? in->gatewayId : "",
        in->date ? in->date : "",
        in->deviceType ? in->deviceType : "",
        in->interval_minutes,
        in->total_readings,
        in->device_count
    );

    if (ret < 0) return SERIALIZE_INVALID_INPUT;
    written += ret; remaining = (int)size - written;
    if (remaining <= 0) return SERIALIZE_BUFFER_TOO_SMALL;

    for (int i = 0; i < in->device_count; i++) {
        const DeviceReading *d = &in->devices[i];

        ret = snprintf(out + written, remaining,
            "%s{\"media\":\"%s\",\"meter\":\"%s\",\"deviceId\":\"%s\",\"unit\":\"%s\",\"data\":[",
            (i > 0) ? "," : "",
            d->media ? d->media : "",
            d->meter ? d->meter : "",
            d->deviceId ? d->deviceId : "",
            d->unit ? d->unit : ""
        );

        if (ret < 0) return SERIALIZE_INVALID_INPUT;
        written += ret; remaining = (int)size - written;
        if (remaining <= 0) return SERIALIZE_BUFFER_TOO_SMALL;

        for (int j = 0; j < d->data_count; j++) {
            const DataPoint *p = &d->data[j];

            ret = snprintf(out + written, remaining,
                "%s{\"timestamp\":\"%s\",\"meter_datetime\":\"%s\",\"total_m3\":%.3f,\"status\":\"%s\"}",
                (j > 0) ? "," : "",
                p->timestamp ? p->timestamp : "",
                p->meter_datetime ? p->meter_datetime : "",
                p->total_m3,
                p->status ? p->status : ""
            );

            if (ret < 0) return SERIALIZE_INVALID_INPUT;
            written += ret; remaining = (int)size - written;
            if (remaining <= 0) return SERIALIZE_BUFFER_TOO_SMALL;
        }

        // close data array and device object
        ret = snprintf(out + written, remaining, "]}");
        if (ret < 0) return SERIALIZE_INVALID_INPUT;
        written += ret; remaining = (int)size - written;
        if (remaining <= 0) return SERIALIZE_BUFFER_TOO_SMALL;
    }

    // close readings array, values, object and outer array
    ret = snprintf(out + written, remaining, "]}}]");
    if (ret < 0) return SERIALIZE_INVALID_INPUT;
    written += ret; remaining = (int)size - written;
    if (written >= (int)size) return SERIALIZE_BUFFER_TOO_SMALL;

    return SERIALIZE_OK;
}
