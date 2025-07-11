#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <iostream>

// Throw an exception and terminate GLFW
void throw_ex(const char* msg)
{
   std::cout << msg << '\n';
   glfwTerminate();
   std::exit(-1);
}

// Resize callback function
void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
   assert(width > 0 && height > 0);
   glViewport(0, 0, width, height);
}

// Main function
int main()
{
   // Vertex shader
   const char* vertex_shader_source =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";
   
   // Fragment shader
   const char* fragment_shader_source =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "   FragColor = vec4(1.0f, 0.5f, 0.f, 1.0f);\n"
      "}\0";

   // Initialize GLFW and tell it the version and profile
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   // Initialize the window
   GLFWwindow* window = glfwCreateWindow(800, 600, "2 Triangles.", nullptr, nullptr);
   if (!window)
      throw_ex("Failed to create the window!");
   
   // Set the current window
   glfwMakeContextCurrent(window);

   // Initialize GLAD
   if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
      throw_ex("Failed to initialize GLAD!");
   
   // Set the viewport
   glViewport(0, 0, 800, 600);

   // Set window resize callback
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   // Create triangle vertices
   float vertices[]
   {
      // Triangle 1
      -0.75f, 0.0f, 0.0f,
      -0.5f,  0.5f, 0.0f,
      -0.25f, 0.0f, 0.0f,
      // Triangle 2
       0.25f, 0.0f, 0.0f,
       0.5f,  0.5f, 0.0f,
       0.75f, 0.0f, 0.0f
   };

   // Create and bind a vertex buffer object
   unsigned VBO = 0;
   glGenBuffers(1, &VBO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);

   // GL_STATIC_DRAW, GL_STREAM_DRAW, GL_DYNAMIC_DRAW
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   // Create and compile the vertex shader
   unsigned vertex_shader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
   glCompileShader(vertex_shader);

   // Check if vertex shader compilation was successful
   int success_v = 0;
   char info_log_v[512] = "\0";
   glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success_v);

   if (!success_v)
   {
      glGetShaderInfoLog(vertex_shader, sizeof(info_log_v), nullptr, info_log_v);
      std::cout << "Failed to compile the vertex shader: " << info_log_v;
   }

   // Create and compile the fragment shader
   unsigned fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
   glCompileShader(fragment_shader);

   // Check if fragment shader compilation was successful
   int success_f = 0;
   char info_log_f[512] = "\0";
   glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success_f);

   if (!success_f)
   {
      glGetShaderInfoLog(fragment_shader, sizeof(info_log_f), nullptr, info_log_f);
      std::cout << "Failed to compile the fragment shader: " << info_log_f;
   }

   // Create and link the shader program
   unsigned shader_program = glCreateProgram();
   glAttachShader(shader_program, vertex_shader);
   glAttachShader(shader_program, fragment_shader);
   glLinkProgram(shader_program);

   // Check if shader program linked successfully
   int success_sp = 0;
   char info_log_sp[512] = "\0";
   glGetProgramiv(shader_program, GL_LINK_STATUS, &success_sp);

   if (!success_sp)
   {
      glGetProgramInfoLog(shader_program, sizeof(info_log_sp), nullptr, info_log_sp);
      std::cout << "Failed to link the shader program: " << info_log_sp;
   }
   
   // Clean up the shaders
   glDeleteShader(vertex_shader);
   glDeleteShader(fragment_shader);

   // Create a vertex attribute pointer
   unsigned VAO = 0;
   glGenVertexArrays(1, &VAO);

   // Initialize the VAO
   glBindVertexArray(VAO);

   // Copy vertices in a buffer
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   // Link vertex attributes
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   // Create the render loop
   while (!glfwWindowShouldClose(window))
   {
      // Input

      // Check if the window should close
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
         glfwSetWindowShouldClose(window, true);

      // Render
      glClearColor(.5f, .5f, .5f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT);

      // Use the shader program and bind VAO
      glUseProgram(shader_program);
      glBindVertexArray(VAO);

      // Draw the first triangle
      // glDrawArrays(GL_TRIANGLES, 0, 3);

      // Draw the second triangle
      // glDrawArrays(GL_TRIANGLES, 3, 3);

      // On reviewing the solution, it is more optimal to just draw all 6 vertices at once
      glDrawArrays(GL_TRIANGLES, 0, 6);

      // Swap buffers and check and call events
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   // Clean up
   glfwTerminate();
   return 0;
}