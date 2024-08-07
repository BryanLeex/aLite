#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "aLiteLib/Context/Context.h"

int main() {

    Context::Context context;


    while (context.GetWindow()->isWindowRunning()) {

        glClearColor(44/255.f, 10/255.f, 36/255.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();
        context.GetWindow()->SwapBuffer();

    }

    return 0;
}
