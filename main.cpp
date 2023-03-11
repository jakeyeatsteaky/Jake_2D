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

class Observer
{
public:
    Observer() = default;
    Observer(std::string n) : name(n) {}
    ~Observer () {}

    void onNotifyAll() {
        std::cout << name << " says hello \n";
    }

    std::string getName() {return name;}
private:
    std::string name;
};

class Subject
{
public:
    Subject() = default;
    ~Subject() {}
    
    void AddObserver(Observer* ob) {
        observers.push_front(ob);
    }

    void RemoveObserver(Observer* ob) {
        observers.remove(ob);
    }

    void NotifyAll() {
        for(Observer* o : observers) {
            o->onNotifyAll();
        }
    }

private:
    std::string name;
    std::forward_list<Observer*> observers; // Consideration: Does this subject have ownership of all these observers?  Something to think about when using this raw pointer or smart pointers
    
};


int main(int argc, char** argv) 
{
    Subject subject;
    Observer ob  = Observer("ob");
    subject.AddObserver(&ob);
    subject.AddObserver(new Observer("Ob 2"));
    subject.AddObserver(new Observer("Ob 3"));

    subject.NotifyAll();

    subject.RemoveObserver(&ob);

    subject.NotifyAll();

    return 0;
}