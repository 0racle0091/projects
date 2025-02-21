
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <array>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <unsupported/Eigen/MatrixFunctions>



constexpr size_t N = 3;
constexpr size_t Nsp = 24;
constexpr size_t Nd = 6;
constexpr double PI = 3.14159265358979323846;

std::array<double, 4> Quat(const std::array<std::array<double, 3>, 3>& R) {
    Eigen::Matrix3d mat;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            mat(i, j) = R[i][j];
        }
    }

    Eigen::Quaterniond q(mat);

    q.normalize();

    std::array<double, 4> quat = { q.x(), q.y(), q.z(), q.w() };
    return quat;
}

void dotProd(const std::array<std::array<double, N>, N>& a, const std::array<std::array<double, N>, N>& b, std::array<std::array<double, N>, N>& output) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            output[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                output[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

double doubleDotProd(const std::array<std::array<double, N>, N>& A, const std::array<std::array<double, N>, N>& B) {
    double result = 0.0;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result += A[i][j] * B[i][j];
        }
    }
    return result;
}

void dotProdMV(const std::array<std::array<double, Nd>, Nd>& a, const std::array<double, Nd>& b, std::array<double, Nd>& result) {
    for (size_t i = 0; i < Nd; i++) {
        result[i] = 0.0;
        for (size_t j = 0; j < Nd; j++) {
            result[i] += a[i][j] * b[j];
        }
    }
}

void transpose(const std::array<std::array<double, N>, N>& input, std::array<std::array<double, N>, N>& output) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            output[j][i] = input[i][j];
        }
    }
}



using Matrix3x3 = std::array<std::array<double, N>, N>;
using Matrix6x6 = std::array<std::array<double, Nd>, Nd>;
using Matrix24x24 = std::array<std::array<double, Nsp>, Nsp>;
using Matrix24x3x3 = std::array<Matrix3x3, Nsp>;

int main()
{
    std::ofstream outFile("lab.csv");
    std::ofstream oFile("krist.csv");
    std::srand(0);
    double  c = 0.4082482904638631;
    
    //for(int l=0;l<500;l++){
    
    Matrix3x3 sigma = { { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} } };
    Matrix24x3x3 mu = { {
        {{
          {{-c, -c, -c}}, {{0, 0, 0}}, {{c, c, c}}
          }},
        {{
            {{-c, -c, -c}}, {{c, c, c}}, {{0, 0, 0} }
            }},
        {{
    { {-c, -c, c} }, { {0, 0, 0} }, {{ -c, -c, c }}
    }},
        {{
            { {-c, -c, c} }, { {c, c, -c} }, { {0, 0, 0 }}
        }},
        {{
            {{-c, c, -c} }, { {-c, c, -c} }, {{ 0, 0, 0 }}
            }},
        {{
            {{-c, c, -c} }, { {0, 0, 0} }, {{ c, -c, c }}
            }},
        {{
            {{-c, c, c} }, { {-c, c, c} }, {{ 0, 0, 0 }}
            }},
        {{
            {{-c, c, c} }, { {0, 0, 0} }, {{ -c, c, c }}
            }},
        {{
            {{0, 0, 0} }, { {-c, -c, -c} }, {{ c, c, c }}
            }},
              {{
                  {{0, 0, 0}}, {{-c, -c, c}}, {{-c, -c, c}}
                  }},
              {{
                  {{0, 0, 0}}, {{-c, c, -c}}, {{-c, c, -c}}
                  }},
              {{
                  {{0, 0, 0}}, {{-c, c, c}}, {{c, -c, -c}}
                  }},
        // doubled by sliding directions
            {{
            {{c, c, c}}, {{0, 0, 0}}, {{-c, -c, -c}}
            }},
            {{
                {{c, c, c}}, {{-c, -c, -c}}, {{0, 0, 0}}
                }},
            {{
                {{c, c, -c}}, {{0, 0, 0}}, {{c, c, -c}}
                }},
            {{
                {{c, c, -c}}, {{-c, -c, c}}, {{0, 0, 0}}
                }},
            {{
                {{c, -c, c}}, {{c, -c, c}}, {{0, 0, 0}}
                }},
            {{
                {{c, -c, c}}, {{0, 0, 0}}, {{ -c, c, -c}}
                }},
            {{
                {{c, -c, -c}}, {{c, -c, -c}}, {{0, 0, 0}}
                }},
            {{
                {{c, -c, -c}}, {{0, 0, 0}}, {{c, -c, -c}}
                }},
            {{
                {{0, 0, 0}}, {{c, c, c}}, {{-c, -c, -c}}
                }},
            {{
                {{0, 0, 0}}, {{c, c, -c}}, {{c, c, -c}}
                }},
            {{
                {{0, 0, 0}}, {{c, -c, c}}, {{c, -c, c}}
                }},
            {{
                {{0, 0, 0}}, {{c, -c, -c}}, {{-c, c, c}}
                }}
            }
    };

    Matrix24x24 H = { {
        {1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4},
        {1.4, 1, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4},
        {1.4, 1.4, 1, 1.4, 1.4, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4},
        {1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4},
        {1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4},
        {1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4},
        {1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1, 1.4, 1.4, 1.4, 1.4, 1.4},
        {1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4},
        {1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4,1.4},
        {1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4},
        {1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4},
        {1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1},
        {1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1.4},
        {1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1.4},
        {1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4},
        {1.4,1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4},
        {1.4, 1.4, 1.4, 1.4,1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1.4},
        {1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4,1.4, 1.4, 1.4},
        {1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4},
        {1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4},
        {1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4},
        {1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1.4, 1, 1.4, 1.4},
        {1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1.4, 1.4, 1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1.4, 1, 1.4},
        {1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4,1.4, 1, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1}
    } };
    int M = 12;
    Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
    Eigen::Matrix3d LstarEig;
    Eigen::Matrix3d dF;
    Eigen::Matrix3d C;
    Eigen::Matrix3d epsilon_H;
    Eigen::Matrix3d sigmaEig;
    Eigen::Matrix3d sigmaEiglab;
    double perf = 1.0062891;
    std::array<double, Nsp> taustar = { 16e6*perf, 16e6 * perf, 16e6 * perf, 16e6 * perf , 16e6 * perf, 16e6 * perf, 16e6 * perf , 16e6 * perf,
        16e6 * perf, 16e6 * perf , 16e6 * perf, 16e6 * perf, 16e6 * perf, 16e6 * perf, 16e6 * perf , 16e6 * perf,
     16e6 * perf, 16e6 * perf, 16e6 * perf, 16e6 * perf, 16e6 * perf, 16e6 * perf , 16e6 * perf, 16e6 * perf };
    std::array<double, Nsp> tau = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
  0., 0., 0., 0., 0., 0., 0. };
    std::array<double, Nsp> taudot = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
  0., 0., 0., 0., 0., 0., 0. };
    std::array<double, Nsp> etta = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };
    Matrix3x3 zettaie = { { {0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.} } };
    Matrix3x3 lambda = { {
        {1e-3, 0.0, 0.0},
        {0.0, -1e-3 / 2, 0.0},
        {0.0, 0.0, -1e-3 / 2}
    } };
    Matrix3x3 omega = { {
        {0., 0., 0.},
        {0., 0., 0.},
        {0., 0., 0.}
    } };
    Matrix6x6 Pi{ {
        {168.4e9, 121.4e9, 121.4e9, 0., 0., 0.},
        {121.4e9, 168.4e9, 121.4e9, 0., 0., 0.},
        {121.4e9, 121.4e9, 168.4e9, 0., 0., 0.},
        {0., 0., 0., 75.4e9, 0., 0.},
        {0., 0., 0., 0., 75.4e9, 0.},
        {0., 0., 0., 0., 0., 75.4e9}
    } };
    double dt = 0.001;
    double h0 = 180000000 * 1.00602658;
    double etastar = 0;
    double summdef = 0;
    double t = 0;
    Matrix3x3 lambdastar = { {
        {0., 0., 0.},
        {0., 0., 0.},
        {0., 0., 0.}
    } };
    int V = 83* 0.81632639;
    Matrix3x3 zettae = { {
        {0., 0., 0.},
        {0., 0., 0.},
        {0., 0., 0.}
    } };
    Matrix3x3 sigmadot = { {
        {0., 0., 0.},
        {0., 0., 0.},
        {0., 0., 0.}
    } };
    std::array<double, Nd> sigmaprom = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    Matrix3x3 temp = { {
        {0.,0.,0.},
        {0.,0.,0.},
        {0.,0.,0.},
    } };
    Matrix3x3 ObT = { {
        {0.,0.,0.},
        {0.,0.,0.},
        {0.,0.,0.},
    } };
    Matrix3x3 Obdot = { {
        {0.,0.,0.},
        {0.,0.,0.},
        {0.,0.,0.},
    } };
    std::array<double, Nd> sigmadotprom = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };


    std::array<double, 4> q = { 0.0,0.0,0.0,0.0 };
    std::array<double, 4> q1 = { 0.0,0.0,0.0,0.0 };
    std::array<double, Nd> SpecV = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    int br = 0;
    Matrix3x3 Ob = { {
        {0.,0.,0.},
        {0.,0.,0.},
        {0.,0.,0.},
    } };
    Matrix3x3 Obnach = { {
        {0.,0.,0.},
        {0.,0.,0.},
        {0.,0.,0.},
    } };
    int counter = 0;
    int counter1 = 0;
    int Itlim = 1000000;

    Eigen::Matrix3d Obeig;
    Obeig << 0.997681, 0.035537, -0.0580565,
        -0.0454228, 0.982802, -0.178991,
        0.0506972, 0.181213, 0.982136;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            Ob[i][j] = Obeig(i, j);
            Obnach[i][j] = Obeig(i, j);
        }
    }
    //Eigen::Matrix3d Obeig;
    //Matrix24x3x3 mu1;

    std::cout << "{{" << Obeig(0, 0) << "," << Obeig(0, 1) << "," << Obeig(0, 2) << "}," << "\n"
        << "{" << Obeig(1, 0) << "," << Obeig(1, 1) << "," << Obeig(1, 2) << "}," << "\n"
        << "{" << Obeig(2, 0) << "," << Obeig(2, 1) << "," << Obeig(2, 2) << "}}" << "\n"; 
        /*for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                LstarEig(i, j) = lambda[i][j];
            }
        }*/

        //начало цикла
    for (int b = 0; b < 10000; b++) {
        for (int m = 0; m < 24; m++) {
            tau[m] = doubleDotProd(sigma, mu[m]);
        }

        counter++;


        transpose(Ob, ObT);
        dotProd(Ob, lambda, temp);
        dotProd(temp, ObT, lambdastar);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                Obeig(i, j) = Ob[i][j];
            }
        }


        etastar = 0;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                etastar += pow(fabs(lambdastar[i][j]), 2);
            }
        }

        etastar = sqrt(etastar);

        for (int m = 0; m < 24; m++) {
            if (tau[m] > taustar[m]) {
                etta[m] = 1.06774798 *etastar * pow(fabs(tau[m] / taustar[m]), V);
                //br = 1;
            }
            else {
                etta[m] = 0;
            }
        }

        //if (br == 1) { break; }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int m = 0; m < 24; m++) {
                    zettaie[i][j] += etta[m] * mu[m][i][j];
                }
            }
        }

        omega[0][0] = 0;
        omega[1][1] = 0;
        omega[2][2] = 0;
        omega[1][0] = lambdastar[1][0] - zettaie[1][0];
        omega[0][1] = -omega[1][0];
        omega[2][0] = lambdastar[2][0] - zettaie[2][0];
        omega[0][2] = -omega[2][0];
        omega[2][1] = lambdastar[2][1] - zettaie[2][1];
        omega[1][2] = -omega[2][1];

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                zettae[i][j] = lambdastar[i][j] - omega[i][j] - zettaie[i][j];
                //std::cout << zettae[i][j]<<std::endl;
                //zettae[i][j] = 0;
            }
        }

        //sigmadotprom todasyo vse dela tosi bosi
        SpecV = { zettae[0][0],zettae[1][1], zettae[2][2], zettae[0][1] + zettae[1][0], zettae[0][2] + zettae[2][0], zettae[1][2] + zettae[2][1] };

        dotProdMV(Pi, SpecV, sigmadotprom);

        sigmadot[0][0] = sigmadotprom[0];
        sigmadot[1][1] = sigmadotprom[1];
        sigmadot[2][2] = sigmadotprom[2];
        sigmadot[0][1] = sigmadotprom[3];
        sigmadot[1][0] = sigmadotprom[3];
        sigmadot[0][2] = sigmadotprom[4];
        sigmadot[2][0] = sigmadotprom[4];
        sigmadot[1][2] = sigmadotprom[5];
        sigmadot[2][1] = sigmadotprom[5];

        for (int m = 0; m < 24; m++) {
            for (int s = 0; s < 24; s++) {
                taudot[m] += H[m][s] * etta[s] * h0;
            }
        }

        dotProd(omega, Ob, Obdot);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                //Ob
                Ob[i][j] += Obdot[i][j] * dt;
                sigma[i][j] += sigmadot[i][j] * dt;
                zettaie[i][j] = 0;
                zettae[i][j] = 0;
            }
        }

        for (int i = 0; i < Nsp; i++) {
            taustar[i] += taudot[i] * dt;
            taudot[i] = 0;
        }

        double normsigma1 = 0;
        double normsigma;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                normsigma1 += sigma[i][j] * sigma[i][j];
            }
        }


        //proverka na tupost`
        normsigma = sqrt(normsigma1);


        //proverka na tupost` 2
        if (counter == 1000000) {

            //std::cout << sigma[0][0]<<" "<< etta[0] << "  taustar" << taustar[0] << "tau " << tau[0] << " normsigma " << normsigma <<" Ob "<<Ob[0][0]<<" Obdot "<<Obdot[0][0]<<" omega "<<omega[0][0]<<" zettae "<<zettae[0][0]<<" sigmadprom "<<sigmadotprom[0]<<" lstar "<< lambdastar[0][0] << std::endl;
            //std::cout << "zetta 2 " << zettae[1][1] << " " << zettae[2][2] <<" etastar "<<etastar<< " epsilonH"<<epsilon_H(1,1)<<" C "<<C(1, 1)<<std::endl;
            std::cout << "It" << b / 1000000 << std::endl;
            //std::cout << Ob[0][0] << std::endl;;
            counter = 0;

        }
        //vivod
        if (counter1 == 100) {
            counter1 = 0;
        }
        if (counter1 == 0||b==0) {
            //perehod na lab
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    sigmaEig(i, j) = sigma[i][j];
                }
            }
            //std::cout << mu[1][1][1] << std::endl;
            //std::cout << "zetta 2 " << taustar[0] << " " << SpecV[2] << " etastar " << etastar << std::endl;
            sigmaEiglab = Obeig.transpose() * sigmaEig * Obeig;
            //std::cout << sigmaEiglab(2, 2) << " " << sigma[2][2] << std::endl;
            outFile << sigmaEiglab(0,0) <<"\n";
            oFile << sigma[0][0] << "\n";

        }

        counter1++;


    }//konec cikla





//}
outFile.close();
oFile.close();
return 0;
}


//std::cout << sigma[0][0] << "bruhaaa" << std::endl;
/*q = Quat(Ob);
for (int i = 0; i < 4; i++) {
   std::cout << q[i] << std::endl;

}
std::cout << "quat" << l << std::endl;
outFile << q[0] << ", " << q[1] << ", " << q[2] << ", " << q[3] << "\n"; 

    q = Quat(Ob);
    q1 = Quat(Obnach);
    std::cout << "quat" << l << std::endl;
    outFile << q[0] << ", " << q[1] << ", " << q[2] << ", " << q[3] << "; " << q1[0] << ", " << q1[1] << ", " << q1[2] << "penis " << q1[3] << "\n";
*/ //quat dlya orientaciy
//}


        //dlya F
        /*for (int i = 0; i < 1000; ++i) {
            dF = LstarEig * F * dt;
            F += dF;
        }*/

        //F na pervom shage - edinich, poetomu nahodim meru gence s opozdaniem na shag
        /*C = F.transpose() * F;    **<< epsilon_H(1, 1) << ", "**
        epsilon_H = C.log();*/
        //std::cout << "sigmalab " << sigmaEiglab(1, 1) << " sigmacrist " << sigma[1][1] << " ObEig "<< Obeig <<std::endl;
//etta[m] = etastar * pow(fabs(tau[m] / taustar[m]), V)