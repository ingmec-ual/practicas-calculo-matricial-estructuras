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
%}

clc;
clear;

E = 200e9;  % Pa
A = 2e-4;   % m^2

% Barra a
[Ka_11_loc, Ka_22_loc, Ka_12_loc] = matriz_barra_art_art(0.5, E, A);
ang_a = deg2rad(0);
Ra = matriz_rotacion2(ang_a);
Ka_11 = Ra * Ka_11_loc * Ra';
Ka_22 = Ra * Ka_22_loc * Ra';
Ka_12 = Ra * Ka_12_loc * Ra';

% Barra b
[Kb_11_loc, Kb_33_loc, Kb_13_loc] = matriz_barra_art_art(1.0, E, A);
ang_b = deg2rad(90);
Rb = matriz_rotacion2(ang_b);
Kb_11 = Rb * Kb_11_loc * Rb';
Kb_33 = Rb * Kb_33_loc * Rb';
Kb_13 = Rb * Kb_13_loc * Rb';

% Barra c
[Kc_22_loc, Kc_33_loc, Kc_23_loc] = matriz_barra_art_art(hypot(0.5,1.0), E, A);
ang_c = atan2(1.0, -0.5);
Rc = matriz_rotacion2(ang_c);
Kc_22 = Rc * Kc_22_loc * Rc';
Kc_33 = Rc * Kc_33_loc * Rc';
Kc_23 = Rc * Kc_23_loc * Rc';

% Ensamblar matriz de rigidez global
K = zeros(6);
K(1:2, 1:2) = Ka_11 + Kb_11;
K(3:4, 3:4) = Ka_22 + Kc_22;
K(5:6, 5:6) = Kb_33 + Kc_33;
K(1:2, 3:4) = Ka_12;
K(3:4, 1:2) = Ka_12';
K(1:2, 5:6) = Kb_13;
K(5:6, 1:2) = Kb_13';
K(3:4, 5:6) = Kc_23;
K(5:6, 3:4) = Kc_23';

disp('K =');
disp(K);

% Opcional: visualizar el patrón de zeros de la matriz:
if (1)
    spy(K)
    title('"Sparsity Pattern" de la matriz de rigidez K')
    axis equal

    % Etiquetas para las coordenadas:
    labels = {'x1','y1','x2','y2','x3','y3'};

    xticks(1:6);
    yticks(1:6);
    xticklabels(labels);
    yticklabels(labels);

    xtickangle(45);  % para mejor visibilidad
    grid on; % Para ver la rejilla
end

% Resolver sistema
idxs_R = [1 2 4];  % MATLAB uses 1-based indexing
idxs_L = [3 5 6];

KLL = K(idxs_L, idxs_L);
KRR = K(idxs_R, idxs_R);
KLR = K(idxs_L, idxs_R);
KRL = KLR';

FL = [0; 1000; 0];
UR = [0; 0; 0];

UL = KLL \ (FL - KLR * UR);
FR = KRR * UR + KRL * UL;

U = zeros(6, 1);
U(idxs_L) = UL;
U(idxs_R) = UR;

fprintf('UL: %s\n', mat2str(UL', 6));
fprintf('FR: %s\n', mat2str(FR', 6));

% Esfuerzos en barras (locales)
% Barra a
Ka_loc = [Ka_11_loc, Ka_12_loc; Ka_12_loc', Ka_22_loc];
Ta = [Ra, zeros(2); zeros(2), Ra];
ua = U([1 2 3 4]);
fa = Ka_loc * Ta' * ua;

% Barra b
Kb_loc = [Kb_11_loc, Kb_13_loc; Kb_13_loc', Kb_33_loc];
Tb = [Rb, zeros(2); zeros(2), Rb];
ub = U([1 2 5 6]);
fb = Kb_loc * Tb' * ub;

% Barra c
Kc_loc = [Kc_22_loc, Kc_23_loc; Kc_23_loc', Kc_33_loc];
Tc = [Rc, zeros(2); zeros(2), Rc];
uc = U([3 4 5 6]);
fc = Kc_loc * Tc' * uc;

fprintf('\nEsfuerzos en barras (coordenadas locales):\n');
fprintf('fa: %s\n', mat2str(fa', 6));
fprintf('fb: %s\n', mat2str(fb', 6));
fprintf('fc: %s\n', mat2str(fc', 6));
