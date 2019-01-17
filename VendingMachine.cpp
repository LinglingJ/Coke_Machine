//Jessica Bao 1001124828

#include <iostream>
#include <string>
#include "VendingMachine.h"

//VendingMachine::VendingMachine(std::string name, int change)
  //          :machineName{name},changeLevel{change}
    //        {}
        std::string VendingMachine::getMachineName() 
        {
            return machineName;
        }
        void VendingMachine::setMachineName(std::string newMachineName) 
        {
            machineName=newMachineName;
        }
        int VendingMachine::getChangeLevel()
        {   
            return changeLevel;
        }
        bool VendingMachine::incrementChangeLevel(int amountToAdd)
        {
            if(amountToAdd +changeLevel<=maxChangeCapacity){
                changeLevel += amountToAdd;
                return true;
            }
            else{
                return false;
            }
        }
        int VendingMachine::getMaxChangeCapacity()
        {
            return maxChangeCapacity;
        }
        std::string VendingMachine::displayMoney(int amount)
        {
            std::string dollars;
            std::string cents;
            dollars=std::to_string(amount/100);
            cents=std::to_string(abs(amount%100));
            return('$' +dollars +'.' +(cents.size()==1? "0":"") +cents);
        }
