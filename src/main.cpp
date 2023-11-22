/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: main.cpp
@version: I
Creation: 07/11/2023
Last modification: 21/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#include "cube.h"
#include "camera.h"
#include "colors.h"
#include "object.h"
#include "sphere.h"
#include "skybox.h"
#include "materials.h"
#include <SDL.h>
#include <string>
#include <vector>
#include <cstdlib>
#include "SDL_image.h"
#include <SDL_events.h>
#include <SDL_render.h>
#include "glm/geometric.hpp"
#include "glm/glm.hpp"
#include <SDL_mixer.h>
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"

// constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 650;
const float ASPECT_RATIO = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);
const int MAX_RECURSION = 3;
const float BIAS = 0.0001f;

// function prototypes
SDL_Renderer* renderer;
std::vector<Object*> objects;
Skybox skybox("src/assets/background/bck.png");
Light light(glm::vec3(-20.0, -30, 30), 1.5f, Color(255, 255, 255));
Camera camera(glm::vec3(0.0, 0.0, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, 1.0f);

// implementation of shadow casting logic
float castShadow(const glm::vec3& shadowOrigin, const glm::vec3& lightDir, Object* hitObject) {
    for (auto& obj : objects) {
        if (obj != hitObject) {
            Intersect shadowIntersect = obj->rayIntersect(shadowOrigin, lightDir);
            if (shadowIntersect.isIntersecting && shadowIntersect.dist > 0) {
                float shadowRatio = shadowIntersect.dist / glm::length(light.position - shadowOrigin);
                shadowRatio = glm::min(1.0f, shadowRatio);
                return 1.0f - shadowRatio;
            }
        }
    }
    return 1.0f; // placeholder value
}

// implementation of point drawing logic
void point(glm::vec2 position, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, position.x, position.y);
}

// implementation of ray casting logic
Color castRay(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, const short recursion = 0) {
    float zBuffer = 99999;
    Object* hitObject = nullptr;
    Intersect intersect;

    for (const auto& object : objects) {
        Intersect i;
        if (dynamic_cast<Cube*>(object) != nullptr) {
            i = dynamic_cast<Cube*>(object)->rayIntersect(rayOrigin, rayDirection);
        } else if (dynamic_cast<Sphere*>(object) != nullptr) {
            i = dynamic_cast<Sphere*>(object)->rayIntersect(rayOrigin, rayDirection);
        }
        if (i.isIntersecting && i.dist < zBuffer) {
            zBuffer = i.dist;
            hitObject = object;
            intersect = i;
        }
    }

    if (!intersect.isIntersecting || recursion == MAX_RECURSION) {
        return skybox.getColor(rayDirection);  // Sky color
    }

    glm::vec3 lightDir = glm::normalize(light.position - intersect.point);
    glm::vec3 viewDir = glm::normalize(rayOrigin - intersect.point);
    glm::vec3 reflectDir = glm::reflect(-lightDir, intersect.normal);

    float shadowIntensity = castShadow(intersect.point, lightDir, hitObject);
    float diffuseLightIntensity = std::max(0.0f, glm::dot(intersect.normal, lightDir));
    float specReflection = glm::dot(viewDir, reflectDir);

    Material mat = hitObject->material;

    float specLightIntensity = std::pow(std::max(0.0f, glm::dot(viewDir, reflectDir)), mat.specularCoefficient);

    Color reflectedColor(0.0f, 0.0f, 0.0f);
    if (mat.reflectivity > 0) {
        glm::vec3 origin = intersect.point + intersect.normal * BIAS;
        reflectedColor = castRay(origin, reflectDir, recursion + 1);
    }

    Color refractedColor(0.0f, 0.0f, 0.0f);
    if (mat.transparency > 0) {
        glm::vec3 origin = intersect.point - intersect.normal * BIAS;
        glm::vec3 refractDir = glm::refract(rayDirection, intersect.normal, mat.refractionIndex);
        refractedColor = castRay(origin, refractDir, recursion + 1);
    }

    Color diffuseLight = mat.diffuse * light.intensity * diffuseLightIntensity * mat.albedo * shadowIntensity;
    Color specularLight = light.color * light.intensity * specLightIntensity * mat.specularAlbedo * shadowIntensity;
    Color color = (diffuseLight + specularLight) * (1.0f - mat.reflectivity - mat.transparency) + reflectedColor * mat.reflectivity + refractedColor * mat.transparency;
    return color; // placeholder value
}

// axolotl properties to draw block by block
void createAxolotl() {
    // face
    objects.push_back(new Cube(glm::vec3(-1.3f, -1.3f, -2.5f), glm::vec3(2.0f, 1.0f, 0.4f), barbie));
   
    // left eye
    objects.push_back(new Cube(glm::vec3(-1.0f, -0.3f, 0.4f), glm::vec3(-0.7f, -0.1f, 0.41f), carbon));
    objects.push_back(new Cube(glm::vec3(-1.3f, -0.3f, 0.4f), glm::vec3(-1.0f, -0.1f, 0.41f), carbon));
    objects.push_back(new Cube(glm::vec3(-1.0f, -0.45f, 0.4f), glm::vec3(-0.7f, -0.25f, 0.41f), carbon));
    objects.push_back(new Cube(glm::vec3(-1.3f, -0.45f, 0.4f), glm::vec3(-1.0f, -0.25f, 0.41f), carbon));

    // right eye
    objects.push_back(new Cube(glm::vec3(1.4f, -0.3f, 0.4f), glm::vec3(1.7f, -0.1f, 0.41f), carbon));
    objects.push_back(new Cube(glm::vec3(1.7f, -0.3f, 0.4f), glm::vec3(2.0f, -0.1f, 0.41f), carbon));
    objects.push_back(new Cube(glm::vec3(1.4f, -0.45f, 0.4f), glm::vec3(1.7f, -0.25f, 0.41f), carbon));
    objects.push_back(new Cube(glm::vec3(1.7f, -0.45f, 0.4f), glm::vec3(2.0f, -0.25f, 0.41f), carbon));

    // smile
    objects.push_back(new Cube(glm::vec3(0.2f, -0.5f, 0.4f), glm::vec3(0.6f, -0.3f, 0.41f), smile));
    objects.push_back(new Cube(glm::vec3(0.2f, -0.45f, 0.4f), glm::vec3(0.6f, -0.25f, 0.41f), smile));

    // body
    objects.push_back(new Cube(glm::vec3(-1.0f, -1.3f, -5.5f), glm::vec3(1.0f, 0.5f, -2.5f), barbie));
    objects.push_back(new Cube(glm::vec3(-1.001f, 0.5f, -5.5f), glm::vec3(1.001f, 0.5f, -5.3f), barbie));
    objects.push_back(new Cube(glm::vec3(-1.001f, 0.5f, -5.3f), glm::vec3(1.001f, 0.5f, -4.0f), barbie));
    objects.push_back(new Cube(glm::vec3(-1.001f, 0.5f, -5.5f), glm::vec3(1.001f, -0.1f, -5.3f), popsicle));
    objects.push_back(new Cube(glm::vec3(-1.001f, -1.3f, -2.5f), glm::vec3(1.001f, -1.0f, -5.0f), carbon));
    objects.push_back(new Cube(glm::vec3(-1.001f, -1.0f, -2.5f), glm::vec3(1.001f, -0.7f, -4.4f), smile));
    objects.push_back(new Cube(glm::vec3(-1.001f, -1.0f, -2.5f), glm::vec3(1.001f, 0.5f, -2.8f), coal));
    objects.push_back(new Cube(glm::vec3(-1.002f, -1.3f, -2.5f), glm::vec3(1.002f, -1.0f, -2.8f), barbie));
    objects.push_back(new Cube(glm::vec3(-1.001f, 0.0f, -3.5f), glm::vec3(1.001f, 0.3f, -5.0f), rubber));
    objects.push_back(new Cube(glm::vec3(-1.001f, -0.3f, -2.8f), glm::vec3(1.001f, -0.6f, -4.0f), barbie));

    // tail
    objects.push_back(new Cube(glm::vec3(-0.35f, -0.7f, -5.5f), glm::vec3(0.2f, 0.3f, -7.0f), barbie));
    objects.push_back(new Cube(glm::vec3(-0.35f, -0.75f, -0.75f), glm::vec3(0.2f, 0.1f, -7.5f), popsicle));
    objects.push_back(new Cube(glm::vec3(-0.35f, -0.5f, -0.75f), glm::vec3(0.2f, 0.0f, -7.8f), darkCoal));
    objects.push_back(new Cube(glm::vec3(-0.35f, -0.2f, -0.75f), glm::vec3(0.2f, 0.0f, -8.0f), coal));

    // right front leg
    objects.push_back(new Cube(glm::vec3(-0.25f, -1.0f, -2.75f), glm::vec3(2.5f, -0.75f, -1.0f), popsicle));
    objects.push_back(new Cube(glm::vec3(-0.25f, -1.0f, -2.75f), glm::vec3(2.5f, -0.75f, -3.0f), white));

    // left front leg
    objects.push_back(new Cube(glm::vec3(-2.0f, -1.0f, -2.75f), glm::vec3(2.5f, -0.75f, -1.0f), popsicle));
    objects.push_back(new Cube(glm::vec3(-2.0f, -1.0f, -2.75f), glm::vec3(2.5f, -0.75f, -3.0f), smile));

    // right back leg
    objects.push_back(new Cube(glm::vec3(-0.25f, -1.0f, -4.75f), glm::vec3(2.5f, -0.75f, -5.0f), popsicle));
    objects.push_back(new Cube(glm::vec3(-0.25f, -1.0f, -4.75f), glm::vec3(2.5f, -0.75f, -6.5f), white));

    // left back leg
    objects.push_back(new Cube(glm::vec3(-2.0f, -1.0f, -4.75f), glm::vec3(2.5f, -0.75f, -5.0f), popsicle));
    objects.push_back(new Cube(glm::vec3(-2.0f, -1.0f, -4.75f), glm::vec3(2.5f, -0.75f, -6.5f), white));

    // left ear
    objects.push_back(new Cube(glm::vec3(-1.0f, 1.0f, -0.5f), glm::vec3(-0.3f, 1.4f, -0.2f), straw));
    objects.push_back(new Cube(glm::vec3(-0.99f, 0.99f, -0.49f), glm::vec3(-0.299f, 1.39f, -0.23f), carbon));
    // upper cube left
    objects.push_back(new Cube(glm::vec3(-1.3f, 1.4f, -0.5f), glm::vec3(-0.6f, 1.8f, -0.2f), straw));
    objects.push_back(new Cube(glm::vec3(-1.29f, 1.4f, -0.49f), glm::vec3(-0.59f, 1.79f, -0.23f), carbon));
    // upper cube 2 left
    objects.push_back(new Cube(glm::vec3(-1.6f, 1.8f, -0.5f), glm::vec3(-0.9f, 2.2f, -0.2f), straw));
    objects.push_back(new Cube(glm::vec3(-1.59f, 1.79f, -0.49f), glm::vec3(-0.89f, 2.19f, -0.23f), carbon));

    // right ear
    objects.push_back(new Cube(glm::vec3(1.0f, 1.0f, -0.5f), glm::vec3(1.8f, 1.4f, -0.2f), straw));
    objects.push_back(new Cube(glm::vec3(0.99f, 0.99f, -0.49f), glm::vec3(1.79f, 1.39f, -0.23f), carbon));
    // upper cube right
    objects.push_back(new Cube(glm::vec3(1.3f, 1.4f, -0.5f), glm::vec3(2.0f, 1.8f, -0.2f), straw));
    objects.push_back(new Cube(glm::vec3(1.29f, 1.39f, -0.49f), glm::vec3(1.99f, 1.79f, -0.23f), carbon));
    // upper cube 2 right
    objects.push_back(new Cube(glm::vec3(1.6f, 1.8f, -0.5f), glm::vec3(2.3f, 2.2f, -0.2f), straw));
    objects.push_back(new Cube(glm::vec3(1.59f, 1.79f, -0.49f), glm::vec3(2.29f, 2.19f, -0.23f), carbon));

    // left gills up
    objects.push_back(new Cube(glm::vec3(-1.0f, 0.5f, -0.5f), glm::vec3(-1.8f, 0.1f, -0.2f), darkCoal));
    objects.push_back(new Cube(glm::vec3(-1.8f, 0.9f, -0.5f), glm::vec3(-2.2f, 0.5f, -0.2f), coal));
    objects.push_back(new Cube(glm::vec3(-2.2f, 1.3f, -0.5f), glm::vec3(-2.6f, 0.9f, -0.2f), darkCoal));

    // left gills down
    objects.push_back(new Cube(glm::vec3(-1.0f, -0.5f, -0.5f), glm::vec3(-1.8f, -0.1f, -0.2f), darkCoal));
    objects.push_back(new Cube(glm::vec3(-1.8f, -0.9f, -0.5f), glm::vec3(-2.2f, -0.5f, -0.2f), coal));
    objects.push_back(new Cube(glm::vec3(-2.2f, -1.3f, -0.5f), glm::vec3(-2.6f, -0.9f, -0.2f), darkCoal));

    // right gills up
    objects.push_back(new Cube(glm::vec3(1.6f, 0.5f, -0.5f), glm::vec3(2.4f, 0.1f, -0.2f), darkCoal));
    objects.push_back(new Cube(glm::vec3(2.4f, 0.9f, -0.5f), glm::vec3(2.8f, 0.5f, -0.2f), coal));
    objects.push_back(new Cube(glm::vec3(2.8f, 1.3f, -0.5f), glm::vec3(3.2f, 0.9f, -0.2f), darkCoal));

    // right gills down
    objects.push_back(new Cube(glm::vec3(1.6f, -0.5f, -0.5f), glm::vec3(2.4f, -0.1f, -0.2f), darkCoal));
    objects.push_back(new Cube(glm::vec3(2.4f, -0.9f, -0.5f), glm::vec3(2.8f, -0.5f, -0.2f), coal));
    objects.push_back(new Cube(glm::vec3(2.8f, -1.3f, -0.5f), glm::vec3(3.2f, -0.9f, -0.2f), darkCoal));
}

// pickles properties to draw block by block
void createPickles() {
// pickle 1
    // left
    objects.push_back(new Cube(glm::vec3(-5.0f, -4.7f, -0.5f), glm::vec3(-5.3f, -0.3f, -0.2f), mold));
    objects.push_back(new Cube(glm::vec3(-5.0f, -4.7f, -1.0f), glm::vec3(-5.3f, -0.3f, -0.2f), mold));
    objects.push_back(new Cube(glm::vec3(-5.0f, -4.7f, -1.5f), glm::vec3(-5.3f, -0.3f, -0.2f),grass));

    // right
    objects.push_back(new Cube(glm::vec3(-6.0f, -4.7f, -0.5f), glm::vec3(-6.3f, -0.3f, -0.2f), grass));
    objects.push_back(new Cube(glm::vec3(-6.0f, -4.7f, -1.0f), glm::vec3(-6.3f, -0.3f, -0.2f), mold));
    objects.push_back(new Cube(glm::vec3(-6.0f, -4.7f, -1.5f), glm::vec3(-6.3f, -0.3f, -0.2f), grass));

    // front
    objects.push_back(new Cube(glm::vec3(-4.9f, -4.7f, -0.25f), glm::vec3(-6.0f, -0.3f, 0.0f), mold));

    //back
    objects.push_back(new Cube(glm::vec3(-4.9f, -4.7f, -1.75f), glm::vec3(-6.0f, -0.3f, -1.5f), grass));

    // light
    objects.push_back(new Cube(glm::vec3(-6.0f, -0.3f, -0.75f), glm::vec3(-5.5f, 0.2f, -0.5f), lights));
    objects.push_back(new Cube(glm::vec3(-5.7f, -0.3f, -1.25f), glm::vec3(-5.2f, 0.2f, -1.0f), lights));

// pickle 2
    // left
    objects.push_back(new Cube(glm::vec3(5.0f, -4.7f, -0.5f), glm::vec3(5.3f, -0.3f, -0.2f), grass));
    objects.push_back(new Cube(glm::vec3(5.0f, -4.7f, -1.0f), glm::vec3(5.3f, -0.3f, -0.2f), mold));
    objects.push_back(new Cube(glm::vec3(5.0f, -4.7f, -1.5f), glm::vec3(5.3f, -0.3f, -0.2f), grass));

    // right
    objects.push_back(new Cube(glm::vec3(6.0f, -4.7f, -0.5f), glm::vec3(6.3f, -0.3f, -0.2f), mold));
    objects.push_back(new Cube(glm::vec3(6.0f, -4.7f, -1.0f), glm::vec3(6.3f, -0.3f, -0.2f), grass));
    objects.push_back(new Cube(glm::vec3(6.0f, -4.7f, -1.5f), glm::vec3(6.3f, -0.3f, -0.2f), mold));

    // front
    objects.push_back(new Cube(glm::vec3(4.9f, -4.7f, -0.25f), glm::vec3(6.0f, -0.3f, 0.0f), grass));

    // back
    objects.push_back(new Cube(glm::vec3(4.9f, -4.7f, -1.75f), glm::vec3(6.0f, -0.3f, -1.5f), mold));

    // light
    objects.push_back(new Cube(glm::vec3(6.0f, -0.3f, -0.75f), glm::vec3(5.5f, 0.2f, -0.5f), lights));
    objects.push_back(new Cube(glm::vec3(5.7f, -0.3f, -1.25f), glm::vec3(5.2f, 0.2f, -1.0f), lights));
}

// void method that calls the two figures of the scene
void setUp() {
    createAxolotl();
    createPickles();
}

// implementation of rendering logic
void render() {
    float fov = 3.1415/3;
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {

            float random_value = static_cast<float>(std::rand())/static_cast<float>(RAND_MAX);
            if (random_value < 0.0 ) {
                continue;
            }

            float screenX = (2.0f * (x + 0.5f)) / SCREEN_WIDTH - 1.0f;
            float screenY = -(2.0f * (y + 0.5f)) / SCREEN_HEIGHT + 1.0f;
            screenX *= ASPECT_RATIO;
            screenX *= tan(fov/2.0f);
            screenY *= tan(fov/2.0f);

            glm::vec3 cameraDir = glm::normalize(camera.target - camera.position);
            glm::vec3 cameraX = glm::normalize(glm::cross(cameraDir, camera.up));
            glm::vec3 cameraY = glm::normalize(glm::cross(cameraX, cameraDir));
            glm::vec3 rayDirection = glm::normalize(
                    cameraDir + cameraX * screenX + cameraY * screenY
            );

            Color pixelColor = castRay(camera.position, rayDirection);
            point(glm::vec2(x, y), pixelColor);
        }
    }
}

int main(int argc, char* argv[]) {
    // SDL and SDL_mixer initialization
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }

    Mix_Music* music = Mix_LoadMUS("src/assets/sounds/cards.wav");
    if (music == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }

    Mix_PlayMusic(music, -1);

    // SDL window creation
    SDL_Window* window = SDL_CreateWindow("Axolotls Like Pickles - Raytracing by bl33h",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    // initializations
    bool running = true;
    SDL_Event event;
    Uint32 currentTime = startTime;
    Uint32 startTime = SDL_GetTicks();
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    setUp();

    // main loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            // keys camera movement
            if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        camera.rotate(0.0f, 1.0f);
                        break;
                    case SDLK_DOWN:
                        camera.rotate(0.0f, -1.0f);
                        break;
                    case SDLK_LEFT:
                        camera.rotate(-1.0f, 0.0f);
                        break;
                    case SDLK_RIGHT:
                        camera.rotate(1.0f, 0.0f);
                        break;
                    case SDLK_w:
                        camera.move(1.0f);
                        break;
                    case SDLK_s:
                        camera.move(-1.0f);
                        break;
                }
            }

            // mousewheel zoom
            if (event.type == SDL_MOUSEWHEEL) {
            camera.processMouseScroll(event.wheel.y);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        render();
        SDL_RenderPresent(renderer);       
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}