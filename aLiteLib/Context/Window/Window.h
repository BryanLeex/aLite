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

namespace Context::Window {

    class Window {

    public:

        Window();
        explicit Window(WindowSetting &p_windowSetting);

        ~Window();

        std::pair<int16_t, int16_t>     getPosition();

        void                            SwapBuffer();

        bool                            isWindowRunning();

    private:

        void initWindow();

        static void initGLAD();

        void createWindow();

        void updateSizeLimit();

        GLFWwindow*                         m_glfwWindow = nullptr;

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
