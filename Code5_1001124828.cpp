// Jessica Bao 1001124828


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include "CokeMachine.h"
#include "VendingMachine.h"
#include "CokeLib.h"
#include <map>
#include <sstream>
#include <gtkmm.h>

using namespace std;

//function declarations
int CokeMenu(CokeMachine& MyCokeMachine);
int getPayment();
int getRestock();
int getChange();
int getNewCokePrice();
string getNewMachineName();

int main(int argc, char* argv[])
{
    Gtk::Main kit(argc, argv);

    //Initializing variables--------------------------------------------------------------------------------------------------------
    int choice;
    int i = 0;
    int k;
    string Input_File;
    string Output_File;
    string CokeMachineLine;
    vector<CokeMachine> SetOfCokeMachines;
    vector<string> ConstructorValues(4);
    ifstream CokeInputFile;
    ofstream CokeOutputFile;
    int payment;
    string change;
    string newMachineName;
    int action;
    int restock;
    int amountToAdd;
    int newCokePrice;
    enum ACTION {OK, NOINVENTORY, NOCHANGE, INSUFFICIENTFUNDS, EXACTCHANGE};
    map<string,int> MyMap;
    ostringstream objOutput; 


    //Initializing Coke Machine----------------------------------------------------------------------------------------------------
    CokeMachine MyCokeMachine{"CSE 1325 Coke Machine", 50, 500, 100};
    CokeMachine CokeMachine_Default;
    //Getting command line parameters-----------------------------------------------------------------------------------------------
    try
    {
        MyCokeMachine.get_command_line_params(argc, argv, &Input_File, &Output_File);
    }
    catch(invalid_argument& say)
    {
        cout<<say.what()<<endl;
        return 0;
    }

    CokeInputFile.open(Input_File,ios::in);
    CokeOutputFile.open(Output_File,ios::out);
    if(CokeInputFile.is_open())
    {   
        while(!CokeInputFile.eof())
        {   
            getline(CokeInputFile,CokeMachineLine);
            if(ParseCokeLine(CokeMachineLine, ConstructorValues))
            {
                CokeMachine Temp_Machine{ConstructorValues[0],stoi(ConstructorValues[1]),stoi(ConstructorValues[2]),stoi(ConstructorValues[3])};
                SetOfCokeMachines.push_back(Temp_Machine);
                i++;
            }
        }
        CokeInputFile.clear();
    }
    else
    {
        cout<<"Unable to open file"<<endl;
        exit(0);
    }
            CokeInputFile.close();

int a= 0;
do{
    //Creating Menu to use coke machine--------------------------------------------------------------------------------------------
    cout<<endl<<endl<<"Pick a Coke Machine"<<endl<<endl;
    cout<<"0. Exit"<<endl;
    int a = 0;
    for(auto j : SetOfCokeMachines)  //Range based for loop
    {
        a++;
    cout<<a<<"  "<<SetOfCokeMachines[a-1].getMachineName()<<endl;
    }
    a=a+1;
    cout<<a<<"  Add a new machine"<<endl;
    cout<<"Enter a choice ";
    cin>>choice;
    string Line;
    
    switch(choice){
    case 0:
            cout<<"\nYour Coke Reciept"<<endl;
            for (auto mapItem : MyMap)
            {
            cout << mapItem.first << " : " << mapItem.second << endl;
            }
         if (CokeOutputFile.is_open())
            {
                
                for(int z=0;z<(a-1);z++)
                {
                    Line= CreateCokeOutputLine(SetOfCokeMachines[z]);
                    CokeOutputFile<<Line<<endl;   
                }
                CokeOutputFile.close();
            }
            else 
            {
                cout << "Unable to open file";
            }
            return 0;
        break;
    default: 
        if(choice<a)
        {
            MyCokeMachine = SetOfCokeMachines[choice-1];
        }
        else if(choice==(a))
        {
            MyCokeMachine = CokeMachine_Default;
            SetOfCokeMachines.push_back(CokeMachine());
            cout<<"New machine added"<<endl;
        }
        else
        {
            cout<<"Please pick a number on the menu list"<<endl;
        } 
    break;
    }
        do{
            k = CokeMenu(MyCokeMachine);
            switch(k){
            case 0: 
                cout<<"Good choice, Cokes aren't good for you"<<endl<<endl;
                break;
            case 1: 
                payment = getPayment();
                if (MyCokeMachine.buyACoke(payment,change,action)){
                    if(action==ACTION(OK)){
                        string message{"Here's your Coke and your change of "+change};
                        Gtk::MessageDialog *MyMessageDialog = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                        MyMessageDialog->run();
                        MyMessageDialog->close();
                        delete MyMessageDialog;
                    }
                    else {
                        string message{"Thank you for exact change.\n Here's your Coke"};
                        Gtk::MessageDialog *MyMessageDialog = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                        MyMessageDialog->run();
                        MyMessageDialog->close();
                        delete MyMessageDialog;
                    }
                     //Map Reciept
                    string Str;
                    Str = MyCokeMachine.getMachineName();
                    if(MyMap[Str])
                    {
                        MyMap[Str]= MyMap[Str]+1;
                    }
                    else
                    {
                        MyMap[Str]=1;  
                    }
                }
                else{
                    if (action==ACTION(NOINVENTORY)){
                        string message{"Out of Coke"};
                        Gtk::MessageDialog *MyMessageDialog = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                        MyMessageDialog->run();
                        MyMessageDialog->close();
                        delete MyMessageDialog;
                    }
                    else if(action==ACTION(NOCHANGE)){
                        string message{"Unable to give change at this time...returning your payment"};
                        Gtk::MessageDialog *MyMessageDialog = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                        MyMessageDialog->run();
                        MyMessageDialog->close();
                        delete MyMessageDialog;
                    }
                    else{
                        string message{"Insufficent payment...returning your payment"};
                        Gtk::MessageDialog *MyMessageDialog = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                        MyMessageDialog->run();
                        MyMessageDialog->close();
                        delete MyMessageDialog;
                    }
                }
                break;
                cout<<"You did not select a number on the menu options"<<endl;
            case 2:
                restock=getRestock();
                if(MyCokeMachine.incrementInventory(restock)){
                    string message{"Your inventory has been restocked. Your inventory level is now "+to_string(MyCokeMachine.getInventoryLevel())};
                    Gtk::MessageDialog *MyMessageDialog = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                    MyMessageDialog->run();
                    MyMessageDialog->close();
                    delete MyMessageDialog;
                }
                else{
                    string message{"You have exceeded your machine's max capacity. Your inventory level is now "+to_string(MyCokeMachine.getInventoryLevel())};
                    Gtk::MessageDialog *MyMessageDialog = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                    MyMessageDialog->run();
                    MyMessageDialog->close();
                    delete MyMessageDialog;
                }
                break;
            case 3:
                amountToAdd=getChange();
                if(MyCokeMachine.incrementChangeLevel(amountToAdd)){
                    string message{"Your change has been updated. Your change level is now "+MyCokeMachine.displayMoney(MyCokeMachine.getChangeLevel())};
                    Gtk::MessageDialog *MyMessageDialog = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                    MyMessageDialog->run();
                    MyMessageDialog->close();
                    delete MyMessageDialog;
                }
                else{
                    string message{"You have exceeded your machine's max change capacity. Your change level is now "+MyCokeMachine.displayMoney(MyCokeMachine.getChangeLevel())};
                    Gtk::MessageDialog *MyMessageDialog = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                    MyMessageDialog->run();
                    MyMessageDialog->close();
                    delete MyMessageDialog;
                }
                break;
            case 4:{
                objOutput << MyCokeMachine << endl;
                string message;
                message = objOutput.str();
                Gtk::MessageDialog *MyMessageDialog = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                MyMessageDialog->run();
                MyMessageDialog->close();
                delete MyMessageDialog;}
                break;
            case 5:{
                //cout<<"Enter a new machine name ";
                //cin>>newMachineName;
                newMachineName = getNewMachineName();
                MyCokeMachine.setMachineName(newMachineName);
                string message{"Machine name has been updated"};
                Gtk::MessageDialog *MyMessageDialog = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                MyMessageDialog->run();
                MyMessageDialog->close();
                delete MyMessageDialog;}
                break;
            case 6:{
                //cout<<"Enter a new Coke price ";
                //cin>>newCokePrice;
                newCokePrice = getNewCokePrice();
                MyCokeMachine.setCokePrice(newCokePrice);
                string message{"Coke price has been updated"};
                Gtk::MessageDialog *MyMessageDialog = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                MyMessageDialog->run();
                MyMessageDialog->close();
                delete MyMessageDialog;}
                break;
                default:
                cout<<"Please pick a number on the menu list"<<endl;
                break;
            }
            SetOfCokeMachines[choice-1]=MyCokeMachine;
        }while(k!=0);
    }while(choice!=0); 
    
    return 0;
}

ostream& operator<<(ostream& output, CokeMachine& MyCokeMachine)
{
    output<<"Machine Name: "+MyCokeMachine.getMachineName()<<"\n"
        <<"Current Inventory Level "+to_string(MyCokeMachine.getInventoryLevel())<<"\n"
        <<"Max Inventory Capacity "+to_string(MyCokeMachine.getMaxInventoryCapacity())<<"\n"
        <<"\nCurrent Change Level "+MyCokeMachine.displayMoney(MyCokeMachine.getChangeLevel())<<"\n"
        <<"Max Change Capacity "+MyCokeMachine.displayMoney(MyCokeMachine.getMaxChangeCapacity())<<"\n"
        <<"\nCurrent Coke price is "+MyCokeMachine.getCokePrice()<<"\n";
    
    return output;
}
string CreateCokeOutputLine(CokeMachine& MyCokeMachine)
    {
    string TheLine;
    TheLine= MyCokeMachine.getMachineName()+"|"+to_string(MyCokeMachine.CokePrice)+"|"+MyCokeMachine.displayMoney(MyCokeMachine.getChangeLevel())+"|"+to_string(MyCokeMachine.inventoryLevel);
    return TheLine;
    }

    int CokeMenu(CokeMachine& MyCokeMachine){ 
        int k;
        //Creating Menu to use coke machine--------------------------------------------------------------------------------------------
        cout<<endl<<endl<<MyCokeMachine.getMachineName()<<endl<<endl;
        Gtk::Dialog *MyDialog = new Gtk::Dialog();
        MyDialog->set_title("Coke Menu");

        vector<string> buttons = {"Walk away","Buy a Coke","Restock Machine","Add change","Display Machine Info","Update Machine Name","Update Coke Price"};
        
        for(int i=0; i<buttons.size();i++){
            MyDialog->add_button(buttons[i], i);
            }
        MyDialog->set_default_response(0);
        int result = MyDialog->run();
        
        MyDialog->close();
        delete MyDialog;	
        return result;
        }

    int getPayment(){
        int payment;
        Gtk::Dialog *MyDialog = new Gtk::Dialog();

        MyDialog->set_title("Insert Payment");

        std::vector<std::string> buttons = {"OK"};
        for (int i = 0; i < buttons.size(); i++)
        MyDialog->add_button(buttons[i], i);
        MyDialog->set_default_response(4);
        Gtk::Label *MyLabel = Gtk::manage(new Gtk::Label("Enter amount:"));
        MyDialog->get_vbox()->pack_start(*MyLabel);
        MyLabel->show();
        Gtk::Entry *MyEntry = Gtk::manage(new Gtk::Entry());
        MyEntry->set_text("Enter your payment here");
        MyEntry->set_max_length(50);
        MyEntry->show();
        MyDialog->get_vbox()->pack_start(*MyEntry);
        Gtk::Image *MyImage = Gtk::manage(new Gtk::Image{"gtkmm-SMALL.png"});
        MyImage->show();
        MyDialog->get_vbox()->pack_start(*MyImage);

        int result = MyDialog->run();
        std::string text = MyEntry->get_text();
        MyDialog->close();
        delete MyDialog;
        payment = stoi(text);
        return payment;
        }
    int getRestock(){
        int restock;
        Gtk::Dialog *MyDialog = new Gtk::Dialog();

        MyDialog->set_title("Restock");

        std::vector<std::string> buttons = {"OK"};
        for (int i = 0; i < buttons.size(); i++)
        MyDialog->add_button(buttons[i], i);
        MyDialog->set_default_response(4);
        Gtk::Label *MyLabel = Gtk::manage(new Gtk::Label("How much product are you adding to the machine?"));
        MyDialog->get_vbox()->pack_start(*MyLabel);
        MyLabel->show();
        Gtk::Entry *MyEntry = Gtk::manage(new Gtk::Entry());
        MyEntry->set_text("0");
        MyEntry->set_max_length(50);
        MyEntry->show();
        MyDialog->get_vbox()->pack_start(*MyEntry);
        Gtk::Image *MyImage = Gtk::manage(new Gtk::Image{"gtkmm-SMALL.png"});
        MyImage->show();
        MyDialog->get_vbox()->pack_start(*MyImage);

        int result = MyDialog->run();
        std::string text = MyEntry->get_text();
        MyDialog->close();
        delete MyDialog;
        restock = stoi(text);
        cout<<"How much product are you adding to the machine? ";
        return restock;
        }
    int getChange(){
        int amountToAdd;
        Gtk::Dialog *MyDialog = new Gtk::Dialog();

        MyDialog->set_title("Change");

        std::vector<std::string> buttons = {"OK"};
        for (int i = 0; i < buttons.size(); i++)
        MyDialog->add_button(buttons[i], i);
        MyDialog->set_default_response(4);
        Gtk::Label *MyLabel = Gtk::manage(new Gtk::Label("How much change are you adding to the machine? "));
        MyDialog->get_vbox()->pack_start(*MyLabel);
        MyLabel->show();
        Gtk::Entry *MyEntry = Gtk::manage(new Gtk::Entry());
        MyEntry->set_text("0");
        MyEntry->set_max_length(50);
        MyEntry->show();
        MyDialog->get_vbox()->pack_start(*MyEntry);
        Gtk::Image *MyImage = Gtk::manage(new Gtk::Image{"gtkmm-SMALL.png"});
        MyImage->show();
        MyDialog->get_vbox()->pack_start(*MyImage);

        int result = MyDialog->run();
        std::string text = MyEntry->get_text();
        MyDialog->close();
        delete MyDialog;
        amountToAdd = stoi(text);
        return amountToAdd;}

    int getNewCokePrice(){
        int price;
        Gtk::Dialog *MyDialog = new Gtk::Dialog();

        MyDialog->set_title("Coke Price");

        std::vector<std::string> buttons = {"OK"};
        for (int i = 0; i < buttons.size(); i++)
        MyDialog->add_button(buttons[i], i);
        MyDialog->set_default_response(4);
        Gtk::Label *MyLabel = Gtk::manage(new Gtk::Label("Enter amount:"));
        MyDialog->get_vbox()->pack_start(*MyLabel);
        MyLabel->show();
        Gtk::Entry *MyEntry = Gtk::manage(new Gtk::Entry());
        MyEntry->set_text("Enter price here");
        MyEntry->set_max_length(50);
        MyEntry->show();
        MyDialog->get_vbox()->pack_start(*MyEntry);
        Gtk::Image *MyImage = Gtk::manage(new Gtk::Image{"gtkmm-SMALL.png"});
        MyImage->show();
        MyDialog->get_vbox()->pack_start(*MyImage);

        int result = MyDialog->run();
        std::string text = MyEntry->get_text();
        MyDialog->close();
        delete MyDialog;
        price = stoi(text);
        return price;}

    string getNewMachineName(){
        string name;
        Gtk::Dialog *MyDialog = new Gtk::Dialog();

        MyDialog->set_title("New Machine Name");

        std::vector<std::string> buttons = {"OK"};
        for (int i = 0; i < buttons.size(); i++)
        MyDialog->add_button(buttons[i], i);
        MyDialog->set_default_response(4);
        Gtk::Label *MyLabel = Gtk::manage(new Gtk::Label("Enter machine name"));
        MyDialog->get_vbox()->pack_start(*MyLabel);
        MyLabel->show();
        Gtk::Entry *MyEntry = Gtk::manage(new Gtk::Entry());
        MyEntry->set_text("Enter name here");
        MyEntry->set_max_length(50);
        MyEntry->show();
        MyDialog->get_vbox()->pack_start(*MyEntry);
        Gtk::Image *MyImage = Gtk::manage(new Gtk::Image{"gtkmm-SMALL.png"});
        MyImage->show();
        MyDialog->get_vbox()->pack_start(*MyImage);

        int result = MyDialog->run();
        name = MyEntry->get_text();
        MyDialog->close();
        delete MyDialog;
        return name;}



