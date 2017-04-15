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
#include <iostream>

int main()
{
	Eigen::Matrix3d M = Eigen::Matrix3d::Identity();
	std::cout << "Matriz identidad I_3:" << std::endl << M << std::endl;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			M(i, j) += i+j;
		}
	}

	std::cout << "Matriz M:" << std::endl << M << std::endl;
	std::cout << "Inversa de la matriz M:" << std::endl << M.inverse() << std::endl;

	return 0; // el programa finaliza sin errores
}
