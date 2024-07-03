#include <raylib.h>
#include <raymath.h>
#include <chibi/eval.h>
#include "lib/scene.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "dotlambda"

void dostuff(sexp ctx) {
  /* declare and preserve local variables */
  sexp_gc_var2(obj1, obj2);
  sexp_gc_preserve2(ctx, obj1, obj2);

  /* load a file containing Scheme code */
  obj1 = sexp_c_string(ctx, "file.scm", -1);
  sexp_load(ctx, obj1, NULL);

  /* eval a C string as Scheme code */
  sexp_eval_string(ctx, "(some scheme expression)", -1, NULL);

  /* construct a Scheme expression to eval */
  obj1 = sexp_intern(ctx, "my-procedure", -1);
  obj2 = sexp_cons(ctx, obj1, SEXP_NULL);
  sexp_eval(ctx, obj2, NULL);

  /* release the local variables */
  sexp_gc_release2(ctx);
}

// void start_engine() {
//        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

//     Camera3D camera = {0};
//     camera.position = (Vector3){0.0f, 10.0f, -25.0f};
//     camera.target = (Vector3){0.0f, 0.0f, 0.0f};
//     camera.up = (Vector3){0.0f, 1.0f, 0.0f};
//     camera.fovy = 45.0f;
//     camera.projection = CAMERA_PERSPECTIVE;

//     Vector3 cubePosition = {0.0f, 0.0f, 0.0f};
//     Vector3 spherePosition = {5.0f, 0.0f, 0.0f};

//     Model model = LoadModel(ASSETS_PATH "plane.obj");
//     Texture2D texture = LoadTexture(ASSETS_PATH "plane_diffuse.png");

//     model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

//     float pitch = 0.0f;
//     float roll = 0.0f;
//     float yaw = 0.0f;

//     SetTargetFPS(60);

//     while (!WindowShouldClose())
//     {
//         UpdateCamera(&camera, CAMERA_ORBITAL);

//         if (IsKeyDown(KEY_DOWN))
//             pitch += 0.6f;
//         else if (IsKeyDown(KEY_UP))
//             pitch -= 0.6f;
//         else
//         {
//             if (pitch > 0.3f)
//                 pitch -= 0.3f;
//             else if (pitch < -0.3f)
//                 pitch += 0.3f;
//         }

//         // Plane yaw (y-axis) controls
//         if (IsKeyDown(KEY_S))
//             yaw -= 1.0f;
//         else if (IsKeyDown(KEY_A))
//             yaw += 1.0f;
//         else
//         {
//             if (yaw > 0.0f)
//                 yaw -= 0.5f;
//             else if (yaw < 0.0f)
//                 yaw += 0.5f;
//         }

//         // Plane roll (z-axis) controls
//         if (IsKeyDown(KEY_LEFT))
//             roll -= 1.0f;
//         else if (IsKeyDown(KEY_RIGHT))
//             roll += 1.0f;
//         else
//         {
//             if (roll > 0.0f)
//                 roll -= 0.5f;
//             else if (roll < 0.0f)
//                 roll += 0.5f;
//         }

//         // Reset camera lookat
//         // if (IsKeyDown('Z'))
//         // {
//         //     camera.target = (Vector3){0.0f, 0.0f, 0.0f};
//         // }

//         model.transform = MatrixRotateXYZ((Vector3){DEG2RAD * pitch, DEG2RAD * yaw, DEG2RAD * roll});

//         BeginDrawing();

//         ClearBackground(RAYWHITE);

//         BeginMode3D(camera);
//         {
//             DrawModel(model, cubePosition, 1.0f, WHITE);
//             DrawGrid(20, 1.0f);
//         }
//         EndMode3D();

//         EndDrawing();
//     }

//     UnloadModel(model);
//     CloseWindow();
// }

int main()
{
    sexp ctx;
    sexp_scheme_init();
    ctx = sexp_make_eval_context(NULL, NULL, NULL, 0, 0);
    sexp_load_standard_env(ctx, NULL, SEXP_SEVEN);
    sexp_load_standard_ports(ctx, NULL, stdin, stdout, stderr, 1);
    dostuff(ctx);
    sexp_destroy_context(ctx);

    return 0;
}
