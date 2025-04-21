function R = matriz_rotacion3(ang_rad)
%{
Ver documentacion en matriz_barra_art_art.m
%}

R = [cos(ang_rad), -sin(ang_rad), 0;
     sin(ang_rad),  cos(ang_rad), 0;
            0,         0, 1];
end