// Jessica Bao 1001124828
#ifndef VENDING_MACHINE_H      //INCLUDE GUARRRD
#define VENDING_MACHINE_H

class VendingMachine
{
public:
    //Pure virtual  functions
     virtual int getInventoryLevel() = 0;
     virtual int getMaxInventoryCapacity() = 0;
     virtual bool incrementInventory(int amountToAdd) = 0;

    //Regular Functions
        std::string getMachineName();
        void setMachineName(std::string newMachineName);
        int getChangeLevel();
        bool incrementChangeLevel(int amountToAdd);
        int getMaxChangeCapacity();
        std::string displayMoney(int amount);
private:
        std::string machineName;
        int changeLevel = 0;
        int maxChangeCapacity = 5000;

};
#endif
