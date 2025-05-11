// definições da aplicação

#pragma once

class App {
    public:
        void Initialize(void);
        void Shutdown(void);

        //

        void Update(double deltaTime);
        void Render(int fps);
};
