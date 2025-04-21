function [Kii, Kjj, Kij] = matriz_barra_rig_rig(L, E, A, Iz)
%{
Ver documentacion en matriz_barra_art_art.m
%}

L2 = L^2;
L3 = L^3;
EI = E * Iz;
EA = E * A;

% Submatrices en locales:
Kii = [ EA/L,       0,         0;
         0,   12*EI/L3,   6*EI/L2;
         0,   6*EI/L2,   4*EI/L ];

Kjj = [ EA/L,       0,          0;
         0,   12*EI/L3,  -6*EI/L2;
         0,  -6*EI/L2,   4*EI/L ];

Kij = [-EA/L,        0,         0;
         0,  -12*EI/L3,   6*EI/L2;
         0,  -6*EI/L2,   2*EI/L ];
end