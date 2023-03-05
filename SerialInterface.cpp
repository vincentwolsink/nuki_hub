#include "Arduino.h"
#include "SerialInterface.h"

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
            char str[sizeof(_buffer)];
            memset(str, 0, sizeof(str));

            uint8_t index = 0;

            while(getNext(str, index))
            {
                Serial.println(str);
                memset(str, 0, sizeof(str));
            }

            Serial.println();

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
