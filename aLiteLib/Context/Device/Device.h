//
// Created by Bryan on 06/08/2024.
//

#ifndef ALITE_DEVICE_H
#define ALITE_DEVICE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Settings.h"

#define aLog(a_name) spdlog::get(a_name)

namespace Context::Device {

    class Device {

    public:

        Device();
        ~Device();
        explicit Device(DeviceSetting &p_deviceSetting);


    private:

        DeviceSetting   m_setting;

        bool            m_isAlive = false;

        void initDevice();

        void initGLFW();

        void initLogger();

    };

}

// Context

#endif //ALITE_DEVICE_H
