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
            BindKeyActionCallback();
            BindFrameBufferResizeCallback();
            BindResizeCallback();
            BindCursorMoveCallback();
            BindMouseButtonCallback();
            BindMouseScrollCallback();
            BindWindowMoveCallback();
            BindWindowMaximizeCallback();
            BindWindowMinimizeCallback();
            BindWindowFocusCallback();
            BindWindowCloseCallback();
            BindWindowRefreshCallback();


            // Binding Event
            me_FrameBufferResize.AddListener([](auto && PH1, auto && PH2) {

                glViewport(0, 0, static_cast<GLint>(PH1), static_cast<GLint>(PH2));

            });

            me_ResizeEvent.AddListener([this](auto && PH1, auto && PH2) {

                this->m_size = {PH1, PH2};

            });

            me_WindowRefreshEvent.AddListener([this]() {



            });

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

        updateSizeLimit();

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

    Window *Window::findInstance(GLFWwindow *p_window) {
        if (g_Window_Map.find(p_window) == g_Window_Map.end()) {
            return nullptr;
        }
        return g_Window_Map[p_window];
    }

    void Window::BindFrameBufferResizeCallback() const {

        aLog("Window")->info("BindFrameBufferResizeCallback");

        glfwSetFramebufferSizeCallback(m_glfwWindow, [](GLFWwindow *p_window, GLint p_width, GLint p_height) {

            Window *Instance = findInstance(p_window);
            if(Instance) {

                Instance->me_FrameBufferResize.Invoke(p_width, p_height);
                aLog("Window")->debug("glfwSetFramebufferSizeCallback: {}x{}", p_width, p_height);

            }

        });

    }

    void Window::BindKeyActionCallback() const {

        aLog("Window")->info("BindKeyActionCallback");

        glfwSetKeyCallback(m_glfwWindow, [](GLFWwindow *p_window, GLint p_key, GLint p_scancode, GLint p_action, GLint p_mode) {

            aLog("Window")->debug("Key Action: Key: {}, ScanCode: {}, Action: {}, Mode{}", p_key, p_scancode, p_action, p_mode);

            Window *Instance = findInstance(p_window);
            if(Instance) {

                if (p_action == GLFW_PRESS) {
                    Instance->me_KeyPressedEvent.Invoke(p_key);
                } else if (p_action == GLFW_RELEASE) {
                    Instance->me_KeyReleasedEvent.Invoke(p_key);
                } else if (p_action == GLFW_REPEAT) {
                    Instance->me_KeyRepeatEvent.Invoke(p_key);
                } else {
                    throw std::runtime_error("Unknowing Key Action");
                }

            }

        });

    }

    void Window::BindResizeCallback() const {

        aLog("Window")->info("BindResizeCallback");

        glfwSetWindowSizeCallback(m_glfwWindow, [](GLFWwindow *p_window, GLint p_width, GLint p_height) {

            Window *Instance = findInstance(p_window);
            if(Instance) {
                Instance->me_ResizeEvent.Invoke(static_cast<uint32_t>(p_width), static_cast<uint32_t>(p_height));
            }

        });

    }

    void Window::BindMouseButtonCallback() const {

        aLog("Window")->info("BindResizeCallback");

        glfwSetMouseButtonCallback(m_glfwWindow, [](GLFWwindow* p_window, GLint p_button, GLint p_action, GLint p_mode) {

            aLog("Window")->debug("Mouse Button Action: Key: {}, Action: {}, Mode{}", p_button, p_action, p_mode);

            Window *Instance = findInstance(p_window);
            if(Instance) {

                if (p_action == GLFW_PRESS) {
                    Instance->me_MousePressedEvent.Invoke(p_button);
                } else if (p_action == GLFW_RELEASE) {
                    Instance->me_MouseReleasedEvent.Invoke(p_button);
                }

            }

        });

    }

    void Window::BindMouseScrollCallback() const {

        aLog("Window")->info("BindResizeCallback");

        glfwSetScrollCallback(m_glfwWindow, [](GLFWwindow *p_window, GLdouble x_offset, GLdouble y_offset) {

            aLog("Window")->debug("Scroll: {}, {}", x_offset, y_offset);

            Window *Instance = findInstance(p_window);
            if(Instance) {
                Instance->me_MouseScrollEvent.Invoke(static_cast<float_t>(x_offset), static_cast<float_t>(y_offset));
            }

        });

    }

    void Window::BindWindowMoveCallback() const {

        aLog("Window")->info("BindWindowMoveCallback");

        glfwSetWindowPosCallback(m_glfwWindow, [](GLFWwindow *p_window, GLint xPos, GLint yPos) {

            aLog("Window")->debug("Window Move: {}, {}", xPos, yPos);

            Window *Instance = findInstance(p_window);
            if(Instance) {
                Instance->me_WindowMoveEvent.Invoke(static_cast<int16_t>(xPos), static_cast<int16_t>(yPos));
            }

        });

    }

    void Window::BindCursorMoveCallback() const {

        aLog("Window")->info("BindCursorMoveCallback");

        glfwSetCursorPosCallback(m_glfwWindow, [](GLFWwindow *p_window, GLdouble xPos, GLdouble yPos) {

            aLog("Window")->debug("Cursor Move: {}, {}", xPos, yPos);

            Window *Instance = findInstance(p_window);
            if(Instance) {
                Instance->me_CursorMoveEvent.Invoke(static_cast<int16_t>(xPos), static_cast<int16_t>(yPos));
            }

        });

    }

    void Window::BindWindowMaximizeCallback() const {

        aLog("Window")->info("BindWindowMaximizeCallback");

        glfwSetWindowMaximizeCallback(m_glfwWindow, [](GLFWwindow *p_window, GLint Mode) {

            aLog("Window")->debug("Window Maximize: {}", Mode);

            Window *Instance = findInstance(p_window);
            if(Instance && Mode == 1) {
                Instance->me_WindowMaximize.Invoke();
            }

        });

    }

    void Window::BindWindowMinimizeCallback() const {
        aLog("Window")->info("BindWindowMinimizeCallback");

        // TODO: Complete it callback.
    }

    void Window::BindWindowFocusCallback() const {

        aLog("Window")->info("BindWindowFocusCallback");

        glfwSetWindowFocusCallback(m_glfwWindow, [](GLFWwindow *p_window, GLint Mode) {

            aLog("Window")->debug("Window Focus: {}", Mode);

            Window *Instance = findInstance(p_window);
            if(Instance) {
                if (Mode == 1) {
                    Instance->me_GainFocusEvent.Invoke();
                } else {
                    Instance->me_LostFocusEvent.Invoke();
                }
            }

        });

    }

    void Window::BindWindowCloseCallback() const {

        aLog("Window")->info("BindWindowCloseCallback");

        glfwSetWindowCloseCallback(m_glfwWindow, [](GLFWwindow *p_window) {

            aLog("Window")->info("Window Close");

            Window *Instance = findInstance(p_window);
            if(Instance) {
                Instance->me_WindowCloseEvent.Invoke();
            }

        });

    }

    void Window::Close() {

        me_WindowCloseEvent.Invoke();

        glfwSetWindowShouldClose(m_glfwWindow, GL_TRUE);

    }

    void Window::BindWindowRefreshCallback() const {

        aLog("Window")->info("BindWindowCloseCallback");

        glfwSetWindowRefreshCallback(m_glfwWindow, [](GLFWwindow *p_window) {

            aLog("Window")->debug("Window Refresh");

            Window *Instance = findInstance(p_window);
            if (Instance) {
                Instance->me_WindowRefreshEvent.Invoke();
            }

        });

    }


}

