#include <string>
#include "specie_class.h"
#ifndef FUNGI_H
#define FUNGI_H

class Fungi : public Specie
{
public:
    explicit Fungi(int id);

    // SET

    void setHymeniumType(std::string);
    void setCapType(std::string);
    void setCapColor(float, float, float);
    void setTrunkColor(float, float, float);
    void setSporesColor(float, float, float);

    // GET

    std::string getHymeniumType()const;
    std::string getCapType()const;
	float getCapColor(int id)const;
	float getTrunkColor(int id)const;
	float getSporesColor(int id)const;

	void selectFungi(int);

	// CONST VARS
	
private:
    std::string hymenium_type;
    std::string cap_type;
	float cap_color[3];
	float trunk_color[3];
	float spores_color[3];
};
#endif // FUNGI_H
