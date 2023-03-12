#include "Arduino.h"
#include "SerialInterface.h"
#include "PreferencesKeys.h"
#include "RestartReason.h"


SerialInterface::SerialInterface(Preferences *preferences)
: _preferences(preferences)
{
    _tokens.reserve(5);
}

void SerialInterface::update()
{
    while(Serial.available() > 0)
    {
        int val = Serial.read();
        char c = val;

        Serial.print(c);
        Serial.flush();
        if(_index < sizeof(_buffer)-1)
        {
            _buffer[_index] = c;
            ++_index;
        }

        if (val == 13)
        {
            Serial.println();
            parse();

            _index = 0;
            memset(_buffer, 0, sizeof(_buffer));
        }
    }
}

bool SerialInterface::getNext(char* token, uint8_t& index)
{
    uint8_t i = 0;

    while(index < sizeof(_buffer))
    {
        if(_buffer[index] == 32)
        {
            ++index;
            return i > 0;
        }
        if(_buffer[index] == 13)
        {
            return i > 0;
        }
        else
        {
            token[i] = _buffer[index];
            ++i;
            ++index;
        }
    }

    return false;
}

void SerialInterface::parse()
{
    String command;
    _tokens.clear();

    char str[sizeof(_buffer)];
    memset(str, 0, sizeof(str));

    uint8_t index = 0;

    while(getNext(str, index))
    {
        _tokens.push_back(str);
        memset(str, 0, sizeof(str));
    }

    if(!isAuthenticated())
    {
        Serial.println(F("Denied: not authenticated."));
        return;
    }

    _authenticatedTs = millis() + 3 * 60 * 1000;

    // prevent unknown command output
    if(_tokens.size() >= 1 && _tokens[0] == "auth")
    {
        return;
    }

    if(_tokens.size() >= 1 && _tokens[0] == "restart")
    {
        Serial.println(F("Restarting ESP"));
        delay(200);
        restartEsp(RestartReason::RequestedViaSerialInterface);
    }
    if(_tokens.size() >= 1 && _tokens[0] == "serialoff")
    {
        _preferences->putUChar(preference_serial_interface_enabled, 1);;
    }
    if(_tokens.size() >= 1 && _tokens[0] == "clearall")
    {
        _preferences->clear();
        Serial.println(F("Cleared all settings"));
    }
    else if(_tokens.size() >= 3 && _tokens[0] == "nwhw")
    {
        _preferences->putInt(preference_network_hardware, _tokens[1].toInt());
        _preferences->putInt(preference_network_hardware_gpio, _tokens[2].toInt());
    }
    else if(_tokens.size() >= 3 && _tokens[0] == "wifi")
    {
        _preferences->putString(preference_network_preload_ssid, _tokens[1]);
        _preferences->putString(preference_network_preload_psk, _tokens[2]);
    }
    else if(_tokens.size() >= 2 && _tokens[0] == "dhcp")
    {
        _preferences->putBool(preference_ip_dhcp_enabled, _tokens[1].toInt() > 0);
    }
    else if(_tokens.size() >= 3 && _tokens[0] == "ip")
    {
        _preferences->putString(preference_ip_address, _tokens[1]);
        _preferences->putString(preference_ip_subnet, _tokens[2]);
    }
    else if(_tokens.size() >= 2 && _tokens[0] == "gw")
    {
        _preferences->putString(preference_ip_gateway, _tokens[1]);
    }
    else if(_tokens.size() >= 2 && _tokens[0] == "dns")
    {
        _preferences->putString(preference_ip_dns_server, _tokens[1]);
    }
    else if(_tokens.size() >= 3 && _tokens[0] == "mqttbroker")
    {
        _preferences->putString(preference_mqtt_broker, _tokens[1]);
        _preferences->putInt(preference_mqtt_broker_port, _tokens[2].toInt());
    }
    else if(_tokens.size() >= 3 && _tokens[0] == "cred")
    {
        _preferences->putString(preference_cred_user, _tokens[1]);
        _preferences->putString(preference_cred_password, _tokens[2]);
    }
    else if(_tokens.size() >= 3 && _tokens[0] == "mqttauth")
    {
        _preferences->putString(preference_mqtt_user, _tokens[1]);
        _preferences->putString(preference_mqtt_password, _tokens[2]);
    }
    else if(_tokens.size() >= 3 && _tokens[0] == "nukienable")
    {
        _preferences->putBool(preference_lock_enabled, _tokens[1].toInt() > 0);
        _preferences->putBool(preference_opener_enabled, _tokens[2].toInt() > 0);
    }
    else if(_tokens.size() >= 3 && _tokens[0] == "nukipath")
    {
        _preferences->putString(preference_mqtt_lock_path, _tokens[1]);
        _preferences->putString(preference_mqtt_opener_path, _tokens[2]);
    }
    else
    {
        Serial.println(F("Unknown command or invalid parameters."));
    }
}


bool SerialInterface::isAuthenticated()
{
    if(millis() < _authenticatedTs)
    {
        return true;
    }
    if(_preferences->getString(preference_cred_user) == "" && _preferences->getString(preference_cred_password) == "")
    {
        return true;
    }
    if(_tokens.size() >= 1 && _tokens[0] == "auth")
    {
        if(_lastAuthTs > 0 && millis() < _lastAuthTs)
        {
            Serial.println(F("Authentication retry too fast."));
            return false;
        }

        if (_tokens.size() >= 3 && _preferences->getString(preference_cred_user) == _tokens[1] && _preferences->getString(preference_cred_password) == _tokens[2])
        {
            Serial.println(F("Authentication successful"));
            _authenticatedTs = millis() + 3 * 60 * 1000;
            return true;
        }
        else
        {
            Serial.println(F("Authentication failed"));
            _lastAuthTs = _lastAuthTs + 3000;
        }
    }
    return false;
}
