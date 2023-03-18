#include "stdio.h"

#include "SDL_functions.h"

SDL::SDL() 
{

}

SDL::~SDL() 
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void SDL::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("Could not init SDL ::SDL_ERROR:: {}\n");
    }

    m_window = SDL_CreateWindow("GameWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!m_window){
        printf("SDL Window could not be created :: SDL_ERROR :: {}\n");
    }

    SDL_SetWindowResizable(m_window, SDL_TRUE);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer){
        printf("SDL Renderer could not be created :: SDL_ERROR :: {}\n");
    }

    framebuffer = (uint32_t*)malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
    if(!framebuffer) {
        fprintf(stderr, "Error allocating memory for the frambuffer\n");
        return;
    }

    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

    printf("Successfully created SDL Window\n");

}

int lerp(int a, int b, float t)
{
    return (1-t) * a + t*b;
}

void render(SDL* sdl)
{
    SDL_Renderer* renderer = sdl->getRenderer();

    // clear
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //object
    // Vec2 pos;
    //         float t = 0.01;
    // for(int i = 10; i < 1600; ++i)
    // {
    //         pos.xPos = i;
    //         pos.yPos = ;
    //         int color = lerp(0,255,t);
    //         SDL_SetRenderDrawColor(renderer, color, 0, 0, 255);
    //         SDL_RenderDrawPoint(renderer, pos.xPos, pos.yPos);
    //         t+=0.01;
    // }

    
    // Update the screen
    SDL_RenderPresent(renderer);
}

void process_input(bool& is_running) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        is_running = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
          is_running = false;
        break;
    }
  }
}