Unit = 1.e-3;
lc = 0.5*Unit;

//N_Layers = 20;

r1=61.2*0.5*Unit;
r2=106.4*0.5*Unit;
h=4.61*Unit/2.;

r_inf=200*Unit;
r_ext=125*Unit;

// Define torus section
P0= newp; Point(P0) = {0,0,0, lc};
P1= newp; Point(P1) = {r1,0,-h, lc};
P2= newp; Point(P2) = {r2,0,-h, lc};
P3= newp; Point(P3) = {r2,0, h, lc};
P4= newp; Point(P4) = {r1,0, h, lc};

L12=newl; Line(L12) = {P1, P2};
L23=newl; Line(L23) = {P2, P3};
L34=newl; Line(L34) = {P3, P4};
L41=newl; Line(L41) = {P4, P1};

L=newl; Line Loop(L) = {L12, L23, L34, L41};
S=newreg; Plane Surface(S) = {L};

// Define ext section
P5=newp; Point(P5) = {0,0, -r_ext, 10*lc};
P6=newp; Point(P6) = {r_ext, 0, 0, 10*lc};
P7=newp; Point(P7) = {0, 0, r_ext, 10*lc};

L05=newl; Line(L05) = {P0, P5};
C56=newl; Circle(C56) = {P5, P0, P6};
C67=newl; Circle(C67) = {P6, P0, P7};
L70=newl; Line(L70) = {P7, P0};

L_ext=newl; Line Loop(L_ext) = {L05, C56, C67, L70};
S_ext=newreg; Plane Surface(S_ext) = {L_ext, -L};

// Define inf section
P8=newp; Point(P8) = {0,     0, -r_inf, 60*lc};
P9=newp; Point(P9) = {r_inf, 0, 0, 60*lc};
P10=newp; Point(P10) = {0,   0, r_inf, 60*lc};

L58=newl; Line(L58) = {P5, P8};
C89=newl; Circle(C89) = {P8, P0, P9};
C910=newl; Circle(C910) = {P9, P0, P10};
L107=newl; Line(L107) = {P10, P7};

L_inf=newl; Line Loop(L_inf) = {L58, C89, C910, L107, -C67, -C56};
S_inf=newreg; Plane Surface(S_inf) = {L_inf};

// Build 3D geom
Extrude { {0,0,1} , {0,0,0} , Pi/2. } { 
  Surface{S, S_ext, S_inf}; 
}

//  Define Physical

Physical Volume("COIL") = {1}; // Tore
Physical Volume("Omega") = {2,3}; // Air

Physical Surface("Border") = {74, 96,12,18,40,6, 85, 88};  // Sym


//Physical Line("Axis") = {7,10,13,16}; //Axis
