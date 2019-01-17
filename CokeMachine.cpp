//Jessica Bao 1001124828

#include <iostream>
#include <string>
#include "CokeMachine.h"

CokeMachine::CokeMachine(std::string name, int cost, int change, int inventory)
            :CokePrice{cost},inventoryLevel{inventory}
            {  
                setMachineName(name);
                incrementChangeLevel(change);
            }
        void CokeMachine::get_command_line_params(int argc, char* argv[], std::string* Input_File, std::string* Output_File)
        {
            int i;
            std::string cla;
            if(argc==1)
            {
                throw std::invalid_argument("Missing command line parameters - - USAGE : INPUTFILENAME= OUTPUTFILENAME=");
            }
  
            for (i = 1; i < argc; i++)
            {
                cla = argv[i];
                //std::cout<<"My cla string is: "<<cla<<std::endl;
                if (cla.substr(0, cla.find("=")) == "INPUTFILENAME")
                {
                    *Input_File = cla.substr(cla.find("=")+1, cla.length());
                }
                else if(cla.substr(0, cla.find("=")) == "OUTPUTFILENAME")
                {
                        *Output_File = cla.substr(cla.find("=")+1, cla.length());
                        //std::cout<<"My Output_File is: "<<*Output_File<<std::endl;
                        i=argc;

                }
                else
                {
                    throw std::invalid_argument("Missing command line parameters - - USAGE : INPUTFILENAME= OUTPUTFILENAME=");
                    i=argc;
                }
            }
        }

     int CokeMachine::getInventoryLevel()
        {
            return inventoryLevel;
        }
     int CokeMachine::getMaxInventoryCapacity()
        {
            return maxInventoryCapacity;
        }
     bool CokeMachine::incrementInventory(int amountToAdd)
        {
            if (amountToAdd +inventoryLevel<=maxInventoryCapacity){
                inventoryLevel += amountToAdd;                
                return true;
            }
            else{
                return false;
            }
        }


        void CokeMachine::setCokePrice(int newCokePrice)
        {
            CokePrice = newCokePrice;
        }
        bool CokeMachine::buyACoke(int payment,std::string& change,int& action)
        {
            
            if(inventoryLevel==0) {
                action = 1;
            } else if((payment-CokePrice)>getChangeLevel()) {
                action = 2;
            } else if(payment<CokePrice) {
                action = 3;
            } else if(payment==CokePrice) {
                action = 4;
                inventoryLevel--;
                if (getChangeLevel() +CokePrice<=getMaxChangeCapacity())
                    incrementChangeLevel(CokePrice);
            } else {
                action = 0;
                inventoryLevel--;
                change = displayMoney(payment-CokePrice);
                if(getChangeLevel() +payment-CokePrice<=getMaxChangeCapacity()){
                incrementChangeLevel(payment-CokePrice);
                }
            }
            return !(action%4);
        }
        
        
        std::string CokeMachine::getCokePrice()
        {
            return displayMoney(CokePrice);    
        }
        
        CokeMachine::~CokeMachine()
        {  }

