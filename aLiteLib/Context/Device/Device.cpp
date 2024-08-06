//
// Created by Bryan on 06/08/2024.
//

#include "Device.h"

namespace Context::Device {

    Device::Device(DeviceSetting &p_deviceSetting) {

        m_setting = p_deviceSetting;

        this->initDevice();

    }

    Device::Device() {

        m_setting = DeviceSetting();

        this->initDevice();

    }

    Device::~Device() {

        aLog("Device")->info("Device Destroy.");

        if (m_isAlive) {

            glfwTerminate();

        }

    }

    void Device::initDevice() {

        try {

            initLogger();
            aLog("Device")->info("initLogger Finish.");

            initGLFW();
            aLog("Device")->info("initGLFW Finish.");

        } catch (std::exception &exception) {
            aLog("Device")->critical(exception.what());
        }

    }

    void Device::initLogger() {

        for (const auto &a_name : m_setting.m_LoggerName) {

            if (spdlog::get(a_name) != nullptr) continue;

            auto Logger = spdlog::stdout_color_mt(a_name);

            Logger->set_pattern(m_setting.DefaultPattern);
            Logger->set_level(m_setting.DefaultLevel);

            Logger->info("Logger ({}) Initialized.", a_name);

        }

    }



    void Device::initGLFW() {

        if (!glfwInit()) {
            glfwTerminate();
            throw std::runtime_error("Can Not Initialize glfw.");
        }

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_setting.GLFWMinorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_setting.GLFWMajorVersion);

        glfwWindowHint(GLFW_SAMPLES, m_setting.samples);

        m_isAlive = true;

    }




}
// Context