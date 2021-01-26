#include <iostream>
#include <stdexcept>
using namespace std;
#include "specie_class.h"

Specie::Specie(int id)
{
	selectSpecie(id);
}
void Specie::setFamily(string family_a) {
    if (family_a.size() <= 30) {
        family = family_a;
    }
    else {
		family = family_a.substr(0, 45);
        std::cerr << "La familia\"" << family_a << "\" excede la longitud maxima (16). \n" << std::endl;
    }
}
void Specie::setName(string name_a) {
    if (name_a.size() <= 30) {
        name = name_a;
    }
    else {
        name = name_a.substr(0, 45);
        cerr << "El nombre\"" << name_a << "\" excede la longitud maxima (16). \n" << endl;
    }
}
void Specie::setBiome(string biome_a) {
    if (biome_a.size() <= 30) {
        biome = biome_a;
    }
    else {
		biome = biome_a.substr(0, 45);
        cerr << "El bioma\"" << biome_a << "\" excede la longitud maxima (16). \n" << endl;
    }
}

string Specie::getFamily() const {
    return family;
}
string Specie::getName() const {
    return name;
}
string Specie::getBiome() const {
    return biome;
}

void Specie::selectSpecie(int id)
{
	switch (id)
	{
	case(1):
		setFamily("Bolbitiaceae");
		setName("Panaeolus Cyanescens");
		setBiome("Tropical");
		break;
	case(2):
		setFamily("Strophariaceae");
		setName("Kuehneromyces mutabilis");
		setBiome("Forest");
		break;
	case(3):
		setFamily("Amanitaceae");
		setName("Amanita Muscaria");
		setBiome("Boreal");
		break;
	case(4):
		setFamily("Bolbitiaceae");
		setName("Roridomyces Phyllostachys");
		setBiome("Asian Forest");
		break;
	default:
		std::cerr << "[!] INVALID SHROOM ID: (1 - 4)\n";
		break;
	}
}
void Specie::showInfo()const {
    cout << " ----------------------------------- SPECIE ----------------------------------- \n\n";
    cout << " Genre: " << getFamily() << endl;
    cout << " Name: " << getName() << endl;
    cout << " Location: " << getBiome() << endl << endl;
}
