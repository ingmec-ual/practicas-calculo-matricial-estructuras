# ------------------------------------------------
# Sección: Configuración de CMake
# ------------------------------------------------

# Version minima de CMake que queremos soportar
cmake_minimum_required(VERSION 3.1)   

# El nombre del "proyecto" CMake, que será el nombre de la "solución" de Visual Studio
project(practica-cm)

# Usaremos como mínimo la versión C++11 del lenguaje C++
set(CMAKE_CXX_STANDARD 11)

# Usar un nivel avanzado de "warnings" para detectar posibles errores:
IF(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
ENDIF()


# ------------------------------------------------
# Sección: Declaración de librerías a "importar"
# ------------------------------------------------

# Indicar que queremos usar las cabeceras (.h) del directorio "Eigen"
SET(EIGEN_INCL_DIR "${${PROJECT_NAME}_SOURCE_DIR}")
MESSAGE(STATUS "Usando directorio Eigen: ${EIGEN_INCL_DIR}/Eigen")
include_directories(${EIGEN_INCL_DIR})


# ---------------------------------------------------------------------
# Sección: DECLARACIÓN DE "TARGETS": nuestros programas y librerías
# Cada uno será un "proyecto" de Visual Studio.
# ---------------------------------------------------------------------

# Definir programa ejecutable: ejemplo C++ básico
add_executable(
	# Nombre del ejecutable
	ejemplo_cpp
	# Lista de ficheros de código fuente a compilar en este "target":
	ejemplo_cpp.cpp
)

# Definir programa ejecutable: práctica de cálculo matricial #1 
add_executable(
	# Nombre del ejecutable
	practica1
	# Lista de ficheros de código fuente a compilar en este "target":
	practica1.cpp
	libcalculomatricial.h  libcalculomatricial.cpp
	eigen_indexing.h
)

