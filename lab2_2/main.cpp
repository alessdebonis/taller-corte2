// Laboratorio 2.2: Construccion del Motor de Regresion Logistica
// Autor: Alessandro De Bonis Rodriguez

#include <iostream>
#include <cmath>
#include <iomanip>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// ------------------------------------------------------------
// Actividad 1: regresion lineal (paso introductorio)
// Modelo: y = w * x + b
// Los datos salen de la recta y = 2x + 1, asi sabemos
// que el resultado correcto es w = 2 y b = 1.
// ------------------------------------------------------------

void linearRegression() {
    cout << "=== Actividad 1: Regresion lineal ===" << endl;

    VectorXd x(5);
    x << 1, 2, 3, 4, 5;

    VectorXd y(5);
    y << 3, 5, 7, 9, 11;

    int m = x.size();        // numero de datos
    double w = 0.0;          // peso inicial
    double b = 0.0;          // sesgo inicial
    double learningRate = 0.05;
    int iterations = 2000;

    for (int i = 0; i < iterations; i++) {
        // 1. Prediccion para todos los datos a la vez
        VectorXd prediction = (x * w).array() + b;

        // 2. Error de cada dato
        VectorXd error = prediction - y;

        // 3. Gradientes del error cuadratico medio
        double dw = (2.0 / m) * error.dot(x);
        double db = (2.0 / m) * error.sum();

        // 4. Actualizar pesos
        w = w - learningRate * dw;
        b = b - learningRate * db;

        if (i % 500 == 0) {
            double mse = error.squaredNorm() / m;
            cout << "Iteracion " << i << "  MSE = " << mse << endl;
        }
    }

    cout << "Resultado: w = " << w << "   b = " << b << endl;
    cout << "(Esperado: w = 2, b = 1)" << endl << endl;
}

// ------------------------------------------------------------
// Actividad 2: funcion Sigmoid
// sigma(z) = 1 / (1 + e^(-z))
// Se aplica a cada elemento del vector z
// ------------------------------------------------------------

VectorXd sigmoid(const VectorXd& z) {
    return 1.0 / (1.0 + (-z.array()).exp());
}

// ------------------------------------------------------------
// Actividad 3: funcion de costo Cross-Entropy
// J = -(1/m) * suma[ y*log(p) + (1-y)*log(1-p) ]
// ------------------------------------------------------------

double crossEntropy(const VectorXd& y, const VectorXd& p) {
    int m = y.size();
    ArrayXd yArr = y.array();
    ArrayXd pArr = p.array();

    ArrayXd perSample = yArr * pArr.log() + (1.0 - yArr) * (1.0 - pArr).log();
    return -perSample.sum() / m;
}

int main() {
    linearRegression();

    // Datos: horas de estudio de 10 estudiantes y si aprobaron (1) o no (0)
    VectorXd hours(10);
    hours << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;

    VectorXd passed(10);
    passed << 0, 0, 0, 0, 1, 0, 1, 1, 1, 1;

    int m = hours.size();

    // ---------- Actividad 2: evaluar la Sigmoid ----------
    cout << "=== Actividad 2: Sigmoid ===" << endl;
    VectorXd testZ(5);
    testZ << -5, -1, 0, 1, 5;
    cout << "z          = " << testZ.transpose() << endl;
    cout << "sigmoid(z) = " << sigmoid(testZ).transpose() << endl << endl;

    // Pesos iniciales en cero
    double w = 0.0;
    double b = 0.0;

    VectorXd z = (hours * w).array() + b;
    VectorXd p = sigmoid(z);
    cout << "Predicciones iniciales (w = 0, b = 0):" << endl;
    cout << p.transpose() << endl << endl;

    // ---------- Actividad 3: costo inicial ----------
    cout << "=== Actividad 3: Costo Cross-Entropy ===" << endl;
    cout << "Costo inicial = " << crossEntropy(passed, p) << endl;
    cout << "(Con todas las predicciones en 0.5 el costo es ln(2) = 0.6931)" << endl << endl;

    // ---------- Actividad 4: gradiente descendiente ----------
    cout << "=== Actividad 4: Gradiente descendiente ===" << endl;
    double learningRate = 0.1;
    int iterations = 5000;

    for (int i = 0; i < iterations; i++) {
        // 1. Prediccion
        z = (hours * w).array() + b;
        p = sigmoid(z);

        // 2. Error (prediccion - real)
        VectorXd error = p - passed;

        // 3. Gradientes
        double dw = error.dot(hours) / m;
        double db = error.sum() / m;

        // 4. Actualizar pesos
        w = w - learningRate * dw;
        b = b - learningRate * db;

        if (i % 1000 == 0) {
            cout << "Iteracion " << i << "  Costo = " << crossEntropy(passed, p) << endl;
        }
    }

    // Resultado final
    p = sigmoid((hours * w).array() + b);
    cout << "Costo final = " << crossEntropy(passed, p) << endl;
    cout << "Pesos finales: w = " << w << "   b = " << b << endl << endl;

    cout << "Horas | Real | Probabilidad | Prediccion" << endl;
    cout << fixed << setprecision(4);
    for (int i = 0; i < m; i++) {
        int prediction = (p(i) >= 0.5) ? 1 : 0;
        cout << setw(5) << (int)hours(i) << " | " << setw(4) << (int)passed(i) << " | "
             << setw(12) << p(i) << " | " << setw(10) << prediction << endl;
    }

    return 0;
}
