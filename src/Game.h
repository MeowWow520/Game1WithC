#pragma once

#ifndef GAME_H
#define GAME_H



class Game {
public:
    Game() = default;
    ~Game() = default;
    void Run();
    void Init();
    void Update();
    void Clean();
    
private:
    bool isRunning = true;
};

#endif // !GAME_H