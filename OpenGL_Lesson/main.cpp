//
//  main.cpp
//  OpenGL_Lesson
//
//  Created by wta1601 on 2017/11/08.
//  Copyright © 2017年 kyo. All rights reserved.
//

#include "global.h"
#include "Loader.hpp"

// glfwWindowHintをまとめた処理です
void initWindowHints();

int main() {
    
    if (!glfwInit()){
        return -1;
    }
    
    initWindowHints();
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "🐵", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }
    
    vector<vec3> vertices;
    LoadMesh("monkey.obj", &vertices);
    
    // シェーダー読み込み
    GLuint programID = LoadShaders( "Red.vs", "Red.fs" );
    
    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
    
    
    while (!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* ここから三角の描画処理 */
        
        glUseProgram(programID);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        
        glDrawArrays(GL_TRIANGLES, 0, (int)(vertices.size()));
        glDisableVertexAttribArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void initWindowHints()
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED ,true);  // <-これをfalseにすると…
}


