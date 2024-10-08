#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <filesystem>

#include "Context/Context.h"

#include "Utils/BasicGeo.h"
#include "Utils/Foreach.h"

#include "Render/Resources/Shader.h"

int main() {

    Context::Context context;

    auto shader = Render::Resources::Shader("../resources/shaders/default");

    Utils::BasicGeo plane;

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load("../resources/textures/grass_block_side.png", &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        aLog("Main")->error("Failed to load texture");
    }
    stbi_image_free(data);
    shader.SetValue("aTexture", 0);

    try {
        while (context.GetWindow()->isWindowRunning()) {

            glClearColor(44/255.f, 10/255.f, 36/255.f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            context.Tick();

//            shader.SetValue("time", glfwGetTime());
            shader.SetValue("aModel", glm::scale(glm::mat4(1), glm::vec3 (.5, .5, 1)));

            shader.Bind();
            plane.Draw();

            context.GetWindow()->SwapBuffer();
            glfwPollEvents();

        }
    } catch (std::exception &exception) {
        aLog("Main")->critical(exception.what());
    } catch (...) {
        aLog("Main")->critical("Unknown Error");
    }


    return 0;
}
