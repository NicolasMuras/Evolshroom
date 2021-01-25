#include <string>
#ifndef SPECIE_H
#define SPECIE_H

class Specie
{
public:
    explicit Specie(std::string, std::string, std::string);

    // SET

    void setGenre(std::string);
    void setName(std::string);
    void setLocation(std::string);

    // GET

    std::string getGenre()const;
    std::string getName()const;
    std::string getLocation()const;

    // FUNCTIONS

    void showInfo()const;

private:
    std::string genre;
    std::string name;
    std::string location;
};
#endif // SPECIE_H
