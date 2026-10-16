// Laboratorio 2.1: Tensores y Operaciones Basicas con Eigen
// Autor: Alessandro De Bonis Rodriguez

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// ------------------------------------------------------------
// Actividad 2: operaciones basicas de algebra lineal
// ------------------------------------------------------------

void matrixSum() {
    cout << "=== 1. Suma de matrices ===" << endl;

    Matrix2d a;
    a << 1, 2,
         3, 4;

    Matrix2d b;
    b << 5, 6,
         7, 8;

    // Eigen suma posicion por posicion
    Matrix2d result = a + b;

    cout << "A =\n" << a << endl;
    cout << "B =\n" << b << endl;
    cout << "A + B =\n" << result << endl << endl;
}

void dotProduct() {
    cout << "=== 2. Producto punto ===" << endl;

    Vector3d u(1, 2, 3);
    Vector3d v(4, 5, 6);

    // 1*4 + 2*5 + 3*6 = 32
    double result = u.dot(v);

    cout << "u = " << u.transpose() << endl;
    cout << "v = " << v.transpose() << endl;
    cout << "u . v = " << result << endl << endl;
}

void matrixTranspose() {
    cout << "=== 3. Transposicion ===" << endl;

    // Matriz de 2 filas y 3 columnas
    MatrixXd m(2, 3);
    m << 1, 2, 3,
         4, 5, 6;

    // La transpuesta cambia filas por columnas: queda de 3x2
    MatrixXd t = m.transpose();

    cout << "M (2x3) =\n" << m << endl;
    cout << "M^T (3x2) =\n" << t << endl << endl;
}

// ------------------------------------------------------------
// Actividad 3: imagen pequena en escala de grises
// Cada numero es un pixel: 0 = negro, 255 = blanco
// ------------------------------------------------------------

void grayscaleImage() {
    cout << "=== 4. Imagen en escala de grises (4x4) ===" << endl;

    MatrixXd image(4, 4);
    image <<  10,  50, 100, 150,
              20,  60, 110, 160,
              30,  70, 120, 170,
              40,  80, 130, 180;

    cout << "Imagen original =\n" << image << endl << endl;

    // Transformacion 1: subir el brillo (multiplicar por un escalar)
    MatrixXd brighter = image * 1.5;
    // Ningun pixel puede pasar de 255
    brighter = brighter.cwiseMin(255.0);
    cout << "Brillo x1.5 (tope 255) =\n" << brighter << endl << endl;

    // Transformacion 2: negativo de la imagen (255 - pixel)
    MatrixXd allWhite = MatrixXd::Constant(4, 4, 255.0);
    MatrixXd negative = allWhite - image;
    cout << "Negativo (255 - pixel) =\n" << negative << endl << endl;

    // Transformacion 3: voltear la imagen horizontalmente
    // Se multiplica por una matriz que invierte el orden de las columnas
    MatrixXd flip(4, 4);
    flip << 0, 0, 0, 1,
            0, 0, 1, 0,
            0, 1, 0, 0,
            1, 0, 0, 0;
    MatrixXd mirrored = image * flip;
    cout << "Espejo horizontal (imagen * matriz de volteo) =\n" << mirrored << endl << endl;

    // Transformacion 4: transponer la imagen (filas pasan a ser columnas)
    MatrixXd transposed = image.transpose();
    cout << "Imagen transpuesta =\n" << transposed << endl;
}

int main() {
    matrixSum();
    dotProduct();
    matrixTranspose();
    grayscaleImage();
    return 0;
}
