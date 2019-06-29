#ifndef LeapApi_h
#define LeapApi_h
#ifdef __cplusplus
extern "C" {
#endif


#include <LeapC.h>
#include "ExampleConnection.h"

/* Client functions */
LEAP_CONNECTION* OpenConnection();
void CloseConnection();
void CloseConnectionHandle(LEAP_CONNECTION* connectionHandle);
LEAP_TRACKING_EVENT* GetFrame(); //Used in polling example
LEAP_DEVICE_INFO* GetDeviceProperties(); //Used in polling example
const char* ResultString(eLeapRS r);
int GetLeapData(LEAP_HAND* leapHand[], const uint8_t bufzize, int64_t* frameID, uint8_t* nHands);

/* State */
extern bool IsConnected;

/* Callback function pointers */
typedef void (*connection_callback)     ();
typedef void (*device_callback)         (const LEAP_DEVICE_INFO* device);
typedef void (*device_lost_callback)    ();
typedef void (*device_failure_callback) (const eLeapDeviceStatus failure_code,
	const LEAP_DEVICE failed_device);
typedef void (*policy_callback)         (const uint32_t current_policies);
typedef void (*tracking_callback)       (const LEAP_TRACKING_EVENT* tracking_event);
typedef void (*image_callback)          (const LEAP_IMAGE_COMPLETE_EVENT* image_complete_event);
typedef void (*image_error_callback)    (const LEAP_IMAGE_FRAME_REQUEST_ERROR_EVENT* image_error_event);
typedef void (*log_callback)            (const eLeapLogSeverity severity,
	const int64_t timestamp,
	const char* message);
typedef void (*config_change_callback)  (const uint32_t requestID, const bool success);
typedef void (*config_response_callback)(const uint32_t requestID, LEAP_VARIANT value);

extern void millisleep(int milliseconds);

#ifdef __cplusplus
}
#endif
#endif