# Taller Corte 2: Álgebra Lineal Computacional y Regresión Logística

**Universidad Sergio Arboleda** · Docente: Oscar Andrés Arias
**Estudiante:** Alessandro De Bonis Rodríguez

Laboratorios en C++ con la biblioteca de álgebra lineal **Eigen**. El proyecto compila en **macOS, Windows y Linux**.

---

## Contenido del proyecto

```
taller-corte2/
├── CMakeLists.txt        # Archivo de construcción: busca y enlaza Eigen
├── README.md             # Este archivo
├── lab2_1/main.cpp       # Laboratorio 2.1: tensores y operaciones básicas
├── lab2_2/main.cpp       # Laboratorio 2.2: regresión lineal y logística
├── third_party/eigen/    # Copia de Eigen 3.4.0 (por si no está instalado)
└── .vscode/settings.json # Configuración para que VS Code reconozca Eigen
```

### ¿Cómo se enlaza Eigen?

El `CMakeLists.txt` hace dos intentos:

1. Busca Eigen instalado en el sistema con `find_package(Eigen3)`.
2. Si no lo encuentra, usa la copia incluida en `third_party/eigen`.

Por eso **no es obligatorio instalar Eigen**: el proyecto compila en cualquier computador que tenga un compilador de C++ y CMake.

---

## Paso a paso para compilar y ejecutar

### Paso 1. Instalar las herramientas (solo la primera vez)

Se necesitan dos cosas: un **compilador de C++** y **CMake**.

**macOS**

1. Abrir la Terminal.
2. Instalar el compilador de Apple:
   ```bash
   xcode-select --install
   ```
3. Instalar CMake con Homebrew (Eigen es opcional):
   ```bash
   brew install cmake eigen
   ```

**Windows**

1. Descargar e instalar **Visual Studio 2022 Community** (gratuito) desde visualstudio.microsoft.com.
2. En el instalador, marcar la carga de trabajo **"Desarrollo para el escritorio con C++"**. Esta opción ya incluye el compilador y CMake.
3. Al terminar, abrir el programa **"Developer PowerShell for VS 2022"** desde el menú Inicio. Todos los comandos de Windows se escriben ahí.

**Linux (Ubuntu / Debian)**

```bash
sudo apt update
sudo apt install build-essential cmake libeigen3-dev
```

### Paso 2. Descargar el proyecto

Opción A, con Git:

```bash
git clone https://github.com/USUARIO/taller-corte2.git
cd taller-corte2
```

Opción B, sin Git: descargar el ZIP desde GitHub (botón verde **Code → Download ZIP**), descomprimirlo y abrir una terminal dentro de la carpeta `taller-corte2`.

### Paso 3. Configurar el proyecto

Dentro de la carpeta `taller-corte2`:

```bash
cmake -S . -B build
```

Debe aparecer uno de estos dos mensajes:

```
-- Eigen: usando la version instalada en el sistema (...)
-- Eigen: usando la copia incluida en third_party/eigen
```

Cualquiera de los dos está bien.

### Paso 4. Compilar

```bash
cmake --build build --config Release
```

Al final debe decir `Built target lab2_1` y `Built target lab2_2` (o, en Windows, generar `lab2_1.exe` y `lab2_2.exe`).

### Paso 5. Ejecutar

**macOS y Linux**

```bash
./build/lab2_1
./build/lab2_2
```

**Windows (Developer PowerShell)**

```powershell
.\build\Release\lab2_1.exe
.\build\Release\lab2_2.exe
```

> Si en Windows no existe la carpeta `Release`, los ejecutables están directamente en `build\`.

---

## Abrir el proyecto en un editor (opcional)

- **VS Code:** abrir la carpeta `taller-corte2`. Instalar las extensiones *C/C++* y *CMake Tools*. Después de hacer el Paso 3 una vez, VS Code reconoce Eigen y no marca errores en rojo.
- **Qt Creator:** *File → Open File or Project* y seleccionar el archivo `CMakeLists.txt`.
- **Visual Studio 2022:** *Archivo → Abrir → Carpeta* y seleccionar `taller-corte2`. Visual Studio detecta el `CMakeLists.txt` automáticamente.

---

## Solución de problemas

| Problema | Solución |
|---|---|
| `cmake: command not found` | CMake no está instalado. Repetir el Paso 1. |
| `No CMAKE_CXX_COMPILER could be found` | Falta el compilador. En macOS: `xcode-select --install`. En Windows: usar *Developer PowerShell for VS 2022*. |
| Errores raros después de cambiar algo | Borrar la carpeta `build` y repetir desde el Paso 3. macOS/Linux: `rm -rf build`. Windows: `Remove-Item -Recurse -Force build`. |
| VS Code subraya `#include <Eigen/Dense>` en rojo | Hacer el Paso 3 al menos una vez y recargar la ventana de VS Code. Si el proyecto compila, el código está bien: el rojo es solo del editor. |

---

## Laboratorio 2.1: Tensores y Operaciones Básicas

1. **Configuración de Eigen:** se enlaza a cada ejecutable con `target_link_libraries(... Eigen3::Eigen)`.
2. **Operaciones básicas:** suma de matrices (`A + B`), producto punto (`u.dot(v)`) y transposición (`M.transpose()`).
3. **Imagen en escala de grises:** una matriz de 4 × 4 con píxeles entre 0 y 255, a la que se le aplican cuatro transformaciones:
   - Brillo: multiplicar por 1,5 con tope en 255.
   - Negativo: 255 − píxel.
   - Espejo horizontal: multiplicar por una matriz de volteo.
   - Transpuesta.

## Laboratorio 2.2: Motor de Regresión Logística

1. **Regresión lineal:** gradiente descendiente con datos de la recta y = 2x + 1. El programa llega a w = 2 y b = 1.
2. **Sigmoid:** `σ(z) = 1 / (1 + e^(−z))`, aplicada a un vector completo con Eigen.
3. **Costo Cross-Entropy:** `J = −(1/m) Σ [y·ln(p) + (1−y)·ln(1−p)]`. Con los pesos en cero, el costo inicial es ln(2) ≈ 0,6931.
4. **Gradiente descendiente:** datos de horas de estudio (1 a 10) y si el estudiante aprobó (0 o 1). En cada iteración:
   - `w = w − α · (1/m) Σ (p − y)·x`
   - `b = b − α · (1/m) Σ (p − y)`

   El costo baja de 0,6931 a 0,2511 en 5.000 iteraciones.

### Resultado esperado del Laboratorio 2.2

```
Horas | Real | Probabilidad | Prediccion
    1 |    0 |       0.0037 |          0
    2 |    0 |       0.0126 |          0
    3 |    0 |       0.0428 |          0
    4 |    0 |       0.1349 |          0
    5 |    1 |       0.3525 |          0
    6 |    0 |       0.6552 |          1
    7 |    1 |       0.8690 |          1
    8 |    1 |       0.9586 |          1
    9 |    1 |       0.9878 |          1
   10 |    1 |       0.9965 |          1
```

Las horas 5 y 6 quedan mal clasificadas porque en los datos el estudiante de 5 horas aprobó y el de 6 no. Ninguna frontera puede separar esos dos casos. No es un error del programa.

---

## Licencias

- Código de los laboratorios: Alessandro De Bonis Rodríguez.
- Eigen 3.4.0 (`third_party/eigen`): licencia MPL 2.0, ver `third_party/eigen/COPYING.MPL2`.
