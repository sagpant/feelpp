###  TEMPLATE.txt.tpl; coding: utf-8 ---

#  Author(s): Christophe Prud'homme <christophe.prudhomme@feelpp.org>
#       Date: 2013-09-29
#
#  Copyright (C) 2013 Universite de Strasbourg
#
# Distributed under the GPL(GNU Public License):
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
#
set_directory_properties(PROPERTIES LABEL testintegration )
feelpp_add_test( auto_order_integrate )
feelpp_add_test( integration )
feelpp_add_test( integration_ginac )
feelpp_add_test( integration_ho GEO test_integration_ho_geometry.geo )
feelpp_add_test( integration_ifaces )
feelpp_add_test( integration_opt )
feelpp_add_test( integration_relatedmesh )
feelpp_add_test( integration_on_manifolds )
