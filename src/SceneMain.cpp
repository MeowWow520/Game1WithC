#include "SceneMain.h"
#include "Game.h"



SceneMain::SceneMain() : gameInstance(Game::getInstance()) {
    spdlog::info(u8"Entering SceneMain::SceneMain()");
}

SceneMain::~SceneMain() { 
    spdlog::info(u8"Entering SceneMain::~SceneMain()");
}

void SceneMain::Initialize() {
    spdlog::info(u8"Entering SceneMain::Initialize()");

    spdlog::info(u8"Initializing Player Texture");
    player.texture = IMG_LoadTexture(gameInstance.getRenderer(), "assets/images/Test_MyHander.jpg");
    if (player.texture == nullptr) {
        spdlog::error(u8"Failed to load player texture: {}", SDL_GetError());
        player.width = 100;
        player.height = 100;
    } else { 
        spdlog::info(u8"Player texture loaded successfully");
        spdlog::info(u8"Initializing SDL_QueryTexture");
        SDL_QueryTexture(player.texture, NULL, NULL, &player.width, &player.height);
    }
    // Setting initial player position and size
    spdlog::info(u8"Setting initial player position and size");
    spdlog::info(u8"Original player width: {}, height: {}", player.width, player.height);
    player.width /= 4;
    player.height /= 4;
    player.position.x = (float)(gameInstance.getWindowWidth() / 2) - (float)(player.width / 2);
    player.position.y = (float)(gameInstance.getWindowHeight() - player.height);

}

void SceneMain::handleEvents(SDL_Event *event) { }

void SceneMain::Update() { }

void SceneMain::Render() { 
    SDL_SetRenderDrawColor(gameInstance.getRenderer(), 220, 80, 100, 255);
    SDL_Rect r {200, 200, 400, 300};
    SDL_RenderFillRect(gameInstance.getRenderer(), &r);
    /*
    SDL_Rect playerRect = { static_cast<int>(player.position.x), 
                            static_cast<int>(player.position.y), 
                            player.width, 
                            player.height };
    SDL_RenderCopy(gameInstance.getRenderer(), player.texture, NULL, &playerRect);
    */
}

void SceneMain::Clean() { 
    spdlog::info(u8"Entering SceneMain::Clean()");

    if (player.texture != nullptr) {
        SDL_DestroyTexture(player.texture);
        spdlog::info(u8"Player texture destroyed");
    }
}
