/// VolumetricRendering.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Shader.h"
#include "RAW.h"
#include "Data.h"
#include "Texture.h"
 
//Dimensions
#define WIDTH 1000
#define HEIGHT 1000

//Main
int main()
{
    if (!glfwInit())
        return 1;

    //OpenGL specifications
    const char* glsl_version = "#version 460";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    //Window with graphics context
    window = glfwCreateWindow(WIDTH, HEIGHT, "Volumetric Renderer", NULL, NULL);
    if (window == NULL)
        return 2;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

     //GLEW initiaziation
    if (glewInit() != GLEW_OK)
        return 3;

    //Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    //Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    //ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    //for viewport resizing
    int display_w = WIDTH, display_h = HEIGHT;

    //Shader init
    Shader shaderVol("shaders/shader.vert", "shaders/shader.frag");
    Shader shaderQuad("shaders/quad.vert", "shaders/quad.frag");

    //Shader objects
    volShaderID = shaderVol.getShaderID();
    quadShaderID = shaderQuad.getShaderID();

    //Loading .raw file
    RAW raw;
    GLubyte* tempVolData =  raw.loadRaw(raw.filePath, raw.xDim, raw.yDim, raw.zDim);

    //Texture objects
    volTexObj = Texture::textureVolume(tempVolData, raw.xDim, raw.yDim, raw.zDim);
    transferFnTexObj = Texture::textureTransferFunction(transferFunction);
    quadTexObj = Texture::textureQuad(display_w, display_h);

    //Setting up buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, &EBO);

    //Binding Buffers
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    //Unbind Buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    //Depth Buffer
    GLuint depthBuffer;
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, display_w, display_w);

    //Frame Buffer to attcah texture and depth buffer
    GLuint frameBufferTD;
    glGenFramebuffers(1, &frameBufferTD);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferTD);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, quadTexObj, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    
    //Error check
    GLenum complete = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (complete != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "framebuffer is not complete" << std::endl;
        exit(EXIT_FAILURE);
    }

    //Transform Initial values
    fx = 0.1f, fy = 0.1f, fz = 0.0f;
    scale = 1.0f;
    
     // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        glfwPollEvents();
        glClearColor(1.0f,1.0f,1.0f,1.0f);

        //Setting Viewport for re-sizing
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        uiRoutine();

        glEnable(GL_DEPTH_TEST);
        // render to texture
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferTD);
        glViewport(0, 0, display_w, display_h);
        shaderQuad.shaderCall();
        // cull front face
        //glEnable(GL_CULL_FACE);
        transformationRoutine(GL_FRONT, quadShaderID);
        //glDisable(GL_CULL_FACE);
        shaderQuad.shaderClose();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, display_w, display_w);

        shaderVol.shaderCall();
        
        setUniform();
        // cull back face
        
        transformationRoutine(GL_BACK, volShaderID);
        
        shaderVol.shaderClose();

        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    

    //Destroy Calls
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, VBO);
    glDeleteBuffers(1, &EBO);
    glDisable(GL_TEXTURE_3D);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_1D);
    shaderVol.shaderDestroy();
    shaderQuad.shaderDestroy();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
 
//UI: ImGui
void uiRoutine()
{
    // Start the Dear ImGui frame (GUI)
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Show demo window (GUI)
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Begin("Volume Renderer Control");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("Transformation:");
    ImGui::SliderFloat("RotationX", &fx, -360.0f, 360.0f);              // Transform position along x axis
    ImGui::SliderFloat("RotationY", &fy, -360.0f, 360.0f);              // Transform position along y axis
    ImGui::SliderFloat("RotationZ", &fz, -360.0f, 360.0f);              // Transform position along z axis
    ImGui::SliderFloat("Scale", &scale, 0.0f, 2.0f);                     // Scale along all axes
    if (ImGui::Button("Reset Transform"))
    {
        fx = 0.0f, fy = 0.0f, fz = 0.0f;
        scale = 1.0f;
    }
    ImGui::SameLine();
    //ImGui::Checkbox("Demo Window", &show_demo_window);                  // Edit bools storing our window open/close state
    ImGui::End();
    // Rendering
    ImGui::Render();

    // Enable/Disable Wireframe
    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//MVP and Render Buffer
void transformationRoutine(GLenum glFaces, GLuint ID)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Transformations
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, fx * glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, fy * glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, fz * glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(scale, scale, scale));

    glm::mat4 view = glm::lookAt(camPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)display_w / display_h, 0.1f, 1000.0f);

    glm::mat4 MVP = projection * view * model;

    GLuint MVPLoc = glGetUniformLocation(ID, "MVP");
    glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

    glCullFace(glFaces);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

//Uniforms
void setUniform()
{
    GLuint stepLoc = glGetUniformLocation(volShaderID, "stepSize");
    glUniform3fv(stepLoc, 1, &(stepSize.x));

    GLuint screenSizeLoc = glGetUniformLocation(volShaderID, "screenSize");
    glUniform2f(screenSizeLoc, (float) display_w, (float) display_h);

    GLuint transferFuncLoc = glGetUniformLocation(volShaderID, "TransferFuncTex");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_1D, transferFnTexObj);
    glUniform1i(transferFuncLoc, 0);
   
    GLint quadLoc = glGetUniformLocation(volShaderID, "QuadTex");
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, quadTexObj);
    glUniform1i(quadLoc, 1);

    GLint volumeLoc = glGetUniformLocation(volShaderID, "VolumeTex");
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_3D, volTexObj);
    glUniform1i(volumeLoc, 2);
}