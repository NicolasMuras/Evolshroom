#include <iostream>
#include <stdexcept>
using namespace std;
#include "specie_class.h"

Specie::Specie(string genre, string name, string location)
{
    setGenre(genre);
    setName(name);
    setLocation(location);
}
void Specie::setGenre(string genre_a) {
    if (genre_a.size() <= 16) {
        genre = genre_a;
    }
    else {
        genre = genre_a.substr(0, 25);
        std::cerr << "El genero\"" << genre_a << "\" excede la longitud maxima (16). \n" << std::endl;
    }
}

void Specie::setName(string name_a) {
    if (name_a.size() <= 16) {
        name = name_a;
    }
    else {
        name = name_a.substr(0, 25);
        cerr << "El nombre\"" << name_a << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Specie::setLocation(string location_a) {
    if (location_a.size() <= 16) {
        location = location_a;
    }
    else {
        location = location_a.substr(0, 25);
        cerr << "La locacion\"" << location_a << "\" excede la longitud maxima (16). \n" << endl;
    }
}

string Specie::getGenre() const {
    return genre;
}
string Specie::getName() const {
    return name;
}

string Specie::getLocation() const {
    return location;
}

void Specie::showInfo()const {
    cout << " ----------------------------------- SPECIE ----------------------------------- \n\n";
    cout << " Genre: " << getGenre() << endl;
    cout << " Name: " << getName() << endl;
    cout << " Location: " << getLocation() << endl << endl;
}