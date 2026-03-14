#include "SceneMain.h"
#include "Game.h"


// 引入 gameInstance
SceneMain::SceneMain() : gameInstance(Game::getInstance()) {
    spdlog::info(u8"Entering SceneMain::SceneMain()");
}

SceneMain::~SceneMain() { 
    spdlog::info(u8"Entering SceneMain::~SceneMain()");
    Clean();
}

void SceneMain::Initialize() {
    spdlog::info(u8"Entering SceneMain::Initialize()");

    spdlog::info(u8"Initializing player.texture");
    player.texture = IMG_LoadTexture(gameInstance.getRenderer(), "assets/images/Test_MyHander.jpg");
    if (player.texture == nullptr) {
        spdlog::error(u8"Failed to load player texture: {}", SDL_GetError());
    } else { 
        spdlog::info(u8"Player.texture loaded successfully");
        spdlog::info(u8"Initializing SDL_QueryTexture");
        SDL_QueryTexture(player.texture, NULL, NULL, &player.width, &player.height);
        spdlog::info(u8"SDL_QueryTexture initialized successfully");
    }


    // 设置默认玩家位置
    player.width /= 4;
    player.height /= 4;
    player.position.x = (float)(gameInstance.getWindowWidth() / 2) - (float)(player.width / 2);
    player.position.y = (float)(gameInstance.getWindowHeight() - player.height);
    spdlog::info(u8"Setting initial player position and size");
    spdlog::info(u8"Original player.width: {}, player.height: {}", player.width, player.height);
    spdlog::info(u8"Original player.position.x: {}, player.position.y: {}", player.position.x, player.position.y);

}

void SceneMain::handleEvents(SDL_Event *event) { return; }

void SceneMain::Update() { 
    return;
}

void SceneMain::Render() { 
    SDL_Rect playerRect = { static_cast<int>(player.position.x), 
                            static_cast<int>(player.position.y), 
                            player.width, 
                            player.height };
    if (SDL_RenderCopy(gameInstance.getRenderer(), player.texture, NULL, &playerRect) != 0) {
        spdlog::error(u8"Called SDL_RenderCopy failed");
    }

}

void SceneMain::Clean() { 
    spdlog::info(u8"Entering SceneMain::Clean()");

    //删除玩家纹理
    if (player.texture != nullptr) {
        SDL_DestroyTexture(player.texture);
        spdlog::info(u8"Player texture destroyed");
    }
}
