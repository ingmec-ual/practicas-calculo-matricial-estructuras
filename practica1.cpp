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
#include <array>
#include "libcalculomatricial.h"
#include <iostream>

int main()
{
	using namespace Eigen;

	Eigen::Matrix<double,4,4> A = Eigen::Matrix4d::Random(4, 4);
	Eigen::Matrix<double,6,6> K = Eigen::Matrix<double,6,6>::Zero();

	K.block<3,3>(0,0) += indexing(A, std::array<int, 3>{ 0,1,3 }, std::array<int, 3>{ 0,1,3 });
	// TODO: Make an expression valid for lvalue!
	//indexing(K,std::array<int, 3>{ 0,1,3 }, std::array<int, 3>{ 0,1,3 }) = A.block<3,3>(0,0);

	std::cout << A << std::endl << std::endl;
	std::cout << K << std::endl;

	return 0; // el programa finaliza sin errores
}
