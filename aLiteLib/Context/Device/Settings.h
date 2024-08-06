//
// Created by Bryan on 06/08/2024.
//

#ifndef ALITE_SETTINGS_H
#define ALITE_SETTINGS_H

#include <vector>
#include <string>

#include <spdlog/spdlog.h>

namespace Context::Device {

    struct DeviceSetting {

        std::vector<std::string> m_LoggerName = {
                "Main",
                "Device",
                "Window",
                "Context"
        };

        spdlog::level::level_enum   DefaultLevel = spdlog::level::info;

        std::string                 DefaultPattern = "[%H:%M:%S.%f %z] [%n] [%^%l%$] [thread %t] %v";

        uint8_t                     GLFWMajorVersion = 3;
        uint8_t                     GLFWMinorVersion = 3;

        uint16_t                    samples = 4;

    };

}



#endif //ALITE_SETTINGS_H
