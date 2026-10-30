
#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "formas.h"
#include "menu.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    const unsigned int withd = 800;
    const unsigned int height = 800;

    Window janela;
    if (!janela.criar("OpenGL"))
        return -1;

    Shader shader;
    if (!shader.criarDeArquivos(ASSETS_DIR "shaders/basic.vert",
                                ASSETS_DIR "shaders/basic.frag"))
    {
        std::cout << "Falha ao criar o shader!" << std::endl;
        return -1;
    }

    Mesh triangulo;
    if (!triangulo.criar(formas::triangulo(1.0f)))
    {
        std::cout << "Falha ao criar o triangulo!" << std::endl;
        return -1;
    }

    Mesh retangulo;
    if (!retangulo.criar(formas::retangulo(), 2))
    {
        std::cout << "Falha ao criar o retangulo!" << std::endl;
        return -1;
    }

    Mesh quadrado;
    if (!quadrado.criar(formas::quadrado(), 2))
    {
        std::cout << "Falha ao criar o quadrado!" << std::endl;
        return -1;
    }

    // Matrizes GLM
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    // Câmera
    view = glm::translate(
        view,
        glm::vec3(0.0f, -0.5f, -2.0f)
    );

    // Projeção
    proj = glm::perspective(
        glm::radians(45.0f),
        (float)withd / (float)height,
        0.1f,
        100.0f
    );

    // Rotação do objeto
    model = glm::rotate(
        model,
        glm::radians(45.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    Menu menu;
    if (!menu.criar())
        return -1;

    while (!janela.deveFechar())
    {
        menu.atualizar(janela);

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.usar();

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("proj", proj);

        quadrado.desenhar();

        menu.desenhar(janela);

        janela.trocarBuffers();
        janela.processarEventos();
    }

    return 0;
}