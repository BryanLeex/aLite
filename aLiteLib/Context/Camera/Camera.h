//
// Created by Bryan on 11/08/2024.
//

#ifndef ALITE_CAMERA_H
#define ALITE_CAMERA_H

#include "Setting.h"

#include "Context/Window/Window.h"

#include "Context/Device/Device.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Context::Camera {

    class Camera {
    public:

        Camera(Context::Window::Window *p_window) {

            m_window = p_window;
            m_setting = CameraSetting();
            m_movement = 0;

            InitCamera ();

        }

        Camera(Context::Window::Window *p_window, CameraSetting p_setting) {

            m_window = p_window;
            m_setting = p_setting;
            m_movement = 0;

            InitCamera ();

        }

        virtual void Tick() {

            aLog("Camera")->info("m_movement: {:8b}", m_movement);

        }

    private:

        enum class EMovement {
            Forward     = 0b00000001,
            Backward    = 0b00000010,
            Left        = 0b00000100,
            Right       = 0b00001000,
            Jump        = 0b00010000,
            Squat       = 0b00100000,
            Sprint      = 0b01000000,
            Sneak       = 0b10000000,
        };
        uint64_t m_movement;

        void InitCamera () {

            m_window->me_KeyPressedEvent.AddListener(std::bind(&Camera::KeyPressEventFunc, this, std::placeholders::_1));

            m_window->me_KeyReleasedEvent.AddListener(std::bind(&Camera::KeyReleaseEventFunc, this, std::placeholders::_1));

            m_lookatMat =  glm::lookAt(glm::vec3 (0, 1, 0), glm::vec3 (0, 0, 0), glm::vec3(0, 1, 0));

        }

        void KeyReleaseEventFunc (int32_t Key) {

            switch (Key) {
                case static_cast<int32_t>(Device::EKey::KEY_W):
                    aLog("Camera")->info("Go Forward.");
                    m_movement &= static_cast<uint64_t>(Camera::EMovement::Forward) - 1;
                    break;

                case static_cast<int32_t>(Device::EKey::KEY_A):
                    m_movement &= static_cast<uint64_t>(Camera::EMovement::Left) - 1;
                    aLog("Camera")->info("Go Left.");
                    break;

                case static_cast<int32_t>(Device::EKey::KEY_S):
                    m_movement &= static_cast<uint64_t>(Camera::EMovement::Backward) - 1;
                    aLog("Camera")->info("Go Backward.");
                    break;

                case static_cast<int32_t>(Device::EKey::KEY_D):
                    m_movement &= static_cast<uint64_t>(Camera::EMovement::Right) - 1;
                    aLog("Camera")->info("Go Right.");
                    break;
            }

        }

        void KeyPressEventFunc (int32_t Key) {

            switch (Key) {
                case static_cast<int32_t>(Device::EKey::KEY_W):
                    aLog("Camera")->info("Go Forward.");
                    m_movement |= static_cast<uint64_t>(Camera::EMovement::Forward);
                    break;

                case static_cast<int32_t>(Device::EKey::KEY_A):
                    m_movement |= static_cast<uint64_t>(Camera::EMovement::Left);
                    aLog("Camera")->info("Go Left.");
                    break;

                case static_cast<int32_t>(Device::EKey::KEY_S):
                    m_movement |= static_cast<uint64_t>(Camera::EMovement::Backward);
                    aLog("Camera")->info("Go Backward.");
                    break;

                case static_cast<int32_t>(Device::EKey::KEY_D):
                    m_movement |= static_cast<uint64_t>(Camera::EMovement::Right);
                    aLog("Camera")->info("Go Right.");
                    break;
            }

        }

        std::function<int32_t> mf_KeyPressEvent(int32_t Key);

        glm::mat4 m_lookatMat;
        glm::mat4 m_projMat;
        glm::mat4 m_cameraMat;

        glm::vec3 m_cameraPos;

        float_t m_FOV = 45.f;

        Context::Window::Window* m_window;
        CameraSetting m_setting;

    };

}

#endif //ALITE_CAMERA_H
