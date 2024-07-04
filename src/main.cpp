#include <raylib.h>
#include <raymath.h>
#include <chibi/eval.h>
#include "lib/scene.h"
#include <iostream>
#include "lib/rscript.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "dotlambda"

using namespace std;

void dostuff(Rscript &rscript)
{
    sexp ctx = rscript.getContext();
    sexp env = rscript.getEnv();

    sexp update_handler = rscript.getProcFromName("update");
    if (update_handler != NULL)
    {
        sexp args = sexp_list1(ctx, sexp_c_string(ctx, "hello", -1));
        sexp result_sexp = sexp_apply(ctx, update_handler, args);

        char *response = sexp_stringp(result_sexp) ? sexp_string_data(result_sexp) : NULL;
        if (response)
        {
            cout << response << endl;
        }
        else
        {
            cout << "Got nothing" << endl;
        }
    }
    else
    {
        cout << "Not a procedure" << endl;
    }
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

class Test
{
public:
    int a;
    Test()
    {
        this->a = 1;
    }

    Test(int a)
    {
        this->a = a;
    }

    int getA()
    {
        return a;
    }
};

sexp sexp_finalize_Test_type(sexp ctx, sexp self, sexp_sint_t n, sexp obj)
{
    if (sexp_cpointer_freep(obj))
        delete sexp_cpointer_value(obj);
    return SEXP_VOID;
}

sexp make_test(sexp ctx, sexp self, sexp n, sexp init_a)
{
    sexp c_type = sexp_register_c_type(ctx, sexp_c_string(ctx, "test", -1), sexp_finalize_Test_type);
    Test *test = !sexp_numberp(init_a) ? new Test() : new Test((int)sexp_to_double(ctx, init_a));
    return sexp_make_cpointer(ctx, sexp_type_tag(c_type), test, SEXP_NULL, 1);
}

sexp test_get_a(sexp ctx, sexp self, sexp n, sexp test_instance)
{
    sexp test_instance_type = sexp_lookup_type(ctx, sexp_c_string(ctx, "test", -1), test_instance->value.type.name);
    if (test_instance_type == SEXP_FALSE || strcmp(sexp_string_data(sexp_type_name(test_instance_type)), "test") != 0)
    {
        return SEXP_VOID;
    }

    Test *test = (Test *)test_instance->value.cpointer.value;
    return sexp_make_integer(ctx, test->getA());
}

sexp custom_fn(sexp ctx, sexp self, sexp n)
{
    return sexp_c_string(ctx, "Hello from C++!\n", -1);
}

int main()
{
    Rscript rscript("file.scm");

    rscript.bindProc0("hello", 0, custom_fn);
    rscript.bindProcOpt1("make-test", 1, make_test);
    rscript.bindProc1("test->a", 1, test_get_a);

    rscript.load();

    return 0;
}
