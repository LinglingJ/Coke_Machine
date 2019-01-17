//Jessica Bao 1001124828
#ifndef COKE_MACHINE_H      //INCLUDE GUARRRD
#define COKE_MACHINE_H
#include "VendingMachine.h"
class CokeMachine : public VendingMachine
{   
    friend std::ostream& operator<<(std::ostream& output, CokeMachine& MyCokeMachine);
    friend std::string CreateCokeOutputLine(CokeMachine& MyCokeMachine);
    public:
        CokeMachine(std::string name = "New Machine",int cost = 50,int change = 500, int inventory = 100);
        void get_command_line_params(int argc, char* argv[], std::string* Input_File, std::string* Output_File);
        //void setMachineName(std::string newMachineName);
        void setCokePrice(int newCokePrice);
        //std::string getMachineName();
        bool buyACoke(int payment,std::string& change,int& action);
        int getInventoryLevel();
        int getMaxInventoryCapacity();
        bool incrementInventory(int amountToAdd);
        //std::string getChangeLevel();
        //bool incrementChangeLevel(int amountToAdd);
        //std::string getMaxChangeCapacity();
        std::string getCokePrice();
        //std::string displayMoney(int amount);
        ~CokeMachine();
    private:
        //std::string machineName;
        //int changeLevel;
        //int maxChangeCapacity = 5000;
        int CokePrice;
        int inventoryLevel;
        int maxInventoryCapacity = 100;

};
#endif

