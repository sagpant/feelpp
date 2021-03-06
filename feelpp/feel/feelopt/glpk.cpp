/* -*- mode: c++; coding: utf-8; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; show-trailing-whitespace: t -*-*/

#include <feel/feelcore/environment.hpp>
#include <feel/feelopt/glpk.hpp>


namespace Feel
{
namespace opt
{

OptimizationLinearProgramming::OptimizationLinearProgramming(int direction, std::string name)
{
    M_pb = glp_create_prob();
    glp_set_prob_name( M_pb, name.c_str() );
    glp_set_obj_dir( M_pb, direction );
    M_params = new glp_smcp;
    glp_init_smcp(M_params);
    M_params->msg_lev = ioption("glpk.verbosity");
    M_params->meth = ioption("glpk.method");
    M_params->tol_bnd = doption("glpk.tolerance-bounds");
    M_params->tol_dj = doption("glpk.tolerance-dual");
    M_params->tol_piv = doption("glpk.tolerance-pivot");
    M_params->it_lim = ioption("glpk.iteration-limit");
    M_params->tm_lim = ioption("glpk.time-limit");
    M_params->presolve = ioption("glpk.presolve");
    M_scaling = ioption("glpk.scaling");
}

OptimizationLinearProgramming::~OptimizationLinearProgramming()
{
    glp_delete_prob(M_pb);
}

int OptimizationLinearProgramming::solve()
{
    glp_scale_prob(M_pb, M_scaling);
    return glp_simplex(M_pb, M_params);
}

void OptimizationLinearProgramming::addRow(std::string name, int type, double lb, double ub)
{
    int r = glp_add_rows( M_pb, 1);
    glp_set_row_name( M_pb, r, name.c_str() );
    glp_set_row_bnds( M_pb, r, type, lb, ub );
}

void OptimizationLinearProgramming::addColumn(std::string name, double coef, int type, double lb, double ub)
{
    int c = glp_add_cols( M_pb, 1);
    glp_set_col_name( M_pb, c, name.c_str() );
    glp_set_col_bnds( M_pb, c, type, lb, ub );
    glp_set_obj_coef( M_pb, c, coef );
}

void OptimizationLinearProgramming::setMatrix(std::vector<std::vector<double> > matrix)
{
    int k = 1;
    int R = matrix.size();
    if( R == 0 )
        return;
    int C = matrix[0].size();
    int ia[1+C*R], ja[1+C*R];
    double ar[1+C*R];
    for( int r = 0; r < R; ++r)
    {
        for( int c = 0; c < C; ++c)
        {
            ia[k] = r+1;
            ja[k] = c+1;
            ar[k] = matrix[r][c];
            ++k;
        }
    }
    glp_load_matrix( M_pb, C*R, ia, ja, ar );
}

double OptimizationLinearProgramming::getObjectiveValue()
{
    return glp_get_obj_val(M_pb);
}

double OptimizationLinearProgramming::getColumnPrimalValue(int i)
{
    return glp_get_col_prim( M_pb, i );
}

std::string OptimizationLinearProgramming::check(int e)
{
    std::string s;
    switch(e)
    {
    case 0:
        s = "The LP problem instance has been successfully solved.";
        break;
    case GLP_EBADB:
        s = "Unable to start the search, because the initial basis specified in the problem object is invalid—the number of basic (auxiliary and structural) variables is not the same as the number of rows in the problem object.";
        break;
    case GLP_ESING:
        s = "Unable to start the search, because the basis matrix corresponding to the initial basis is singular within the working precision.";
        break;
    case GLP_ECOND:
        s = "Unable to start the search, because the basis matrix corresponding to the initial basis is ill-conditioned, i.e. its condition number is too large.";
        break;
    case GLP_EBOUND:
        s = "Unable to start the search, because some double-bounded (auxiliary or structural) variables have incorrect bounds.";
        break;
    case GLP_EFAIL:
        s = "The search was prematurely terminated due to the solver failure.";
        break;
    case GLP_EOBJLL:
        s = "The search was prematurely terminated, because the objective function being maximized has reached its lower limit and continues decreasing (the dual simplex only).";
        break;
    case GLP_EOBJUL:
        s = "The search was prematurely terminated, because the objective function being minimized has reached its upper limit and continues increasing (the dual simplex only).";
        break;
    case GLP_EITLIM:
        s = "The search was prematurely terminated, because the simplex iteration limit has been exceeded.";
        break;
    case GLP_ETMLIM:
        s = "The search was prematurely terminated, because the time limit has been exceeded.";
        break;
    case GLP_ENOPFS:
        s = "The LP problem instance has no primal feasible solution (only if the LP presolver is used).";
        break;
    case GLP_ENODFS:
        s = "The LP problem instance has no dual feasible solution (only if the LP presolver is used).";
        break;
    default:
        s = "Unknown state " + std::to_string(e);
        break;
    }
    return s;
}

FeelGlpkException::FeelGlpkException(int e) : std::exception(), M_e(e) {}

const char* FeelGlpkException::what() const noexcept
{
    return OptimizationLinearProgramming::check(M_e).c_str();
}


} // namespace opt
} // namespace Feel
