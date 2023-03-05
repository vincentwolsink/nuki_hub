#pragma once

#include <Preferences.h>
#include <vector>

class SerialInterface
{
public:
    explicit SerialInterface(Preferences* preferences);

    void update();

private:
    void parse();
    bool isAuthenticated();

    bool getNext(char* token, uint8_t& index);

    char _buffer[100] = {0};
    uint8_t _index = 0;
    unsigned long _authenticatedTs = 0;

    std::vector<String> _tokens;

    Preferences* _preferences = nullptr;
};