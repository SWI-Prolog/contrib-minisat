#include <SWI-Stream.h>
#include <SWI-cpp.h>
#include <stdio.h>
#include <assert.h>

#if 0
#include <minisat/core/Solver.h>
using namespace Minisat;
#else
#include <Solver.h>
#endif

#define val(i) ((s->model[i] != l_Undef) ? ((s->model[i]==l_True)? i+1:-1*(i+1)):0)

/* FIXME: Allow a solver per thread
*/

static Solver *s = NULL;

PREDICATE0(minisat_new_solver)
{ s = new Solver;

  return TRUE;
}


PREDICATE0(minisat_delete_solver)
{ if (s)
  { delete s;
    s = NULL;
  }

  return TRUE;
}


static inline Lit
pl2lit(PlTerm pl_literal)
{ int pl_lit_int = pl_literal;
  int var;

  var = abs(pl_lit_int)-1;

  while( var >= s->nVars() )
    s->newVar();

#if 0
  mkLit(var, pl_lit_int > 0);
#else
  return pl_lit_int > 0 ? Lit(var) : ~Lit(var);
#endif
}


PREDICATE(minisat_set_minvars, 1)
{ PlTail tail(A1);
  PlTerm head;

  vec<Lit> lits;

  while( tail.next(head) )
    lits.push(pl2lit(head));

  return s->setminVars(lits) != 0;
}

PREDICATE(minisat_add_clause, 1)
{ PlTail tail(A1);
  PlTerm head;

  vec<Lit> lits;

  while( tail.next(head) )
    lits.push( pl2lit(head) );

  return s->addClause(lits) != 0;
}


PREDICATE(minisat_solve, 1)
{ PlTail tail(A1);
  PlTerm head;

  vec<Lit> assumptions;

  while( tail.next(head) )
    assumptions.push( pl2lit(head) );

  return s->solve(assumptions) != 0;
}


PREDICATE(minisat_get_var_assignment, 2)
{ int i = A1;

  i--;

  if ( i < s->nVars() )
    return (A2 = val(i));
  else
    return FALSE;
}


PREDICATE(minisat_nvars, 1)
{ return (A1 = s->nVars());
}
