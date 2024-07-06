#include "rscript.h"

Rscript::Rscript(const char *path)
{
    sexp_scheme_init();

    this->script_path = path;
    this->ctx = sexp_make_eval_context(NULL, NULL, NULL, 0, 0);

    // define R7RS standard
    sexp_load_standard_env(ctx, NULL, SEXP_SEVEN);

    // set ports to stdout/stdin/stderr to be overridden later
    sexp_load_standard_ports(ctx, NULL, stdin, stdout, stderr, 1);

    this->env = sexp_context_env(ctx);
}

sexp Rscript::bindProc0(const char *name, int num_args, sexp (*f)(sexp, sexp, sexp))
{
    return sexp_define_foreign(this->ctx, this->env, name, num_args, f);
}

sexp Rscript::bindProc1(const char *name, int num_args, sexp (*f)(sexp, sexp, sexp, sexp))
{
    return sexp_define_foreign(this->ctx, this->env, name, num_args, f);
}

sexp Rscript::bindProcOpt1(const char *name, int num_args, sexp (*f)(sexp, sexp, sexp, sexp))
{
    return sexp_define_foreign_opt(this->ctx, this->env, name, num_args, f, SEXP_NULL);
}

sexp Rscript::getProcFromName(const char *name)
{
    sexp ref = sexp_env_ref(this->ctx, this->env, sexp_intern(ctx, name, -1), SEXP_FALSE);
    return sexp_procedurep(ref) ? ref : NULL;
}

sexp Rscript::callProc(sexp proc, sexp args)
{
    return sexp_apply(ctx, proc, args);
}

void Rscript::load()
{
    this->script = sexp_load(this->ctx, sexp_c_string(this->ctx, this->script_path, -1), this->env);
}

Rscript::~Rscript()
{
    sexp_destroy_context(this->ctx);
}
