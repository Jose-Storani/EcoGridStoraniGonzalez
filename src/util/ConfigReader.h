#pragma once

#include <fstream>
#include <string>
#include <unordered_map>
#include <stdexcept>

class ConfigReader {
public:
    static std::unordered_map<std::string, std::string> leer(const std::string& rutaArchivo) {
        std::unordered_map<std::string, std::string> valores;
        std::ifstream archivo(rutaArchivo);
        if (!archivo.is_open())
            throw std::runtime_error("No se pudo abrir el archivo de configuracion: " + rutaArchivo);

        std::string linea;
        while (std::getline(archivo, linea)) {
            if (linea.empty() || linea[0] == '#' || linea[0] == ';') continue;

            auto pos = linea.find('=');
            if (pos == std::string::npos) continue;

            std::string clave = linea.substr(0, pos);
            std::string valor = linea.substr(pos + 1);
            valores[clave] = valor;
        }
        return valores;
    }
};
