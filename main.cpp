#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <string>

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& path)
{
    SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
    if (!tex)
        std::cerr << "Failed to load: " << path << " | " << SDL_GetError() << std::endl;
    return tex;
}

int main(int argc, char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window =
        SDL_CreateWindow("Centered Cross Layout", 800, 600, SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        std::cerr << "Window failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, NULL);

    if (!renderer)
    {
        std::cerr << "Renderer failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::string base = "C:\\Users\\OGB\\source\\repos\\IMAGES ASSIGNMENT\\x64\\Debug\\";

    SDL_Texture* topTex = LoadTexture(renderer, base + "img1.png");
    SDL_Texture* bottomTex = LoadTexture(renderer, base + "img2.png");
    SDL_Texture* leftTex = LoadTexture(renderer, base + "img3.png");
    SDL_Texture* rightTex = LoadTexture(renderer, base + "img4.png");

    if (!topTex || !bottomTex || !leftTex || !rightTex)
    {
        std::cerr << "Image loading failed." << std::endl;
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event e;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
                running = false;
        }

        int winW, winH;
        SDL_GetWindowSize(window, &winW, &winH);

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        float size = 150.0f;
        float gap = 95.0f;

        float cx = winW / 2.0f;
        float cy = winH / 2.0f;

        SDL_FRect topRect = {
            cx - size / 2,
            cy - size - gap,
            size,
            size
        };

        SDL_FRect bottomRect = {
            cx - size / 2,
            cy + gap,
            size,
            size
        };

        SDL_FRect leftRect = {
            cx - size - gap,
            cy - size / 2,
            size,
            size
        };

        SDL_FRect rightRect = {
            cx + gap,
            cy - size / 2,
            size,
            size
        };

        SDL_RenderTexture(renderer, topTex, NULL, &topRect);
        SDL_RenderTexture(renderer, bottomTex, NULL, &bottomRect);
        SDL_RenderTexture(renderer, leftTex, NULL, &leftRect);
        SDL_RenderTexture(renderer, rightTex, NULL, &rightRect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(topTex);
    SDL_DestroyTexture(bottomTex);
    SDL_DestroyTexture(leftTex);
    SDL_DestroyTexture(rightTex);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}