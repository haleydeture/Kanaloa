clc;

syms xm dxm ddxm xr dxr ddxr
syms ym dym ddym yr dyr ddyr
syms tz dtz ddtz

xm = xr*cos(tz)-yr*sin(tz);
dxm = diff(xr)*dxr*cos(tz)+xr*diff(cos(tz))*dtz-(diff(yr)*dyr*sin(tz)+yr*diff(sin(tz))*dtz);
ddxm = (diff(dxr)*ddxr*cos(tz)+dxr*diff(cos(tz))*dtz)-...
    (diff(dtz)*ddtz*xr*sin(tz)+dtz*diff(xr)*dxr*sin(tz)+dtz*xr*diff(sin(tz))*dtz)-...
    (diff(dyr)*ddyr*sin(tz)+dyr*diff(sin(tz))*dtz)-...
    (diff(dtz)*ddtz*yr*cos(tz)+dtz*diff(yr)*dyr*cos(tz)+dtz*yr*diff(cos(tz))*dtz);

disp("dxm = ")
pretty(dxm)
disp("ddxm = ")
pretty(ddxm)

ym = xr*sin(tz)+yr*cos(tz);
dym = diff(xr)*dxr*sin(tz)+xr*diff(sin(tz))*dtz+diff(yr)*dyr*cos(tz)+yr*diff(cos(tz))*dtz
ddym = (diff(dtz)*ddtz*xr*cos(tz)+dtz*diff(xr)*dxr*cos(tz)+dtz*xr*diff(cos(tz))*dtz)+...
    (diff(dxr)*ddxr*sin(tz)+dxr*diff(sin(tz))*dtz)-...
    (diff(dtz)*ddtz*yr*sin(tz)+dtz*diff(yr)*dyr*sin(tz)+dtz*yr*diff(sin(tz))*dtz)+...
    (diff(dyr)*ddyr*cos(tz)+dyr*diff(cos(tz))*dtz);

disp("dym = ")
pretty(dym)
disp("ddym = ")
pretty(ddym)

rot = [...
cos(tz) -sin(tz) 0 0 0 0 0 0 0;...
sin(tz) cos(tz) 0 0 0 0 0 0 0;...
0 0 1 0 0 0 0 0 0;...
-sin(tz)*dtz -cos(tz)*dtz 0 cos(tz) -sin(tz) 0 0 0 0;...
cos(tz)*dtz -sin(tz)*dtz 0 sin(tz) cos(tz) 0 0 0 0;...
0 0 0 0 0 1 0 0 0;...
-cos(tz)*dtz^2-sin(tz)*ddtz sin(tz)*dtz^2-cos(tz)*ddtz 0 -2*sin(tz)*dtz -2*cos(tz)*dtz 0 cos(tz) -sin(tz) 0;...
-sin(tz)*dtz^2+cos(tz)*ddtz -cos(tz)*dtz^2-sin(tz)*ddtz 0 2*cos(tz)*dtz -2*sin(tz)*dtz 0 sin(tz) cos(tz) 0;...
0 0 0 0 0 0 0 0 1]

syms x y

rot2d = [cos(tz) -sin(tz) x;...
        sin(tz) cos(tz) y;...
        0 0 1]
    
rot2dInv = simplify(inv([cos(tz) -sin(tz) x;...
        sin(tz) cos(tz) y;...
        0 0 1]))