//
// Created by Bryan on 06/08/2024.
//

#ifndef ALITE_CONTEXT_H
#define ALITE_CONTEXT_H

#include <memory>

#include "Utils/Logger.h"

#include "Context/Device/Device.h"
#include "Context/Window/Window.h"
#include "Context/Camera/Camera.h"

namespace Context {

    class Context {

    public:
        Context();
        ~Context();

        void Tick();

        Device::Device* GetDevice() { return m_device.get(); }

        Window::Window* GetWindow() { return m_window.get(); }

        Camera::Camera* GetCamera() { return m_camera.get(); }

    private:

        std::unique_ptr<Device::Device> m_device;
        std::unique_ptr<Window::Window> m_window;
        std::unique_ptr<Camera::Camera> m_camera;

    };

} // Context

#endif //ALITE_CONTEXT_H
