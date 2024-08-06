//
// Created by Bryan on 06/08/2024.
//

#include "Window.h"

namespace Context::Window {

    std::unordered_map<GLFWwindow*, Window*> Window::g_Window_Map;

    Window::Window() {

        m_windowSetting = WindowSetting();

        initWindow();

    }

    Window::Window(WindowSetting &p_windowSetting) {

        m_windowSetting = p_windowSetting;

        initWindow();

    }

    Window::~Window() {

        aLog("Window")->info("Window Destroy.");

    }

    void Window::initWindow() {

        m_title = m_windowSetting.m_title;
        m_refreshRate = m_windowSetting.m_refreshRate;
        m_fullScreen = m_windowSetting.m_fullscreen;
        m_size = {m_windowSetting.m_width, m_windowSetting.m_height};
        m_minSize = {m_windowSetting.m_minWidth, m_windowSetting.m_minHeight};
        m_maxSize = {m_windowSetting.m_maxWidth, m_windowSetting.m_maxHeight};

        try {

            // Create Window
            createWindow();
            aLog("Window")->info("Create Window.");

            // Initialize GLAD
            initGLAD();
            aLog("Window")->info("initGLAD Finish.");


            // Binding Callback

        } catch (std::exception &exception) {
            aLog("Window")->critical(exception.what());
        }


    }

    void Window::createWindow() {

        GLFWmonitor* p_monitor = nullptr;

        if (m_fullScreen) {

            p_monitor = glfwGetPrimaryMonitor();

        }

        glfwWindowHint(GLFW_RESIZABLE,		m_windowSetting.m_resizeable);
        glfwWindowHint(GLFW_FOCUSED,		m_windowSetting.m_focused);
        glfwWindowHint(GLFW_MAXIMIZED,		m_windowSetting.m_maximized);
        glfwWindowHint(GLFW_VISIBLE,		m_windowSetting.m_visible);
        glfwWindowHint(GLFW_REFRESH_RATE,	m_windowSetting.m_refreshRate);
        glfwWindowHint(GLFW_SAMPLES,		m_windowSetting.m_samples);

        m_glfwWindow = glfwCreateWindow(static_cast<GLint>(m_size.first), static_cast<GLint>(m_size.second),
                                        m_title.c_str(), p_monitor, nullptr);

        if (m_glfwWindow == nullptr) {
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(m_glfwWindow);

        m_position = getPosition();

        g_Window_Map.insert({m_glfwWindow, this});

    }

    void Window::updateSizeLimit() {

        glfwSetWindowSizeLimits(m_glfwWindow,
                static_cast<GLint>(m_minSize.first),
                static_cast<GLint>(m_minSize.second),
                static_cast<GLint>(m_maxSize.first),
                static_cast<GLint>(m_maxSize.second));

    }

    std::pair<int16_t, int16_t> Window::getPosition() {

        GLint x, y;
        glfwGetWindowPos(m_glfwWindow, &x, &y);

        return {static_cast<int16_t>(x), static_cast<int16_t>(y)};
    }

    bool Window::isWindowRunning() {
        return !glfwWindowShouldClose(m_glfwWindow);
    }

    void Window::SwapBuffer() {
        glfwSwapBuffers(m_glfwWindow);
    }

    void Window::initGLAD() {

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD.");
        }

    }


}

