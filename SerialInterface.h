#pragma once

class SerialInterface
{
public:
    void update();

private:
    bool getNext(char* token, uint8_t& index);

    char _buffer[100] = {0};
    uint8_t _index = 0;
    bool _authenticatedTs = 0;
};