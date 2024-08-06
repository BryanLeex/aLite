//
// Created by Bryan on 06/08/2024.
//

#include "Context.h"

namespace Context {


    Context::Context() {

        m_device = std::make_unique<Device::Device>();
        m_window = std::make_unique<Window::Window>();

    }

    Context::~Context() {

        aLog("Context")->info("Context Destroy.");

    }
} // Context