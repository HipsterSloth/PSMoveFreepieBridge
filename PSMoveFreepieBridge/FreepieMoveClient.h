#pragma once
#include "../thirdparty/headers/PSMoveService/PSMoveClient_CAPI.h"
#include <chrono>
#include <windows.h>

#define FPS_REPORT_DURATION 500 // ms

enum eDeviceType
{
    _deviceTypeHMD = 1,
    _deviceTypeController = 2,
};

class FreepieMoveClient
{
public:
	FreepieMoveClient(const std::string &hostAddress);
	~FreepieMoveClient();

	int run(
        eDeviceType deviceType, 
        int32_t deviceCount, 
        int32_t deviceIDs[], 
        PSMTrackingColorType bulbColors[], 
        int32_t freepieIndicies[], 
        bool sendSensorData = true,
        int triggerAxisIndex = -1);

	void handle_client_psmove_event(PSMEventMessage::eEventType event_type);

	void handle_acquire_hmd(PSMResult resultCode, PSMHmdID trackedHmdIndex);
    void handle_acquire_controller(PSMResult resultCode, PSMControllerID trackedControllerIndex);

	bool startup();

	void update();

	void shutdown();

private:
	bool m_keepRunning = true;
	std::string m_hostAddress;
    eDeviceType m_device_type;
    PSMHeadMountedDisplay *hmd_views[4] = { nullptr, nullptr, nullptr, nullptr };
	PSMController *controller_views[4] = { nullptr, nullptr, nullptr, nullptr };
	std::chrono::milliseconds last_report_fps_timestamp;
	PSMRequestID start_stream_request_ids[4] = { -1, -1, -1, -1 };
	PSMControllerID* trackedControllerIDs;
    PSMHmdID* trackedHmdIDs;
	int32_t* trackedFreepieIndicies;
	PSMTrackingColorType* trackedBulbColors;
	int32_t trackedControllerCount = 1;
    int32_t trackedHmdCount = 1;
	bool m_sendSensorData = false;
    int32_t m_triggerAxisIndex = -1;

	void init_controller_views();
	void free_controller_views();
	void init_hmd_views();
	void free_hmd_views();
};

