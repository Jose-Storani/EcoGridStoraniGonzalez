cmake_minimum_required(VERSION 3.15)
project(EcoGrid LANGUAGES CXX)

# Forzar el uso de C++17 requerido por la cátedra
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------------------------------
# CONFIGURACIÓN DE RUTAS LOCALES DE SOCI
# -------------------------------------------------------------------------
# Definimos la ruta raíz donde clonaste y compilaste SOCI en tu máquina
set(SOCI_DIR CUsersRosarioDesktopsoci)
set(SOCI_BUILD_DIR ${SOCI_DIR}build)

# -------------------------------------------------------------------------
# DECLARACIÓN DEL EJECUTABLE
# -------------------------------------------------------------------------
# Reemplaza 'main.cpp' por la lista de todos tus archivos fuentes (.cpp) 
# a medida que los vayas creando (ej Nodo.cpp, GridManager.cpp, etc.)
add_executable(EcoGrid main.cpp)

# -------------------------------------------------------------------------
# CONECTAR LOS ENCABEZADOS (HEADERS)
# -------------------------------------------------------------------------
# Le indicamos al compilador dónde buscar los archivos de cabecera de SOCI
target_include_directories(EcoGrid PRIVATE
    ${SOCI_DIR}include
)

# -------------------------------------------------------------------------
# BUSCAR Y VINCULAR LAS LIBRERÍAS (LINKING)
# -------------------------------------------------------------------------
# Buscamos el componente Core de SOCI en la carpeta build local
find_library(SOCI_CORE_LIB
    NAMES soci_core libsoci_core libsoci_core_4_2
    PATHS ${SOCI_BUILD_DIR}lib ${SOCI_BUILD_DIR}bin
    NO_DEFAULT_PATH
)

# Buscamos el backend de Oracle de SOCI en la carpeta build local
find_library(SOCI_ORACLE_LIB
    NAMES soci_oracle libsoci_oracle libsoci_oracle_4_2
    PATHS ${SOCI_BUILD_DIR}lib ${SOCI_BUILD_DIR}bin
    NO_DEFAULT_PATH
)

# Verificación de seguridad en tiempo de configuración de CMake
if(NOT SOCI_CORE_LIB OR NOT SOCI_ORACLE_LIB)
    message(FATAL_ERROR ¡Error crítico! No se encontraron las librerías de SOCI compiladas. Revisa las rutas en tu CMakeLists.txt.)
endif()

# Vinculamos los binarios encontrados a nuestro ejecutable EcoGrid
target_link_libraries(EcoGrid PRIVATE
    ${SOCI_CORE_LIB}
    ${SOCI_ORACLE_LIB}
)