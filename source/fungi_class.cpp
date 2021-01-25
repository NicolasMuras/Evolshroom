#include <iostream>
#include <stdexcept>
using namespace std;
#include "fungi_class.h"

Fungi::Fungi(string genre, string name, string location, string hymenium, string cap, string capcolor, string trunkcolor, string sporescolor, string gills)
    : Specie(genre, name, location)
{
	setHymeniumType(hymenium);
	setCapType(cap);
	setCapColor(capcolor);
	setTrunkColor(trunkcolor);
	setSporesColor(sporescolor);
	setGillsType(gills);
}

void Fungi::setHymeniumType(string hymenium) {
    if (hymenium.size() <= 16) {
        hymenium_type = hymenium;
    }
    else {
        hymenium_type = hymenium.substr(0, 25);
        cerr << "El hymenium\"" << hymenium << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Fungi::setCapType(string cap) {
    if (cap.size() <= 16) {
        cap_type = cap;
    }
    else {
        cap_type = cap.substr(0, 25);
        cerr << "El cap\"" << cap << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Fungi::setCapColor(string capcolor) {
    if (capcolor.size() <= 16) {
        cap_color = capcolor;
    }
    else {
        cap_color = capcolor.substr(0, 25);
        cerr << "El cap_color\"" << capcolor << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Fungi::setTrunkColor(string trunkcolor) {
    if (trunkcolor.size() <= 16) {
        trunk_color = trunkcolor;
    }
    else {
        trunk_color = trunkcolor.substr(0, 25);
        cerr << "El trunk_color\"" << trunkcolor << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Fungi::setSporesColor(string sporescolor) {
    if (sporescolor.size() <= 16) {
        spores_color = sporescolor;
    }
    else {
        spores_color = sporescolor.substr(0, 25);
        cerr << "El spores_color\"" << sporescolor << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Fungi::setGillsType(string gills) {
    if (gills.size() <= 16) {
        gills_type = gills;
    }
    else {
        gills_type = gills.substr(0, 25);
        cerr << "El gills_type\"" << gills << "\" excede la longitud maxima (16). \n" << endl;
    }
}

string Fungi::getHymeniumType() const {
    return hymenium_type;
}
string Fungi::getCapType() const {
    return cap_type;
}

string Fungi::getCapColor() const {
    return cap_color;
}

string Fungi::getTrunkColor() const {
    return trunk_color;
}
string Fungi::getSporesColor() const {
    return spores_color;
}

string Fungi::getGillsType() const {
    return gills_type;
}
