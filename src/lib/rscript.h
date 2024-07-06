#include <chibi/eval.h>

class Rscript
{
private:
    sexp ctx;
    sexp env;
    sexp script;
    const char* script_path;

public:
    Rscript(const char* path);
    void load();

    sexp bindProc0(const char* name, int num_args, sexp (*f)(sexp, sexp, sexp));
    sexp bindProc1(const char* name, int num_args, sexp (*f)(sexp, sexp, sexp, sexp));
    sexp bindProcOpt1(const char* name, int num_args, sexp (*f)(sexp, sexp, sexp, sexp));
    sexp bindProc2(const char* name, int num_args, sexp (*f)(sexp, sexp, sexp, sexp, sexp));
    sexp bindProc3(const char* name, int num_args, sexp (*f)(sexp, sexp, sexp, sexp, sexp, sexp));
    sexp bindProc4(const char* name, int num_args, sexp (*f)(sexp, sexp, sexp, sexp, sexp, sexp, sexp));

    sexp getProcFromName(const char* name);
    sexp callProc(sexp proc, sexp args);

    sexp getContext() { return this->ctx; }
    sexp getEnv() { return this->env; }

    ~Rscript();
};
