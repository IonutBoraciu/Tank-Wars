#include <ctime>
#include <iostream>
#include "core/engine.h"
#include "components/simple_scene.h"
#include "lab_extra/shadow_mapping/shadow_mapping.h"
#include "lab_extra/compute_shaders/compute_shaders.h"
#include "lab_extra/compute_shaders_ext/compute_shaders_ext.h"
#include "lab_extra/tessellation_shader/tessellation_shader.h"
#include "lab_extra/basic_text/basic_text.h"
//#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_mixer.h"
#if defined(WITH_LAB_M1)
#   include "lab_m1/lab_list.h"
#endif

#if defined(WITH_LAB_M2)
#   include "lab_m2/lab_list.h"
#endif

#if defined(WITH_LAB_EXTRA)
#   include "lab_extra/lab_list.h"
#endif


#ifdef _WIN32
    PREFER_DISCRETE_GPU_NVIDIA;
    PREFER_DISCRETE_GPU_AMD;
#endif


std::string GetParentDir(const std::string &filePath)
{
    size_t pos = filePath.find_last_of("\\/");
    return (std::string::npos == pos) ? "." : filePath.substr(0, pos);
}


int main(int argc, char **argv)
{
    srand((unsigned int)time(NULL));

    // Create a window property structure
    WindowProperties wp;
    wp.resolution = glm::ivec2(1280, 720);
    wp.vSync = true;
    wp.selfDir = GetParentDir(std::string(argv[0]));

    // Init the Engine and create a new window with the defined properties
    (void)Engine::Init(wp);


    // Create a new 3D world and start running it
    World* world = new m1::Tema1;
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("not working sdl init audio\n");
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("not working mix open\n");
    }

    world->Init();
    world->Run();

    // Signals to the Engine to release the OpenGL context
    Engine::Exit();
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}
