//! -*- mode: c++; coding: utf-8; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; show-trailing-whitespace: t  -*- vim:fenc=utf-8:ft=cpp:et:sw=4:ts=4:sts=4
//!
//! This file is part of the Feel++ library
//!
//! This library is free software; you can redistribute it and/or
//! modify it under the terms of the GNU Lesser General Public
//! License as published by the Free Software Foundation; either
//! version 2.1 of the License, or (at your option) any later version.
//!
//! This library is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//! Lesser General Public License for more details.
//!
//! You should have received a copy of the GNU Lesser General Public
//! License along with this library; if not, write to the Free Software
//! Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//!
//! @file
//! @author Christophe Prud'homme <christophe.prudhomme@feelpp.org>
//! @date 15 Jun 2017
//! @copyright 2017 Feel++ Consortium
//!
#include <pybind11/pybind11.h>
#include <feel/feelinfo.h>
#include <feel/feelcore/info.hpp>



#define stringize2(x) #x
#define stringize(x) stringize2(x)

namespace py = pybind11;

void export_core( py::module& );
void export_crb( py::module& );
PYBIND11_PLUGIN(pyfeelpp)
{
    py::module m("pyfeelpp", R"pbdoc(
        PyFeelpp Module plugin
        ----------------------
        .. currentmodule:: pyfeelpp
        .. autosummary::
           :toctree: _generate
    )pbdoc");

#ifdef FEELPP_VERSION_STRING
    m.attr("__version__") = py::str(stringize(FEELPP_VERSION_STRING));
#else
    m.attr("__version__") = py::str("develop");
#endif

    export_core(m);
    export_crb(m);
    
    return m.ptr();
}
#if 0
void export_core();
void export_crb();
BOOST_PYTHON_MODULE( libfeelppy )
{
    export_core();
    export_crb();
}
#endif