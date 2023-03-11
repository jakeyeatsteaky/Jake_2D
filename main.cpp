#include <forward_list>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>

#include "SDL.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#ifdef _USE_SDL_
void sdl() 
{
   if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Could not init SDL ::SDL_ERROR:: {}\n");
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window){
        printf("SDL Window could not be created :: SDL_ERROR :: {}\n");
    }

    SDL_SetWindowResizable(window, SDL_TRUE);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        printf("SDL Renderer could not be created :: SDL_ERROR :: {}\n");
    }

    printf("Successfully created SDL Window\n");
}
#endif

class Observer_Interface
{
public:
    virtual ~Observer_Interface() {}
    virtual void OnNotifyAll() = 0;

};
class Subject_Interface
{
public:
    Subject_Interface() {}
    virtual ~Subject_Interface() {} // virtual destructors are necessary when you have a base class with derived classes and at least one virtual function.  The base class is assumed to be used polymorphically

    virtual void AddObserver(Observer_Interface* ob_i) {
        observers.push_front(ob_i);
    }

    virtual void RemoveObserver(Observer_Interface* ob_i) {
        observers.remove(ob_i);
    }

    virtual void NotifyAll() {
        for(Observer_Interface* o : observers)
            o->OnNotifyAll();
    }

private:   
    std::forward_list<Observer_Interface*> observers;
};


class Watcher : public Observer_Interface
{
public:
    explicit Watcher(const std::string& name): name(name) {};

    void OnNotifyAll() override {
        std::cout << name << " has been notified\n";
    }

private:
    std::string name;
};

class Concrete_Subject : public Subject_Interface
{
public:
    
};


int main(int argc, char** argv) 
{


    return 0;
}