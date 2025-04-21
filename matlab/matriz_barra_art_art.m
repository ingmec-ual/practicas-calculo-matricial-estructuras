function [Kii, Kjj, Kij] = matriz_barra_art_art(L, E, A)
%{
*******************************************************************************
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
*******************************************************************************

Las formulas teoricas pueden consultarse en el libro:
Claraco, J. L. B., González, A., & Ocaña, J. M. G. M. (2012). 
Análisis estático de estructuras por el método matricial. 
Servicio de Publicaciones e Intercambio Científico de la Universidad de Málaga.
https://ingmec.ual.es/~jlblanco/papers/blanco2012calculo_matricial_estructuras.pdf
%}

% Submatrices en locales:
Kii = [E*A / L, 0; 0, 0];
Kjj = Kii;
Kij = [-E*A / L, 0; 0, 0];
end