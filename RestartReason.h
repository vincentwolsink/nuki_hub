#pragma once

enum class RestartReason
{
    RequestedViaMqtt,
    BLEBeaconWatchdog,
    RestartOnDisconnectWatchdog,
    RestartIntervalWatchdog,
    NetworkTimeoutWatchdog,
    WifiInitFailed,
    ReconfigureWifi,
    NetworkDeviceCriticalFailure,
    ConfigurationUpdated,
    RestartTimer,
    OTATimeout,
    DeviceUnpaired,
};

#define RESTART_REASON_VALID_DETECT 0xa00ab00bc00bd00d;

extern int restartReason;
extern uint64_t restartReasonValid;

inline static void restartEsp(RestartReason reason)
{
    restartReason = (int)reason;
    restartReasonValid = RESTART_REASON_VALID_DETECT;
    ESP.restart();
}

inline static String getRestartReason()
{
    uint64_t cmp = RESTART_REASON_VALID_DETECT;
    if(restartReasonValid != cmp)
    {
        return "UnknownNoRestartRegistered";
    }

    switch((RestartReason)restartReason)
    {
        case RestartReason::RequestedViaMqtt:
            return "RequestedViaMqtt";
        case RestartReason::BLEBeaconWatchdog:
            return "BLEBeaconWatchdog";
        case RestartReason::RestartOnDisconnectWatchdog:
            return "RestartOnDisconnectWatchdog";
        case RestartReason::RestartIntervalWatchdog:
            return "RestartIntervalWatchdog";
        case RestartReason::NetworkTimeoutWatchdog:
            return "NetworkTimeoutWatchdog";
        case RestartReason::WifiInitFailed:
            return "WifiInitFailed";
        case RestartReason::ReconfigureWifi:
            return "ReconfigureWifi";
        case RestartReason::NetworkDeviceCriticalFailure:
            return "NetworkDeviceCriticalFailure";
        case RestartReason::ConfigurationUpdated:
            return "ConfigurationUpdated";
        case RestartReason::RestartTimer:
            return "RestartTimer";
        case RestartReason::OTATimeout:
            return "OTATimeout";
        case RestartReason::DeviceUnpaired:
            return "DeviceUnpaired";
        default:
            return "Unknown: " + restartReason;
    }
}

inline static String getEspRestartReason()
{
    esp_reset_reason_t reason = esp_reset_reason();
    switch(reason)
    {
        case esp_reset_reason_t::ESP_RST_UNKNOWN:
            return "ESP_RST_UNKNOWN: Reset reason can not be determined.";
        case esp_reset_reason_t::ESP_RST_POWERON:
            return "ESP_RST_POWERON: Reset due to power-on event.";
        case esp_reset_reason_t::ESP_RST_EXT:
            return "ESP_RST_EXT: Reset by external pin";
        case esp_reset_reason_t::ESP_RST_SW:
            return "ESP_RST_SW: Software reset via esp_restart.";
        case esp_reset_reason_t::ESP_RST_PANIC:
            return "ESP_RST_PANIC: Software reset due to exception/panic.";
        case esp_reset_reason_t::ESP_RST_INT_WDT:
            return "ESP_RST_INT_WDT: Reset (software or hardware) due to interrupt watchdog";
        case esp_reset_reason_t::ESP_RST_TASK_WDT:
            return "ESP_RST_TASK_WDT: Reset due to task watchdog.";
        case esp_reset_reason_t::ESP_RST_WDT:
            return "ESP_RST_WDT: Reset due to other watchdogs.";
        case esp_reset_reason_t::ESP_RST_DEEPSLEEP:
            return "ESP_RST_DEEPSLEEP: Reset after exiting deep sleep mode.";
        case esp_reset_reason_t::ESP_RST_BROWNOUT:
            return "ESP_RST_BROWNOUT: Brownout reset (software or hardware)";
        case esp_reset_reason_t::ESP_RST_SDIO:
            return "ESP_RST_SDIO: Reset over SDIO.";
        default:
            return "Unknown: " + (int)reason;
    }
}