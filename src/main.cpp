#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <raylib-cpp.hpp>

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

#define WINDOW_TITLE "dotlambda"
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

int main()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT); // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 25.0f, -100.0f};
    camera.target = (Vector3){0.0f, 15.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Camera3D camera_shadow_map = {0};
    camera_shadow_map.fovy = 20.0f;
    camera_shadow_map.target = (Vector3){.0f, .0f, .0f};
    camera_shadow_map.position = (Vector3){0.0f, 10.0f, 0.0f};
    camera_shadow_map.up = (Vector3){0.0f, 0.0f,-1.0f};
    camera_shadow_map.projection = CAMERA_PERSPECTIVE;

    RenderTexture2D render_texture = LoadRenderTexture(160, 100);

    Shader shader_default = {0};
    Shader shader = LoadShader(TextFormat(ASSETS_PATH "resources/shaders/glsl%i/lighting.vs", GLSL_VERSION),
                               TextFormat(ASSETS_PATH "resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));

    // Get some required shader locations
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    // Ambient light level (some basic lighting)
    int ambientLoc = GetShaderLocation(shader, "ambient");
    float ambient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
    SetShaderValue(shader, ambientLoc, &ambient, SHADER_UNIFORM_VEC4);

    ////////////////////////////////////////////
    // Ground
    ////////////////////////////////////////////
    Model ground = LoadModelFromMesh(GenMeshCube(100, 50, 100));

    ////////////////////////////////////////////
    // Sphere
    ////////////////////////////////////////////
    Model sphere = LoadModelFromMesh(GenMeshSphere(5, 10, 10));

    shader_default = sphere.materials[0].shader;

    sphere.materials[0].shader = shader;
    ground.materials[0].shader = shader;
    ground.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = render_texture.texture;

    Light sun1 = CreateLight(LIGHT_POINT, (Vector3){50, 50, 0}, Vector3Zero(), WHITE, shader);
    Light sun2 = CreateLight(LIGHT_POINT, (Vector3){-50, 50, 0}, Vector3Zero(), WHITE, shader);
    Light sun3 = CreateLight(LIGHT_POINT, (Vector3){0, 50, 50}, Vector3Zero(), WHITE, shader);
    Light sun4 = CreateLight(LIGHT_POINT, (Vector3){0, 50, -50}, Vector3Zero(), WHITE, shader);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawFPS(10, 10);

        Vector3 spherePosition = {0, 10, 0};
        Vector3 groundPosition = {0, -25, 0};

        BeginTextureMode(render_texture);
        {
            ClearBackground(GRAY);
            BeginMode3D(camera_shadow_map);
            {
                DrawModel(sphere, spherePosition, 1, DARKGRAY);
            }
            EndMode3D();
        }
        EndTextureMode();

        BeginMode3D(camera);
        {

            DrawModel(sphere, spherePosition, 1, GREEN);
            DrawModel(ground, groundPosition, 1, WHITE);

            // DrawGrid(100, 1.0f);
        }
        EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    UnloadModel(sphere);
    UnloadModel(ground);
    UnloadShader(shader);

    return 0;
}
