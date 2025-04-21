function R = matriz_rotacion2(ang_rad)
%{
Ver documentacion en matriz_barra_art_art.m
%}

R = [cos(ang_rad), -sin(ang_rad);
     sin(ang_rad),  cos(ang_rad)];
end