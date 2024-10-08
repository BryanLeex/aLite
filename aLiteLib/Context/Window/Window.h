//
// Created by Bryan on 06/08/2024.
//

#ifndef ALITE_WINDOW_H
#define ALITE_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <unordered_map>

#include <stdexcept>

#include "Settings.h"

#include "Utils/Logger.h"

#include "Context/Event/Event.h"

namespace Context::Window {

    class Window {

    public:

        // Input Device Event
        Event::Event<int32_t>               me_KeyPressedEvent;
        Event::Event<int32_t>               me_KeyReleasedEvent;
        Event::Event<int32_t>               me_KeyRepeatEvent;

        Event::Event<int32_t>               me_MousePressedEvent;
        Event::Event<int32_t>               me_MouseReleasedEvent;
        Event::Event<float_t, float_t>      me_MouseScrollEvent;

        // Window Event
        Event::Event<uint32_t, uint32_t>    me_FrameBufferResize;
        Event::Event<uint32_t, uint32_t>    me_ResizeEvent;

        Event::Event<>                      me_WindowRefreshEvent;

        Event::Event<int16_t, int16_t>      me_WindowMoveEvent;
        Event::Event<int16_t, int16_t>      me_CursorMoveEvent;

        Event::Event<>                      me_WindowMaximize;
        Event::Event<>                      me_WindowMinimize;

        Event::Event<>                      me_GainFocusEvent;
        Event::Event<>                      me_LostFocusEvent;

        Event::Event<>                      me_WindowCloseEvent;

        Window();
        explicit Window(WindowSetting &p_windowSetting);

        ~Window();

        static Window* findInstance(GLFWwindow* p_window);

        std::pair<int16_t, int16_t>     getPosition();

        virtual void                    Tick();

        void                            SwapBuffer();

        bool                            isWindowRunning();

        void                            Close();

    private:

        inline void BindFrameBufferResizeCallback() const ;
        inline void BindResizeCallback() const ;
        inline void BindKeyActionCallback() const ;
        inline void BindMouseButtonCallback() const ;
        inline void BindMouseScrollCallback() const ;
        inline void BindWindowMoveCallback() const ;
        inline void BindCursorMoveCallback() const ;
        inline void BindWindowMaximizeCallback() const ;
        inline void BindWindowMinimizeCallback() const ;
        inline void BindWindowFocusCallback() const ;
        inline void BindWindowCloseCallback() const ;
        inline void BindWindowRefreshCallback() const ;

        inline void initWindow();

        static void initGLAD();

        inline void createWindow();

        inline void updateSizeLimit();

        GLFWwindow*                         m_glfwWindow{};

        std::string                         m_title;

        std::pair<uint16_t, uint16_t>       m_size;
        std::pair<uint16_t, uint16_t>       m_minSize;
        std::pair<uint16_t, uint16_t>       m_maxSize;

        std::pair<uint16_t, uint16_t>       m_position;

        bool                                m_fullScreen{};
        uint32_t                            m_refreshRate{};

        WindowSetting                       m_windowSetting;

        static std::unordered_map<GLFWwindow*, Window*> g_Window_Map;

    };

}



#endif //ALITE_WINDOW_H
