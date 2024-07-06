#include "test.h"

Test::Test()
{
    this->a = 1;
}

Test::Test(int a)
{
    this->a = a;
}

int Test::getA()
{
    return a;
}

sexp Test::sexp_finalize_Test_type(sexp ctx, sexp self, sexp_sint_t n, sexp obj)
{
    if (sexp_cpointer_freep(obj))
        delete sexp_cpointer_value(obj);
    return SEXP_VOID;
}

sexp Test::make(sexp ctx, sexp self, sexp n, sexp init_a)
{
    sexp c_type = sexp_register_c_type(ctx, sexp_c_string(ctx, "test", -1), sexp_finalize_Test_type);
    Test *test = !sexp_numberp(init_a) ? new Test() : new Test((int)sexp_to_double(ctx, init_a));
    return sexp_make_cpointer(ctx, sexp_type_tag(c_type), test, SEXP_NULL, 1);
}

sexp Test::test_get_a(sexp ctx, sexp self, sexp n, sexp test_instance)
{
    sexp test_instance_type = sexp_lookup_type(ctx, sexp_c_string(ctx, "test", -1), test_instance->value.type.name);
    if (test_instance_type == SEXP_FALSE || strcmp(sexp_string_data(sexp_type_name(test_instance_type)), "test") != 0)
    {
        return SEXP_VOID;
    }

    Test *test = (Test *)test_instance->value.cpointer.value;
    return sexp_make_integer(ctx, test->getA());
}
