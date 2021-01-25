#include <iostream>
#include <stdexcept>
using namespace std;
#include "fungi_class.h"
#include "strain_class.h"

Strain::Strain(string strainname, string genre, string name, string location, string hymenium, string cap, string capcolor, string trunkcolor, string sporescolor, string gills)
    : Fungi(genre, name, location, hymenium, cap, capcolor, trunkcolor, sporescolor, gills)
{
    setStrainName(strainname);
}

void Strain::setStrainName(string strainname) {
    if (strainname.size() <= 16) {
        strain_name = strainname;
    }
    else {
        strain_name = strainname.substr(0, 25);
        cerr << "El strain_name\"" << strainname << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Strain::setColonizationMinTemp(float colonizationmintemp) {
    if (colonizationmintemp <= 16) {
        colonization_min_temp = colonizationmintemp;
    }
    else {
        cerr << "El colonization_min_temp\"" << colonizationmintemp << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Strain::setColonizationMaxTemp(float colonizationmaxtemp) {
    if (colonizationmaxtemp <= 16) {
        colonization_max_temp = colonizationmaxtemp;
    }
    else {
        cerr << "El colonization_max_temp\"" << colonizationmaxtemp << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Strain::setColonizationMinHumd(float colonizationminhumd) {
    if (colonizationminhumd <= 16) {
        colonization_min_humd = colonizationminhumd;
    }
    else {
        cerr << "El colonization_min_humd\"" << colonizationminhumd << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Strain::setColonizationMaxHumd(float colonizationmaxhumd) {
    if (colonizationmaxhumd <= 16) {
        colonization_max_humd = colonizationmaxhumd;
    }
    else {
        cerr << "El colonization_max_humd\"" << colonizationmaxhumd << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Strain::setColonizationSpeed(float colonizationspeed) {
    if (colonizationspeed <= 16) {
        colonization_speed = colonizationspeed;
    }
    else {
        cerr << "El colonization_speed\"" << colonizationspeed << "\" excede la longitud maxima (16). \n" << endl;
    }
}



void Strain::setFructificationMinTemp(float fructificationmintemp) {
    if (fructificationmintemp <= 16) {
        fructification_min_temp = fructificationmintemp;
    }
    else {
        cerr << "El fructification_min_temp\"" << fructificationmintemp << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Strain::setFructificationMaxTemp(float fructificationmaxtemp) {
    if (fructificationmaxtemp <= 16) {
        fructification_max_temp = fructificationmaxtemp;
    }
    else {
        cerr << "El fructification_max_temp\"" << fructificationmaxtemp << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Strain::setFructificationMinHumd(float fructificationminhumd) {
    if (fructificationminhumd <= 16) {
        fructification_min_humd = fructificationminhumd;
    }
    else {
        cerr << "El fructification_min_humd\"" << fructificationminhumd << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Strain::setFructificationMaxHumd(float fructificationmaxhumd) {
    if (fructificationmaxhumd <= 16) {
        fructification_max_humd = fructificationmaxhumd;
    }
    else {
        cerr << "El fructification_max_humd\"" << fructificationmaxhumd << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Strain::setFructificationSpeed(float fructificationspeed) {
    if (fructificationspeed <= 16) {
        fructification_speed = fructificationspeed;
    }
    else {
        cerr << "El fructification_speed\"" << fructificationspeed << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Strain::setPinningAbundance(float pinningabundance) {
    if (pinningabundance <= 16) {
        pinning_abundance = pinningabundance;
    }
    else {
        cerr << "El pinning_abundance\"" << pinningabundance << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Strain::setSporeAbundance(float sporeabundance) {
    if (sporeabundance <= 16) {
        spore_abundance = sporeabundance;
    }
    else {
        cerr << "El spore_abundance\"" << sporeabundance << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Strain::setResistanceLevel(float resistancelevel) {
    if (resistancelevel <= 16) {
        resistance_level = resistancelevel;
    }
    else {
        cerr << "El resistance_level\"" << resistancelevel << "\" excede la longitud maxima (16). \n" << endl;
    }
}

void Strain::setColorDifference(float colordifference) {
    if (colordifference <= 16) {
        color_difference = colordifference;
    }
    else {
        cerr << "El color_difference\"" << colordifference << "\" excede la longitud maxima (16). \n" << endl;
    }
}



string Strain::getStrainName() const {
    return strain_name;
}