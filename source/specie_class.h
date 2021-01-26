#include <string>
#ifndef SPECIE_H
#define SPECIE_H

class Specie
{
public:
    explicit Specie(int id);

    // SET

    void setFamily(std::string);
    void setName(std::string);
    void setBiome(std::string);

    // GET

    std::string getFamily()const;
	std::string getName()const;
    std::string getBiome()const;

    // FUNCTIONS

	void selectSpecie(int);
    void showInfo()const;

private:
    std::string family;
    std::string name;
    std::string biome;
};
#endif // SPECIE_H
