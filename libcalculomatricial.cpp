/******************************************************************************
Prácticas de cálculo matricial de estructuras
https://github.com/ingmec-ual/practicas-calculo-matricial-estructuras

Copyright 2017 - Jose Luis Blanco Claraco <jlblanco@ual.es>
University of Almeria
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.
Complete BSD-3-clause License: https://opensource.org/licenses/BSD-3-Clause
******************************************************************************/

#include "libcalculomatricial.h"

// Las formulas teoricas pueden consultarse en el libro:
//  Claraco, J. L. B., González, A., & Ocaña, J. M. G. M. (2012). Análisis estático de estructuras por el método matricial. Servicio de Publicaciones e Intercambio Científico de la Universidad de Málaga.
// http://ingmec.ual.es/~jlblanco/papers/blanco2012calculo_matricial_estructuras.pdf


// Matriz para barra articulada-articulada. Ver documentacion en el .h
void calcmat::matriz_barra_art_art(
	double L, double E, double A,
	Eigen::Matrix2d & Kii,
	Eigen::Matrix2d & Kjj,
	Eigen::Matrix2d & Kij
)
{
	// Submatrices en locales:
	Kii <<
		E*A / L, 0,
		0, 0;
	Kjj = Kii;
	Kij <<
		-E*A / L, 0,
		0, 0;
}

// Matriz para barra rigida-rigida. Ver documentacion en el .h
void calcmat::matriz_barra_rig_rig(double L, double E, double A, double Iz, Eigen::Matrix3d & Kii, Eigen::Matrix3d & Kjj, Eigen::Matrix3d & Kij)
{
	const double L2 = L*L, L3 = L2*L, EI = E*Iz, EA = E*A;
	
	// Submatrices en locales:
	Kii <<
		EA/L , 0        , 0        ,
		0    , 12*EI/L3 , 6*EI/L2  ,
		0    , 6*EI/L2  , 4*EI/L;
	Kjj <<
		EA/L , 0        , 0        ,
		0    , 12*EI/L3 , -6*EI/L2  ,
		0    , -6*EI/L2  , 4*EI/L;
	Kij <<
		-EA/L , 0        , 0        ,
		0    , -12*EI/L3 , 6*EI/L2  ,
		0    , -6*EI/L2  , 2*EI/L;
}

// Ver documentacion en el.h
Eigen::Matrix2d calcmat::matriz_rotacion2(double ang)
{
	Eigen::Matrix2d R;
	R <<
		cos(ang), -sin(ang),
		sin(ang), cos(ang);
	return R;
}

// Ver documentacion en el.h
Eigen::Matrix3d calcmat::matriz_rotacion3(double ang) 
{
	Eigen::Matrix3d R;
	R <<
		cos(ang), -sin(ang), 0,
		sin(ang), cos(ang), 0,
		0, 0, 1;
	return R;
}

