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

#include <Eigen/Dense>
#include "eigen_indexing.h"

namespace calcmat
{
	/** Genera la matriz de rigidez de una barra articulada-articulada con 4 GDL.
	* \param[in] L Longitud de la barra [m]
	* \param[in] E Modulo de Yound [Pa]
	* \param[in] A Seccion de la barra [m^2]
	*
	* La salida se da en forma de las tres submatrices Kii, Kjj, Kij:
	*      [  Kii  |  Kij  ]
	*  K = [ ------+------ ]
	*      [ Kij^T |  Kjj  ]
	*/
	void matriz_barra_art_art(
		double L, double E, double A,
		Eigen::Matrix2d & Kii,
		Eigen::Matrix2d & Kjj,
		Eigen::Matrix2d & Kij
	);
	




} // end namespace "calcmat"
