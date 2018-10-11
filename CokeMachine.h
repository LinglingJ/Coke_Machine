//Jessica Bao 1001124828
class CokeMachine
{   
    
    public:
        CokeMachine(std::string name,int cost,int change, int inventory)
            :machineName{name},CokePrice{cost},changeLevel{change},inventoryLevel{inventory}
            {}
        std::string getMachineName() 
        {
            return machineName;
        }
        bool buyACoke(int payment,std::string& change,int& action)
        {
            if(inventoryLevel==0) {
                action = 1;
            } else if(stoi(change)>changeLevel) {
                action = 2;
            } else if(payment<CokePrice) {
                action = 3;
            } else if(payment==CokePrice) {
                action = 4;
                inventoryLevel--;
                if (changeLevel +CokePrice<=maxChangeCapacity)
                changeLevel += CokePrice;
            } else {
                action = 0;
                inventoryLevel--;
                change = displayMoney(stoi(change));
                if(changeLevel +payment-CokePrice<=maxChangeCapacity){
                changeLevel=changeLevel +payment-CokePrice;
                }
            }
            return !(action%4);
        }
        
        int getInventoryLevel()
        {
            return inventoryLevel;
        }
        int getMaxInventoryCapacity()
        {
            return maxInventoryCapacity;
        }
        bool incrementInventory(int amountToAdd)
        {
            if (amountToAdd +inventoryLevel<=maxInventoryCapacity){
                inventoryLevel += amountToAdd;                
                return true;
            }
            else{
                return false;
            }
        }
        
        std::string getChangeLevel()
        {   
            return displayMoney(changeLevel);
        }
        bool incrementChangeLevel(int amountToAdd)
        {
            if(amountToAdd +changeLevel<=maxChangeCapacity){
                changeLevel += amountToAdd;
                return true;
            }
            else{
                return false;
            }

        }
        std::string getMaxChangeCapacity()
        {
            return displayMoney(maxChangeCapacity);
        }
        
        std::string getCokePrice()
        {
            return displayMoney(CokePrice);    
        }
        std::string displayMoney(int amount)
        {
            std::string dollars;
            std::string cents;
            dollars=std::to_string(amount/100);
            cents=std::to_string(abs(amount%100));
            return('$' +dollars +'.' +(cents.size()==1? "0":"") +cents);
        }

    private:
        std::string machineName;
        int changeLevel;
        int maxChangeCapacity = 5000;
        int CokePrice;
        int inventoryLevel;
        int maxInventoryCapacity = 100;
        


};


