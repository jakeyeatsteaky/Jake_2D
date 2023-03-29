
#include <array>
#include <queue>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <compare>
#include <climits>

#include "App.h"
#include "DataStructures.h"
#include "Observer.h"
#include "util.h"

int main(int argc, char** argv) {
    
    App app;

    app.Setup();

    while(app.IsRunning())
    {
        app.Input();
        app.Update();
        app.Render();
        
    }

    app.Destroy();

    return 0;

}



