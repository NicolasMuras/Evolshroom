#include <iostream>
#include <stdexcept>
#include "fungi_class.h"

Fungi::Fungi(int id)
    : Specie(id)
{
	selectFungi(id);
}

void Fungi::setHymeniumType(std::string hymenium) {
    if (hymenium.size() <= 16) {
        hymenium_type = hymenium;
    }
    else {
        hymenium_type = hymenium.substr(0, 25);
        std::cerr << "El hymenium\"" << hymenium << "\" excede la longitud maxima (16). \n" << std::endl;
    }
}
void Fungi::setCapType(std::string cap) {
    if (cap.size() <= 16) {
        cap_type = cap;
    }
    else {
        cap_type = cap.substr(0, 25);
		std::cerr << "El cap\"" << cap << "\" excede la longitud maxima (16). \n" << std::endl;
    }
}
void Fungi::setCapColor(float r, float g, float b) 
{
    if (r <= 1 && r >= 0) {
		cap_color[0] = r;
    }
    else {
		cap_color[0] = 0;
        std::cerr << "Valor fuera de rango\"" << r << "\". \n" << std::endl;
    }
	if (g <= 1 && g >= 0) {
		cap_color[1] = g;
	}
	else {
		cap_color[1] = 0;
		std::cerr << "Valor fuera de rango\"" << g << "\". \n" << std::endl;
	}
	if (r <= 1 && b >= 0) {
		cap_color[2] = b;
	}
	else {
		cap_color[2] = 0;
		std::cerr << "Valor fuera de rango\"" << b << "\". \n" << std::endl;
	}
}
void Fungi::setTrunkColor(float r, float g, float b) 
{
	if (r <= 1 && r >= 0) {
		trunk_color[0] = r;
	}
	else {
		trunk_color[0] = 0;
		std::cerr << "Valor fuera de rango\"" << r << "\". \n" << std::endl;
	}
	if (g <= 1 && g >= 0) {
		trunk_color[1] = g;
	}
	else {
		trunk_color[1] = 0;
		std::cerr << "Valor fuera de rango\"" << g << "\". \n" << std::endl;
	}
	if (r <= 1 && b >= 0) {
		trunk_color[2] = b;
	}
	else {
		trunk_color[2] = 0;
		std::cerr << "Valor fuera de rango\"" << b << "\". \n" << std::endl;
	}
}
void Fungi::setSporesColor(float r, float g, float b) 
{
	if (r <= 1 && r >= 0) {
		spores_color[0] = r;
	}
	else {
		spores_color[0] = 0;
		std::cerr << "Valor fuera de rango\"" << r << "\". \n" << std::endl;
	}
	if (g <= 1 && g >= 0) {
		spores_color[1] = g;
	}
	else {
		spores_color[1] = 0;
		std::cerr << "Valor fuera de rango\"" << g << "\". \n" << std::endl;
	}
	if (r <= 1 && b >= 0) {
		spores_color[2] = b;
	}
	else {
		spores_color[2] = 0;
		std::cerr << "Valor fuera de rango\"" << b << "\". \n" << std::endl;
	}
}

std::string Fungi::getHymeniumType() const {
    return hymenium_type;
}
std::string Fungi::getCapType() const {
    return cap_type;
}
float Fungi::getCapColor(int id) const {
    return cap_color[id];
}
float Fungi::getTrunkColor(int id) const {
    return trunk_color[id];
}
float Fungi::getSporesColor(int id) const {
    return spores_color[id];
}


void Fungi::selectFungi(int id)
{
	switch (id)
	{
	case(1):
		setHymeniumType("Gills On");
		setCapType("Convex");
		setCapColor(0.3, 0.3, 0.3);
		setTrunkColor(0.3, 0.3, 0.3);
		setSporesColor(0.1, 0.1, 0.1);
		break;
	case(2):
		setHymeniumType("Gills On");
		setCapType("Flat");
		setCapColor(0.6, 0.3, 0.1);
		setTrunkColor(0.9, 0.9, 0.7);
		setSporesColor(1, 1, 0.8);
		break;
	case(3):
		setHymeniumType("Gills On");
		setCapType("Flat");
		setCapColor(1, 0, 0);
		setTrunkColor(1, 0.9, 0.9);
		setSporesColor(1, 1, 1);
		break;
	case(4):
		setHymeniumType("Gills On");
		setCapType("Convex");
		setCapColor(1, 0.9, 0.2);
		setTrunkColor(0, 1, 0);
		setSporesColor(1, 0.9, 0.2);
		break;
	default:
		std::cerr << "[!] INVALID SHROOM ID: (1 - 4)\n";
		break;
	}
}
