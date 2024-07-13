#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <chibi/eval.h>
#include "lib/test.h"
#include "lib/rscript.h"
#include "lib/math.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "dotlambda"

void dostuff(Rscript &rscript)
{
    sexp ctx = rscript.getContext();
    sexp env = rscript.getEnv();

    sexp update_handler = rscript.getProcFromName("update");
    if (update_handler != NULL)
    {
        sexp result_sexp = rscript.callProc(update_handler, sexp_list1(ctx, sexp_c_string(ctx, "hello from c++", -1)));

        char *response = sexp_stringp(result_sexp) ? sexp_string_data(result_sexp) : NULL;
        if (response)
        {
            std::cout << response << std::endl;
        }
        else
        {
            std::cout << "Got nothing" << std::endl;
        }
    }
    else
    {
        std::cout << "Not a procedure" << std::endl;
    }
}

int main()
{
    Rscript rscript("file.scm");

    sexp (*f)(sexp, sexp, sexp, sexp, sexp, sexp) = &Math::makeVector3;
    sexp (*g)(sexp ctx, sexp self, sexp n, sexp vec1, sexp vec2) = &Math::addVector3;
    sexp (*h)(sexp ctx, sexp self, sexp n, sexp vec1, sexp vec2) = &Math::multiplyVector3;

    rscript.bindProc3("make-vector3", 3, f);
    rscript.bindProc2("vector3+", 2, g);
    rscript.bindProc2("vector3*", 2, h);

    rscript.load();

    // sexp update = rscript.getProcFromName("update");
    // sexp draw = rscript.getProcFromName("draw");

    // if (!update || !draw)
    // {
    //     std::cout << "Could not find update or draw functions" << std::endl;
    //     return 1;
    // }

    // while (true)
    // {
    //     rscript.callProc(update, sexp_list1(rscript.getContext(), sexp_make_integer(rscript.getContext(), 30 / 1000)));
    //     rscript.callProc(draw, SEXP_NULL);
    // }

    return 0;
}
