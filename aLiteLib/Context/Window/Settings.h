//
// Created by Bryan on 06/08/2024.
//

#ifndef ALITE_SETTING_H
#define ALITE_SETTING_H

#include <string>

namespace Context::Window {

    struct WindowSetting {

        std::string         m_title = "Unnamed";

        uint16_t            m_width = 800;
        uint16_t            m_height = 600;

        uint16_t            m_minWidth = 0;
        uint16_t            m_minHeight = 0;

        uint16_t            m_maxWidth = -1;
        uint16_t            m_maxHeight = -1;

        bool                m_fullscreen = false;

        bool                m_resizeable = true;

        bool                m_focused = true;

        bool                m_maximized = false;

        bool                m_visible = true;

        int32_t           m_refreshRate = 60;

        uint8_t             m_samples = 4;

    };

}

#endif //ALITE_SETTING_H
