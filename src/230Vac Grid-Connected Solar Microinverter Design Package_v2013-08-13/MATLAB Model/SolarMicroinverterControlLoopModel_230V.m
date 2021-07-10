% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
% % % % % % % % % SOLAR PV MICROINVERTER MODEL - 230V % % % % % % % % % % %
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
clc;
clear all;
close all

s = tf('s');


%%    PASSIVE COMPONENTS 

 
N =7;                                                                      % Turns Ratio of flyback converter

Ron = 12e-3;
Rp = 28e-3;
Rs = 1;
Rf = 40e-3*2 + 0.2*2 + 60e-3*2;                                             % Filter resistance, mosfet resistances and common mode choke resistance

Lm = 55e-6;
Lf = 300e-6;

Co = 0.1e-6*2+0.015e-6 * 3;

Ibase = 1/0.7733;                                                           % Sensor Gain for perunitization

Vdiode = 2;                                                                 % Diode forward drop

Ts = 17.6e-6;                                                               % Sampling Frequency

%%   STEADY STATE VOLTAGE AND CURRENT LEVELS

Vpv = 36 ;                                                                  % Nominal PV array voltage
P   = 215;                                                                  % Nominal Power output
Vorms = 230;
Vopeak = Vorms*sqrt(2);
Iacrms = 215/Vorms ;                                                        % Nominal Current output
Rload = Vorms / Iacrms;                                                     % Equivalent load resistance
Rf = Rf + Rload;                                                            % Rf and Rload are in series



%%  SMALL SIGNAL STATE SPACE MODEL


D =  Vorms/(Vorms+N*Vpv);                                                    % approximation only.
Ddash = 1-D;

p = N/Ddash;

Im = Iacrms*N/Ddash/2;                                                       % from steady state equation for a single flyback converter

K = Vpv - Im*(Ron+Rp)+Rs*Im/N + Vorms/N + Vdiode;
R = (Ron+Rp)*D + Rs*Ddash/N;



A = [-R/Lm              0       -Ddash/(N*Lm) ;...                          % State Matrix
    0                  -Rf/Lf       1/Lf      ;...
    Ddash/(Co*N)         -1/Co         0       ];

B1= [K/Lm              ;  0  ;      -Im/(N*Co)];                            % Control Matrix 
B2= [ D/Lm             ;  0  ;         0     ];                             % Input voltage disturbance matrix
B3= [ 0                ;-1/Lf;         0     ];                             % Grid voltage disturbance matrix

C = [0 1 0];                                                                % Output matrix for iac vs d plant
    
Cipvd = [D 0 0];                                                            % Output matrix for ipv vs d plant

D1 =0 ;                                                                     % Transmission matrix for iac vs d plant

D2 = Im;                                                                    % Transmission matrix for ipv vs d plant


%% SYSTEM PLANT TRANSFER FUNCTIONS

sys = ss(A,B1,C,D1);                                                        % LTI System for iac vs d transfer function

Gid = tf(sys) / Ibase;                                                      % iac vs d transfer function
 
sys_ipvd = ss(A,B1,Cipvd,D2);                                               % LTI System for ipv vs d transfer function 

Gipvd = 2*tf(sys_ipvd)/ 11;                                                 % ipv vs d transfer function for load sharing controller design

 
%% CURRENT CONTROLLER

H = 1/(1.69e3*8200e-12*s+1);                                                % Feedback network filter

Gc = (0.17+ 1200/s);                                                        % PI Compensator

oltf = Gid * Gc * H;                                                        % Open Loop Transfer function

Gcd = c2d(Gc,Ts,'tustin')                                                   % Compensator TF in Z-domain

%%  LOAD SHARING CONTROLLER 

Gcls = 0.065 + 50/s;                                                        % PI Load Sharing compensator

Gclsd = c2d(Gcls, Ts,'tustin')                                              % Compensator TF in Z-domain
 
oltfLS = Gipvd * Gcls ;                                                     % Open Loop Transfer Function for Load sharing control 


%% FREQUENCY RESPONSE PLOTS


P = bodeoptions; 
P.FreqUnits = 'Hz' ;
P.Grid      = 'on' ;


 figure                                                                      % Freqency response of grid current controller
 bode(Gid, P)
 hold on
 margin(oltf)
 hold off
 
 figure
 bode(Gipvd,P)                                                              % Frequency response of load sharing controller
 hold on
 margin(oltfLS)
 hold off










