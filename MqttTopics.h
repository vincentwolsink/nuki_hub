#pragma once

#define mqtt_topic_battery_level "/battery/level"
#define mqtt_topic_battery_critical "/battery/critical"
#define mqtt_topic_battery_charging "/battery/charging"
#define mqtt_topic_battery_voltage "/battery/voltage"
#define mqtt_topic_battery_drain "/battery/drain"
#define mqtt_topic_battery_max_turn_current "/battery/maxTurnCurrent"
#define mqtt_topic_battery_lock_distance "/battery/lockDistance"
#define mqtt_topic_battery_keypad_critical "/battery/keypadCritical"

#define mqtt_topic_lock_state "/lock/state"
#define mqtt_topic_lock_json "/lock/json"
#define mqtt_topic_query_config "/lock/query/config"
#define mqtt_topic_query_lockstate "/lock/query/lockstate"
#define mqtt_topic_query_keypad "/lock/query/keypad"
#define mqtt_topic_query_battery "/lock/query/battery"
#define mqtt_topic_query_lockstate_command_result "/lock/query/lockstateCommandResult"
#define mqtt_topic_lock_binary_state "/lock/binaryState"
#define mqtt_topic_lock_trigger "/lock/trigger"
#define mqtt_topic_lock_last_lock_action "/lock/lastLockAction"
#define mqtt_topic_lock_log "/lock/log"
#define mqtt_topic_lock_auth_id "/lock/authorizationId"
#define mqtt_topic_lock_auth_name "/lock/authorizationName"
#define mqtt_topic_lock_completionStatus "/lock/completionStatus"
#define mqtt_topic_lock_action_command_result "/lock/commandResult"
#define mqtt_topic_lock_door_sensor_state "/lock/doorSensorState"
#define mqtt_topic_lock_action "/lock/action"
#define mqtt_topic_lock_rssi "/lock/rssi"
#define mqtt_topic_lock_address "/lock/address"
#define mqtt_topic_lock_retry "/lock/retry"

#define mqtt_topic_config_button_enabled "/configuration/buttonEnabled"
#define mqtt_topic_config_led_enabled "/configuration/ledEnabled"
#define mqtt_topic_config_led_brightness "/configuration/ledBrightness"
#define mqtt_topic_config_auto_unlock "/configuration/autoUnlock"
#define mqtt_topic_config_auto_lock "/configuration/autoLock"
#define mqtt_topic_config_single_lock "/configuration/singleLock"
#define mqtt_topic_config_sound_level "/configuration/soundLevel"
#define mqtt_topic_config_last_action_authorization "/configuration/lastActionAuthorizaton"

#define mqtt_topic_info_hardware_version "/info/hardwareVersion"
#define mqtt_topic_info_firmware_version "/info/firmwareVersion"
#define mqtt_topic_info_nuki_hub_version "/info/nukiHubVersion"
#define mqtt_topic_info_nuki_hub_latest "/info/nukiHubLatest"
#define mqtt_topic_info_nuki_hub_ip "/info/nukiHubIp"

#define mqtt_topic_keypad "/keypad"
#define mqtt_topic_keypad_command_action "/keypad/command/action"
#define mqtt_topic_keypad_command_id "/keypad/command/id"
#define mqtt_topic_keypad_command_name "/keypad/command/name"
#define mqtt_topic_keypad_command_code "/keypad/command/code"
#define mqtt_topic_keypad_command_enabled "/keypad/command/enabled"
#define mqtt_topic_keypad_command_result "/keypad/command/commandResult"
#define mqtt_topic_keypad_json "/keypad/json"

#define mqtt_topic_presence "/presence/devices"

#define mqtt_topic_reset "/maintenance/reset"
#define mqtt_topic_uptime "/maintenance/uptime"
#define mqtt_topic_wifi_rssi "/maintenance/wifiRssi"
#define mqtt_topic_log "/maintenance/log"
#define mqtt_topic_freeheap "/maintenance/freeHeap"
#define mqtt_topic_restart_reason_fw "/maintenance/restartReasonNukiHub"
#define mqtt_topic_restart_reason_esp "/maintenance/restartReasonNukiEsp"
#define mqtt_topic_mqtt_connection_state "/maintenance/mqttConnectionState"
#define mqtt_topic_network_device "/maintenance/networkDevice"

#define mqtt_topic_gpio_prefix "/gpio"
#define mqtt_topic_gpio_pin "/pin_"
#define mqtt_topic_gpio_role "/role"
#define mqtt_topic_gpio_state "/state"
