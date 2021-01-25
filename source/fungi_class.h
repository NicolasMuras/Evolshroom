#include <string>
#include "specie_class.h"
#ifndef FUNGI_H
#define FUNGI_H

class Fungi : public Specie
{
public:
    explicit Fungi(std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string);

    // SET

    void setHymeniumType(std::string);
    void setCapType(std::string);
    void setCapColor(std::string);
    void setTrunkColor(std::string);
    void setSporesColor(std::string);
    void setGillsType(std::string);

    // GET

    std::string getHymeniumType()const;
    std::string getCapType()const;
    std::string getCapColor()const;
    std::string getTrunkColor()const;
    std::string getSporesColor()const;
    std::string getGillsType()const;

private:
    std::string hymenium_type;
    std::string cap_type;
    std::string cap_color;
    std::string trunk_color;
    std::string spores_color;
    std::string gills_type;
};
#endif // FUNGI_H