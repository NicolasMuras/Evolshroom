#include <string>
#include "fungi_class.h"
#ifndef STRAIN_H
#define STRAIN_H

class Strain : public Fungi
{
public:
    explicit Strain(int id);

    // SET
	void setID(int);
    void setStrainName(std::string);
    void setFructificationMinTemp(float);
    void setFructificationMaxTemp(float);
    void setFructificationMinHumd(float);
    void setFructificationMaxHumd(float);
    void setFructificationSpeed(float);
    void setColorDifference(float, float, float);

    // GET
	int getID() const;
    std::string getStrainName() const;

	void selectStrain(int);

private:
	int ID = 0;
    std::string strain_name;
    float fructification_min_temp;
    float fructification_max_temp;
    float fructification_min_humd;
    float fructification_max_humd;
    float fructification_speed;
    float color_difference;
};
#endif // STRAIN_H
