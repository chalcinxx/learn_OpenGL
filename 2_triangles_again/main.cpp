#include <glad/glad.h>
#include <GLFW/glfw3.h>

void window_resize_callback(GLFWwindow*, int width, int height)
{
   glViewport(0, 0, width, height);
}

int main()
{
   const char* vertex_shader_source =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{ gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); }\0";
   
   const char* fragment_shader_source =
      "#version 330 core\n"
      "out vec4 FragColor;"
      "void main()\n"
      "{ FragColor = vec4(1.0, 0.0, 0.0, 1.0); }\0";

   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   GLFWwindow* window = glfwCreateWindow(800, 600, "2 Triangles from memory (mostly).", nullptr, nullptr);
   glfwMakeContextCurrent(window);
   
   gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
   glViewport(0, 0, 800, 600);
   glfwSetFramebufferSizeCallback(window, window_resize_callback);

   unsigned vertex = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertex, 1, &vertex_shader_source, nullptr);
   glCompileShader(vertex);

   unsigned fragment = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragment, 1, &fragment_shader_source, nullptr);
   glCompileShader(fragment);

   unsigned shader_program = glCreateProgram();
   glAttachShader(shader_program, vertex);
   glAttachShader(shader_program, fragment);
   glLinkProgram(shader_program);

   glDeleteShader(vertex);
   glDeleteShader(fragment);

   float vertices[]
   {
      // Triangle 1
      -0.75f, 0.0f, 0.0f,
      -0.5f,  0.5f, 0.0f,
      -0.25f, 0.0f, 0.0f,
      // Triangle 2
       0.75f, 0.0f, 0.0f,
       0.5f,  0.5f, 0.0f,
       0.25f, 0.0f, 0.0f
   };

   unsigned VBO = 0;
   glGenBuffers(1, &VBO);

   unsigned VAO = 0;
   glGenVertexArrays(1, &VAO);

   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   while (!glfwWindowShouldClose(window))
   {
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
         glfwSetWindowShouldClose(window, true);
      
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shader_program);

      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 6);

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glfwTerminate();
   return 0;
}