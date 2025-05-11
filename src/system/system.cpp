// configurações do sistema

#include "system.hpp"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

#include <SDL2/SDL.h>

#include "system/subsystems.hpp"
#include "system/global.hpp"
#include "system/graphics/window.hpp"

#include "app/config.hpp"
#include "app/app.hpp"

using namespace std::chrono;
using namespace std::literals::chrono_literals;

// Apenas para analisar se tá tendo muita alocação dinâmica...
void* operator new(size_t size) {
    std::cout << "[system] Allocing " << size << " bytes." << "\n";
    return malloc(size);
}

// armazena os eventos do SDL
SDL_Event SDLEvent;

time_point prevTime = system_clock::now();
time_point currTime = prevTime;

void System::Initialize(void) {
    InitializeSubsystems();

    // Inicializando janela
    window = std::make_shared<Window>("AI Test", 600, 400);

    // gerando recursos globais
    graphicsResources = GraphicsResources { window, imageHandler };
}

void System::Shutdown(void) {
    ShutdownSubsystems();

    // Finalizando janela
    window = nullptr;
}

void System::Run(void) {
    App app; // criando o objeto que controla a aplicação
    app.Initialize();

    // count de atualização
    const double appExecTimeStep = 1.0f / FPS;
    double appExecCount = appExecTimeStep;

    // count de FPS real
    int fps = 0;
    double fpsTimeCount = 1.0f;
    int fpsCount = 0;

    while (!SDL_QuitRequested()) {
        SDL_PollEvent(&SDLEvent);

        // calculando tempo decorrido desde a última execução do loop
        currTime = system_clock::now();
        double loopDeltaTime = duration<double>(currTime - prevTime).count();
        prevTime = currTime;

        appExecCount -= loopDeltaTime;
        fpsTimeCount -= loopDeltaTime;

        // tempo decorrido desde a última atualização
        static double deltaTime = 0;
        deltaTime += loopDeltaTime;

        // atualiza a aplicação com fps fixo
        if (appExecCount <= 0) {
            window->Clear();

            app.Update(deltaTime);
            app.Render(fps);
            
            window->Render();

            fpsCount++;
            appExecCount = appExecTimeStep;
            deltaTime = 0;
        }

        // calcula o fps real
        if (fpsTimeCount <= 0) {
            fpsTimeCount = 1.0f;
            fps = fpsCount;
            fpsCount = 0;
        }

        SDL_Delay(1); // limite de execução
    }

    app.Shutdown();
}
