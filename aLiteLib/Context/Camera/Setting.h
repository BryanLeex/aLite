//
// Created by Bryan on 11/08/2024.
//

#pragma once

#include <stdexcept>

namespace Context::Camera {
    struct CameraSetting {

        float_t Sensitivity = 1.f;

        float_t DefaultVelocity = 1.f;
        float_t SneakVelocity   = 3.f;
        float_t SprintVelocity  = .5f;

    };
}


