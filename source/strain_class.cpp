#include <iostream>
#include <stdexcept>

#include "strain_class.h"

Strain::Strain(int id)
    : Fungi(id)
{
	selectStrain(id);
}

void Strain::setID(int id) {
	if (id <= 4 && id >= 1) {
		ID = id;
	}
	else {
		std::cerr << "El id\"" << id << "\" esta fuera de rango. \n" << std::endl;
	}
}

void Strain::setStrainName(std::string strainname) {
    if (strainname.size() <= 16) {
        strain_name = strainname;
    }
    else {
        strain_name = strainname.substr(0, 25);
		std::cerr << "El strain_name\"" << strainname << "\" excede la longitud maxima (16). \n" << std::endl;
    }
}

void Strain::setFructificationMinTemp(float fructificationmintemp) {
    if (fructificationmintemp >= 0) {
        fructification_min_temp = fructificationmintemp;
    }
    else {
		std::cerr << "El fructification_min_temp\"" << fructificationmintemp << "\" excede la longitud maxima (16). \n" << std::endl;
    }
}

void Strain::setFructificationMaxTemp(float fructificationmaxtemp) {
    if (fructificationmaxtemp <= 40) {
        fructification_max_temp = fructificationmaxtemp;
    }
    else {
		std::cerr << "El fructification_max_temp\"" << fructificationmaxtemp << "\" excede la longitud maxima (16). \n" << std::endl;
    }
}

void Strain::setFructificationMinHumd(float fructificationminhumd) {
    if (fructificationminhumd >= 0) {
        fructification_min_humd = fructificationminhumd;
    }
    else {
		std::cerr << "El fructification_min_humd\"" << fructificationminhumd << "\" excede la longitud maxima (16). \n" << std::endl;
    }
}

void Strain::setFructificationMaxHumd(float fructificationmaxhumd) {
    if (fructificationmaxhumd <= 100) {
        fructification_max_humd = fructificationmaxhumd;
    }
    else {
		std::cerr << "El fructification_max_humd\"" << fructificationmaxhumd << "\" excede la longitud maxima (16). \n" << std::endl;
    }
}

void Strain::setFructificationSpeed(float fructificationspeed) {
    if (fructificationspeed <= 40) {
        fructification_speed = fructificationspeed;
    }
    else {
		std::cerr << "El fructification_speed\"" << fructificationspeed << "\" excede la longitud maxima (16). \n" << std::endl;
    }
}

void Strain::setColorDifference(float red, float green, float blue) {
    if (red <= 1.0 && red >= 0.0) {
        color_difference += red;
    }
    else {
        std::cerr << "Valor: \"" << red << "\" fuera de rango. \n" << std::endl;
    }
	if (green <= 1.0 && green >= 0.0) {
		color_difference += green;
	}
	else {
		std::cerr << "Valor: \"" << green << "\" fuera de rango. \n" << std::endl;
	}
	if (blue <= 1.0 && blue >= 0.0) {
		color_difference += blue;
	}
	else {
		std::cerr << "Valor: \"" << blue << "\" fuera de rango. \n" << std::endl;
	}
}


int Strain::getID() const
{
	return ID;
}

std::string Strain::getStrainName() const {
    return strain_name;
}

void Strain::selectStrain(int id)
{
	switch (id) 
	{
	case(1):
		setID(1);
		setStrainName("Goliath");
		setFructificationMinTemp(23.0);
		setFructificationMaxTemp(27.0);
		setFructificationMinHumd(92.0);
		setFructificationMaxHumd(95.0);
		setFructificationSpeed(12.0);
		setColorDifference(0.01, 0.01, 0.02);
		break;
	case(2):
		setID(2);
		setStrainName("");
		setFructificationMinTemp(21.0);
		setFructificationMaxTemp(25.0);
		setFructificationMinHumd(85.0);
		setFructificationMaxHumd(95.0);
		setFructificationSpeed(16.0);
		setColorDifference(0.02, 0.01, 0.01);
		break;
	case(3):
		setID(3);
		setStrainName("");
		setFructificationMinTemp(23.8);
		setFructificationMaxTemp(29.4);
		setFructificationMinHumd(85.0);
		setFructificationMaxHumd(95.0);
		setFructificationSpeed(10.0);
		setColorDifference(0.01, 0.01, 0.00);
		break;
	case(4):
		setID(4);
		setStrainName("");
		setFructificationMinTemp(27.0);
		setFructificationMaxTemp(32.0);
		setFructificationMinHumd(95.0);
		setFructificationMaxHumd(100.0);
		setFructificationSpeed(10.0);
		setColorDifference(0.00, 0.01, 0.01);
		break;
	default:
		std::cerr << "[!] INVALID SHROOM ID: (1 - 4)\n";
		break;
	}
}
