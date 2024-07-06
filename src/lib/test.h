#include <chibi/eval.h>

class Test
{
private:
    int a;

public:
    Test();
    Test(int a);
    int getA();

    static sexp sexp_finalize_Test_type(sexp ctx, sexp self, sexp_sint_t n, sexp obj);

    static sexp make(sexp ctx, sexp self, sexp n, sexp init_a);

    static sexp test_get_a(sexp ctx, sexp self, sexp n, sexp test_instance);
};
