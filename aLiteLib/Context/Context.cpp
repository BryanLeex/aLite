//
// Created by Bryan on 06/08/2024.
//

#include "Context.h"

namespace Context {


    Context::Context() {

        m_device = std::make_unique<Device::Device>();
        m_window = std::make_unique<Window::Window>();
        m_camera = std::make_unique<Camera::Camera>(m_window.get());

    }

    Context::~Context() {

        aLog("Context")->info("Context Destroy.");

    }

    void Context::Tick() {

        m_camera->Tick();

    }

} // Context