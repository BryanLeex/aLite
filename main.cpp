#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "aLiteLib/Context/Context.h"

int main() {

    Context::Context context;


    while (context.GetWindow()->isWindowRunning()) {

        glfwPollEvents();

        context.GetWindow()->SwapBuffer();

        // @TODO: Complete it tomorrow.

    }

    return 0;
}
