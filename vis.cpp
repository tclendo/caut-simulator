#include <fstream>
#include <iostream>
#include <cstdlib>
#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

using namespace std;

int display_simulation(int rows, int cols, int ruleset, fstream& grid_file) {

  /* 
	 initial set up code for OpenGL window from 
	 https://antongerdelan.net/opengl/hellotriangle.html
  */
// start GL context and O/S window using the GLFW helper library
  if (ruleset == 2) cout << "Fire simulation received by vis" << endl;
  if (!glfwInit()) {
    cerr << "ERROR: could not start GLFW3" << endl;
    return 1;
  } 

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(700, 700, "Cellular Automata", NULL, NULL);
  if (!window) {
    cerr << "ERROR: could not open window with GLFW3" << endl;
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
                                  
  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit();

  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); // version as a string
  cout << "Renderer: " << renderer << endl;
  cout << "OpenGL version supported " << version << endl;

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

  /* OTHER STUFF GOES HERE NEXT */
  while (!glfwWindowShouldClose(window)) {
    // wipe the drawing surface clear
    glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
    //glBindVertexArray(vao);
    // Draw triangles
       
    //glDrawElements( GL_TRIANGLES, 44106, GL_UNSIGNED_INT, NULL );
     
    // update other events like input handling
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);
  }
  
  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}
