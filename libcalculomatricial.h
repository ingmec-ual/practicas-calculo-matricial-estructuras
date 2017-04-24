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

#define _USE_MATH_DEFINES
#include <cmath>  // M_PI, etc.

#include <Eigen/Dense>
#include "eigen_indexing.h"


namespace calcmat
{
	/** Genera la matriz de rigidez de una barra articulada-articulada con 4 GDL (coordenadas locales).
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

	/** Genera la matriz de rigidez de una barra rigida-rigida con 6 GDL (coordenadas locales).
	* \param[in] L Longitud de la barra [m]
	* \param[in] E Modulo de Yound [Pa]
	* \param[in] A Seccion de la barra [m^2]
	* \param[in] Iz Segundo momento de area ("inercia") [m^4]
	*
	* La salida se da en forma de las tres submatrices Kii, Kjj, Kij:
	*      [  Kii  |  Kij  ]
	*  K = [ ------+------ ]
	*      [ Kij^T |  Kjj  ]
	*/
	void matriz_barra_rig_rig(
		double L, double E, double A, double Iz,
		Eigen::Matrix3d & Kii,
		Eigen::Matrix3d & Kjj,
		Eigen::Matrix3d & Kij
	);

	/** Devuelve una matriz de rotacion 2x2 para el angulo ang:
	  *     [ cos(ang)  -sin(ang) ]
	  * R = [                     ]
	  *     [ sin(ang)   cos(ang) ]
	  */
	Eigen::Matrix2d matriz_rotacion2(double ang);

	/** Devuelve una matriz de rotacion 3x3 para el angulo ang:
	*     [ cos(ang)  -sin(ang)  0 ]
	* R = [ sin(ang)   cos(ang)  0 ]
	*     [    0         0       1 ]
	*/
	Eigen::Matrix3d matriz_rotacion3(double ang);


} // end namespace "calcmat"
