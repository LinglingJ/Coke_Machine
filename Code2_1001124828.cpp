//Jessica Bao 1001124828

#include <iostream>
#include <iomanip>
#include <string>
#include "CokeMachine.h"
using namespace std;

int main()
{
    //Initializing variables
    int choice;
    int payment;
    int action;
    int restock;
    int amountToAdd;
    string change;
    enum ACTION {OK, NOINVENTORY, NOCHANGE, INSUFFICIENTFUNDS, EXACTCHANGE};
    CokeMachine MyCokeMachine{"CSE 1325 Coke Machine", 50, 500, 100};
    do{
    //Creating Menu to use coke machine
    cout<<endl<<endl<<MyCokeMachine.getMachineName()<<endl<<endl;
    cout<<"0.   Walk away"<<endl;
    cout<<"1.   Buy a Coke"<<endl;
    cout<<"2.   Restock Machine"<<endl;
    cout<<"3.   Add change"<<endl;
    cout<<"4.   Display Machine Info"<<endl<<endl;

    cin>>choice;
    switch(choice){
    case 0: 
        cout<<"Good choice, Cokes aren't good for you"<<endl<<endl;
        break;
    case 1: 
        cout<<"Insert payment ";
        cin>>payment;
        cout<<"\n"<<endl;
        change=to_string(payment-50);
        if (MyCokeMachine.buyACoke(payment,change,action)){
            if(action==ACTION(OK)){
            cout<<"Here's your Coke and your change of "+change<<endl;
            }
            else {
                cout<<"Thank you for exact change"<<endl;
                cout<<"Here's your Coke"<<endl;
            }
        }
        else{
            if (action==ACTION(NOINVENTORY)){
                cout<<"Out of Coke"<<endl;
            }
            else if(action==ACTION(NOCHANGE)){
                cout<<"Unable to give change at this time...returning your payment"<<endl;
            }
            else{
                cout<<"Insufficent payment...returning your payment"<<endl;
            }
        }
        break;
        cout<<"You did not select a number on the menu options"<<endl;
        case 2:
        cout<<"How much product are you adding to the machine? ";
        cin>>restock;
        if(MyCokeMachine.incrementInventory(restock)){
            cout<<"Your inventory has been restocked"<<endl;
            cout<<"Your inventory level is now "+to_string(MyCokeMachine.getInventoryLevel());
        }
        else{
            cout<<"You have exceeded your machine's max capacity"<<endl;
            cout<<"Your inventory level is now "+to_string(MyCokeMachine.getInventoryLevel())<<endl;
        }
        break;
        case 3:
        cout<<"How much change are you adding to the machine? ";
        cin>>amountToAdd;
        if(MyCokeMachine.incrementChangeLevel(amountToAdd)){
            cout<<"Your change has been updated"<<endl;
            cout<<"Your change level is now "+MyCokeMachine.getChangeLevel()<<endl;
        }
        else{
            cout<<"You have exceeded your machine's max change capacity"<<endl;
            cout<<"Your change level is now "+MyCokeMachine.getChangeLevel()<<endl;
        }
        break;
        case 4:
        cout<<"Current Inventory Level "+to_string(MyCokeMachine.getInventoryLevel())<<endl;
        cout<<"Max Inventory Capacity "+to_string(MyCokeMachine.getMaxInventoryCapacity())<<endl;
        cout<<"\nCurrent Change Level "+MyCokeMachine.getChangeLevel()<<endl;
        cout<<"Max Change Capacity "+MyCokeMachine.getMaxChangeCapacity()<<endl;
        cout<<"\nCurrent Coke price is "+MyCokeMachine.getCokePrice()<<endl;
        cout<<"\n"+MyCokeMachine.getMachineName()<<endl;
        break;
        default:
        cout<<"Please pick a number on the menu list"<<endl;
        break;
    }
    }while(choice!=0);
    
    return 0;
}