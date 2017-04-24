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
#include <Eigen/Dense>
#include <iostream>

int main()
{
	try 
	{
		const double E = 200*1e9; // Modulo de Young (Pa)
		const double A = 2*1e-4;  // Area (m^2)

		// Matrices de rigidez de las barras individuales en 
		// coordenadas LOCALES, y convertir a globales usando:
		// T*K*T' = 
		//  [Ri*Kii*Rit, Ri*Kij*Rjt]
		//  [Rj*Kji*Rit, Rj*Kjj*Rjt]
		// -----------------------------------------------
		// barra a:
		Eigen::Matrix2d Ka_11_loc, Ka_12_loc, Ka_22_loc, Ka_11, Ka_12, Ka_22;
		calcmat::matriz_barra_art_art(0.5 /*L*/, E, A, Ka_11_loc /*Kii*/, Ka_22_loc /*Kjj*/, Ka_12_loc /*Kij*/);
		const double ang_a = 0.0 * M_PI / 180;

		{
			const auto Ra_i = calcmat::matriz_rotacion2(ang_a), Ra_j = Ra_i;  // En este caso Ri=Rj al ser ambas de 2x2
			Ka_11 = Ra_i*Ka_11_loc*Ra_i.transpose();
			Ka_22 = Ra_j*Ka_22_loc*Ra_j.transpose();
			Ka_12 = Ra_i*Ka_12_loc*Ra_j.transpose();
		}

		// barra b:
		Eigen::Matrix2d Kb_11_loc, Kb_13_loc, Kb_33_loc, Kb_11, Kb_13, Kb_33;
		calcmat::matriz_barra_art_art(1.0 /*L*/, E, A, Kb_11_loc /*Kii*/, Kb_33_loc /*Kjj*/, Kb_13_loc /*Kij*/);
		const double ang_b = 90.0 * M_PI / 180;

		{
			const auto Rb_i = calcmat::matriz_rotacion2(ang_b), Rb_j = Rb_i;  // En este caso Ri=Rj al ser ambas de 2x2
			Kb_11 = Rb_i*Kb_11_loc*Rb_i.transpose();
			Kb_33 = Rb_j*Kb_33_loc*Rb_j.transpose();
			Kb_13 = Rb_i*Kb_13_loc*Rb_j.transpose();
		}

		// barra c:
		Eigen::Matrix2d Kc_22_loc, Kc_23_loc, Kc_33_loc, Kc_22, Kc_23, Kc_33;
		calcmat::matriz_barra_art_art( hypot(0.5,1.0) /*L*/, E, A, Kc_22_loc /*Kii*/, Kc_33_loc /*Kjj*/, Kc_23_loc /*Kij*/);
		const double ang_c = atan2(1.0 /*y*/, -0.5 /*x*/);

		{
			const auto R23i = calcmat::matriz_rotacion2(ang_c), R23j = R23i;  // En este caso Ri=Rj al ser ambas de 2x2
			Kc_22 = R23i*Kc_22_loc*R23i.transpose();
			Kc_33 = R23j*Kc_33_loc*R23j.transpose();
			Kc_23 = R23i*Kc_23_loc*R23j.transpose();
		}

		// Ensamblar la matriz de rigidez de la estructura:
		// -----------------------------------------------
		Eigen::Matrix<double, 6, 6> K;
		K.setZero(); // Initializa a todo ceros

		K.block<2, 2>(0, 0) = Ka_11 + Kb_11;
		K.block<2, 2>(2, 2) = Ka_22 + Kc_22;
		K.block<2, 2>(4, 4) = Kb_33 + Kc_33;

		K.block<2, 2>(0, 2) = Ka_12;
		K.block<2, 2>(2, 0) = Ka_12.transpose();

		K.block<2, 2>(0, 4) = Kb_13;
		K.block<2, 2>(4, 0) = Kb_13.transpose();

		K.block<2, 2>(2, 4) = Kc_23;
		K.block<2, 2>(4, 2) = Kc_23.transpose();

		std::cout << "K:\n" << K << std::endl << std::endl;

		// Resolver:
		//  UL = KLL^{-1} * ( FL - KLR * UR )
		//  FR = KRR * UR + KRL * UL
		// -----------------------------------------------
		const std::array<int, 3> idxs_R = {0,1,3}; // gdl "restringidos"
		const std::array<int, 3> idxs_L = {2,4,5}; // gdl "libres"

		const auto KLL = indexing(K, idxs_L, idxs_L);
		const auto KRR = indexing(K, idxs_R, idxs_R);
		const auto KLR = indexing(K, idxs_L, idxs_R);
		const auto KRL = KLR.transpose();

		Eigen::Matrix<double, 3, 1> FL; // Cargas en gdl "libres"
		FL << 0, 1000, 0;

		Eigen::Matrix<double, 3, 1> UR; // Desplazamientos en gdl "restringidos" (apoyos)
		UR << 0,0,0;

		// UL = KLL^{-1} * ( FL - KLR * UR )
		const Eigen::Matrix<double, 3, 1> UL = KLL.colPivHouseholderQr().solve( FL - KLR*UR );

		// FR = KRR * UR + KRL * UL
		const Eigen::Matrix<double, 3, 1>  FR = KRR * UR + KRL * UL;

		// Ensamblar vector U completo:
		Eigen::Matrix<double, 6, 1>  U;
		indexing(U, idxs_L) = UL;
		indexing(U, idxs_R) = UR;

		std::cout << "UL: " << UL.transpose() << std::endl;
		std::cout << "FR: " << FR.transpose() << std::endl;
		//std::cout << "U: " << U.transpose() << std::endl;

		// Esfuerzos en cada barra 
		// f^a_loc = K_^a_loc * T^a^t * u^a   (formula 3.6.4 del libro)
		// ----------------------------------------------------------------
	
		// Barra a:
		Eigen::Matrix<double, 4, 4> Ka_loc, Ta;
		Ka_loc <<
			Ka_11_loc, Ka_12_loc,
			Ka_12_loc.transpose(), Ka_22_loc;
		Ta <<
			calcmat::matriz_rotacion2(ang_a), Eigen::Matrix2d::Zero(),
			Eigen::Matrix2d::Zero(), calcmat::matriz_rotacion2(ang_a);
		const Eigen::Vector4d ua = indexing(U, std::array<int, 4>{0, 1, 2, 3});
		const Eigen::Vector4d fa = Ka_loc * Ta.transpose() * ua;

		// Barra b:
		Eigen::Matrix<double, 4, 4> Kb_loc, Tb;
		Kb_loc <<
			Kb_11_loc, Kb_13_loc,
			Kb_13_loc.transpose(), Kb_33_loc;
		Tb <<
			calcmat::matriz_rotacion2(ang_b), Eigen::Matrix2d::Zero(),
			Eigen::Matrix2d::Zero(), calcmat::matriz_rotacion2(ang_b);
		const Eigen::Vector4d ub = indexing(U, std::array<int, 4>{0, 1, 4, 5});
		const Eigen::Vector4d fb = Kb_loc * Tb.transpose() * ub;

		// Barra c:
		Eigen::Matrix<double, 4, 4> Kc_loc, Tc;
		Kc_loc <<
			Kc_22_loc, Kc_23_loc,
			Kc_23_loc.transpose(), Kc_33_loc;
		Tc <<
			calcmat::matriz_rotacion2(ang_c), Eigen::Matrix2d::Zero(),
			Eigen::Matrix2d::Zero(), calcmat::matriz_rotacion2(ang_c);
		const Eigen::Vector4d uc = indexing(U, std::array<int, 4>{2, 3, 4, 5});
		const Eigen::Vector4d fc = Kc_loc * Tc.transpose() * uc;

		std::cout << std::endl << "Esfuerzos en barras (coordenadas locales):" << std::endl;
		std::cout << "fa: " << fa.transpose() << std::endl;
		std::cout << "fb: " << fb.transpose() << std::endl;
		std::cout << "fc: " << fc.transpose() << std::endl;

		return 0; // el programa finaliza sin errores
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}
}
