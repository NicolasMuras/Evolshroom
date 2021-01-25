#include <string>
#ifndef STRAIN_H
#define STRAIN_H

class Strain : public Fungi
{
public:
    explicit Strain(string, string, string, string, string, string, string, string, string, string);

    // SET

    void setStrainName(string);
    void setColonizationMinTemp(float);
    void setColonizationMaxTemp(float);
    void setColonizationMinHumd(float);
    void setColonizationMaxHumd(float);
    void setColonizationSpeed(float);

    void setFructificationMinTemp(float);
    void setFructificationMaxTemp(float);
    void setFructificationMinHumd(float);
    void setFructificationMaxHumd(float);
    void setFructificationSpeed(float);

    void setPinningAbundance(float);
    void setSporeAbundance(float);
    void setResistanceLevel(float);

    void setColorDifference(float);

    // GET

    string getStrainName() const;
    float getColonizationMinTemp() const;
    float getColonizationMaxTemp() const;
    float getColonizationMinHumd() const;
    float getColonizationMaxHumd() const;
    float getColonizationSpeed() const;

    float getFructificationMinTemp() const;
    float getFructificationMaxTemp() const;
    float getFructificationMinHumd() const;
    float getFructificationMaxHumd() const;
    float getFructificationSpeed() const;

    float getPinningAbundance() const;
    float getSporeAbundance() const;
    float getResistanceLevel() const;
    float getColorDifference() const;

private:
    string strain_name;
    float colonization_min_temp;
    float colonization_max_temp;
    float colonization_min_humd;
    float colonization_max_humd;
    float colonization_speed;

    float fructification_min_temp;
    float fructification_max_temp;
    float fructification_min_humd;
    float fructification_max_humd;
    float fructification_speed;

    float pinning_abundance;
    float spore_abundance;
    float resistance_level;
    float color_difference;
};
#endif // STRAIN_H
