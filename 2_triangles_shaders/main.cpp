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
   const char* fragment_shader_source1 =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "   FragColor = vec4(1.0f, 0.5f, 0.f, 1.0f);\n"
      "}\0";

   // Fragment shader
   const char* fragment_shader_source2 =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "   FragColor = vec4(1.0f, 1.0f, 0.f, 1.0f);\n"
      "}\0";

   // Initialize GLFW and tell it the version and profile
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   // Initialize the window
   GLFWwindow* window = glfwCreateWindow(800, 600, "2 triangle shaders.", nullptr, nullptr);
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
   glShaderSource(fragment_shader, 1, &fragment_shader_source1, nullptr);
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

   // Felt too lazy to create a function, just copied it

   // Create and compile the vertex shader
   unsigned vertex_shader2 = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertex_shader2, 1, &vertex_shader_source, nullptr);
   glCompileShader(vertex_shader2);

   // Check if vertex shader compilation was successful
   int success_v2 = 0;
   char info_log_v2[512] = "\0";
   glGetShaderiv(vertex_shader2, GL_COMPILE_STATUS, &success_v2);

   if (!success_v2)
   {
      glGetShaderInfoLog(vertex_shader2, sizeof(info_log_v2), nullptr, info_log_v2);
      std::cout << "Failed to compile the vertex shader: " << info_log_v2;
   }

   // Create and compile the fragment shader
   unsigned fragment_shader2 = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragment_shader2, 1, &fragment_shader_source2, nullptr);
   glCompileShader(fragment_shader2);

   // Check if fragment shader compilation was successful
   int success_f2 = 0;
   char info_log_f2[512] = "\0";
   glGetShaderiv(fragment_shader2, GL_COMPILE_STATUS, &success_f2);

   if (!success_f2)
   {
      glGetShaderInfoLog(fragment_shader2, sizeof(info_log_f2), nullptr, info_log_f2);
      std::cout << "Failed to compile the fragment shader: " << info_log_f2;
   }

   // Create and link the shader program
   unsigned shader_program2 = glCreateProgram();
   glAttachShader(shader_program2, vertex_shader2);
   glAttachShader(shader_program2, fragment_shader2);
   glLinkProgram(shader_program2);

   // Check if shader program linked successfully
   int success_sp2 = 0;
   char info_log_sp2[512] = "\0";
   glGetProgramiv(shader_program2, GL_LINK_STATUS, &success_sp2);

   if (!success_sp2)
   {
      glGetProgramInfoLog(shader_program2, sizeof(info_log_sp2), nullptr, info_log_sp2);
      std::cout << "Failed to link the shader program: " << info_log_sp2;
   }
   
   // Clean up the shaders
   glDeleteShader(vertex_shader2);
   glDeleteShader(fragment_shader2);

   // Create triangle vertices
   // Triangle 1
   float vertices_tr1[]
   {
      -0.75f, 0.0f, 0.0f,
      -0.5f,  0.5f, 0.0f,
      -0.25f, 0.0f, 0.0f
   };

   // Triangle 2
   float vertices_tr2[]
   {
      0.25f, 0.0f, 0.0f,
      0.5f,  0.5f, 0.0f,
      0.75f, 0.0f, 0.0f
   };

   // Create and bind a vertex buffer object
   unsigned VBO_tr1 = 0;
   glGenBuffers(1, &VBO_tr1);

   // Create a vertex attribute object
   unsigned VAO_tr1 = 0;
   glGenVertexArrays(1, &VAO_tr1);

   // Initialize the VAO
   glBindVertexArray(VAO_tr1);

   // Copy vertices in a buffer
   glBindBuffer(GL_ARRAY_BUFFER, VBO_tr1);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_tr1), vertices_tr1, GL_STATIC_DRAW);

   // Link vertex attributes
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   // Create the same buffer objects for the second triangle and link vertex attributes
   unsigned VBO_tr2 = 0;
   glGenBuffers(1, &VBO_tr2);

   unsigned VAO_tr2 = 0;
   glGenVertexArrays(1, &VAO_tr2);
   glBindVertexArray(VAO_tr2);

   glBindBuffer(GL_ARRAY_BUFFER, VBO_tr2);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_tr2), vertices_tr2, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   // Create the render loop
   while (!glfwWindowShouldClose(window))
   {
      // Check if the window should close
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
         glfwSetWindowShouldClose(window, true);

      // Render
      glClearColor(.5f, .5f, .5f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT);

      // Use the shader program
      glUseProgram(shader_program);

      // Draw the first triangle
      glBindVertexArray(VAO_tr1);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // Use the yellow shader program
      glUseProgram(shader_program2);

      // Draw the second triangle
      glBindVertexArray(VAO_tr2);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      glBindVertexArray(0);

      // Swap buffers and check and call events
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   // Clean up
   glfwTerminate();
   return 0;
}