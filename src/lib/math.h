#include <chibi/eval.h>
#include <raylib.h>
#include <raymath.h>

class Math
{
public:
    static sexp sexp_finalize_raylib_type(sexp ctx, sexp self, sexp_sint_t n, sexp obj)
    {
        if (sexp_cpointer_freep(obj))
            delete sexp_cpointer_value(obj);
        return SEXP_VOID;
    }

    static bool isVector3(sexp ctx, sexp vec)
    {
        sexp vec_instance_type = sexp_lookup_type(ctx, sexp_c_string(ctx, "vector3", -1), vec->value.type.name);
        return vec_instance_type != SEXP_FALSE && strcmp(sexp_string_data(sexp_type_name(vec_instance_type)), "vector3") == 0;
    }

    static Vector3 *toVector3(sexp ctx, sexp vec)
    {
        if (!isVector3(ctx, vec))
        {
            return NULL;
        }
        return (Vector3 *)vec->value.cpointer.value;
    }

    static sexp makeVector3(sexp ctx, sexp self, sexp n, sexp x, sexp y, sexp z)
    {
        sexp vec_type = sexp_register_c_type(ctx, sexp_c_string(ctx, "vector3", -1), sexp_finalize_raylib_type);

        float nx = 0;
        float ny = 0;
        float nz = 0;

        if (x != SEXP_NULL)
        {
            nx = (float)sexp_to_double(ctx, x);
        }

        if (y != SEXP_NULL)
        {
            ny = (float)sexp_to_double(ctx, y);
        }

        if (z != SEXP_NULL)
        {
            nz = (float)sexp_to_double(ctx, z);
        }

        Vector3 *vec = new Vector3({nx, ny, nz});

        return sexp_make_cpointer(ctx, sexp_type_tag(vec_type), vec, SEXP_NULL, 1);
    }

    static sexp addVector3(sexp ctx, sexp self, sexp n, sexp vec1, sexp vec2)
    {
        Vector3 *rvec1;
        Vector3 *rvec2;

        rvec1 = toVector3(ctx, vec1);
        rvec2 = toVector3(ctx, vec2);

        if (!rvec1 || !rvec2)
        {
            return SEXP_FALSE;
        }

        Vector3 res = Vector3Add(*rvec1, *rvec2);
        return makeVector3(ctx, self, sexp_make_fixnum(-1), sexp_make_flonum(ctx, res.x), sexp_make_flonum(ctx, res.y), sexp_make_flonum(ctx, res.z));
    }

    static sexp multiplyVector3(sexp ctx, sexp self, sexp n, sexp vec1, sexp vec2)
    {
        Vector3 *rvec1;
        Vector3 *rvec2;

        rvec1 = toVector3(ctx, vec1);
        rvec2 = toVector3(ctx, vec2);

        if (!rvec1 || !rvec2)
        {
            return SEXP_FALSE;
        }

        Vector3 res = Vector3Multiply(*rvec1, *rvec2);
        return makeVector3(ctx, self, sexp_make_fixnum(-1), sexp_make_flonum(ctx, res.x), sexp_make_flonum(ctx, res.y), sexp_make_flonum(ctx, res.z));
    }
};
