#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class acc
{
    int n;
    char name[100];
    int dep;
    char type;
public:
    void create_account();
    void depo(int);
     void show_account() const;
      void draw(int);
    int return_acc() const;
    char qtype() const;
    int return_balance() const;
     void modify();
    void report() const;
};

void acc::create_account()
{
    cout<<"\nEnter The Account Number :";
    cin>>n;
    cout<<"\n\nEnter Name of The Account Holder : ";
    cin.ignore();
    cin.getline(name,100);
    cout<<"\nEnter Type of Account(c-Current/s-Savings) : ";
    cin>>type;
    cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
    cin>>dep;
    cout<<"\n\n\nCongrats Account Has Been Created..";
}
int acc::return_acc() const
{
    return n;
}
void acc::show_account() const
{
    cout<<"\nAccount Number : "<<n;
    cout<<"\nAccount Holder Name : ";
    cout<<name;
    cout<<"\nType of Account : "<<type;
    cout<<"\nBalance amount : "<<dep;
}


void acc::depo(int x)
{
    dep+=x;
}
int acc::return_balance() const
{
    return dep;
}
char acc::qtype() const
{
    return type;
}
void acc::draw(int x)
{
    dep-=x;
}
void acc::modify()
{
    cout<<"\nAccount Number : "<<n;
    cout<<"\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name,100);
    cout<<"\nModify Type of Account : ";
    cin>>type;
    cout<<"\nModify Balance amount : ";
    cin>>dep;
}
void acc::report() const
{
    cout<<n<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(10)<<dep<<endl;
}
void write_acc()
{
    acc ac;
    ofstream x;
    x.open("info.dat",ios::binary|ios::app);
    ac.create_account();
    x.write(reinterpret_cast<char *> (&ac), sizeof(acc));
    x.close();
}
void dep_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    acc ac;
    fstream x;
    x.open("info.dat", ios::binary|ios::in|ios::out);
    if(!x)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!x.eof() && found==false)
    {
        x.read(reinterpret_cast<char *> (&ac), sizeof(acc));
        if(ac.return_acc()==n)
        {
            ac.show_account();
            if(option==1)
            {
                cout<<"\n\n\tTO DEPOSITE AMOUNT ";
                cout<<"\n\nEnter The amount to be deposited";
                cin>>amt;
                ac.depo(amt);
            }
            if(option==2)
            {
                cout<<"\n\n\tTO WITHDRAW AMOUNT ";
                cout<<"\n\nEnter The amount to be withdraw";
                cin>>amt;
                int bal=ac.return_balance()-amt;
                if((bal<500 && ac.qtype()=='S') || (bal<1000 && ac.qtype()=='C'))
                    cout<<"Insufficience balance";
                else
                    ac.draw(amt);
            }
            int pos=(-1)*static_cast<int>(sizeof(ac));
            x.seekp(pos,ios::cur);
            x.write(reinterpret_cast<char *> (&ac), sizeof(acc));
            cout<<"\n\n\t Record Updated";
            found=true;
           }
         }
    x.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}
void display_sp(int n)      //function to retrive a record from file stored
{
    acc ac;
    bool flag=false;
    ifstream x;
    x.open("info.dat",ios::binary);
    if(!x)
    {
        cout<<"File could not be opened!! Press any Key to exit...";
        return;
    }
    cout<<"\nBALANCE DETAILS\n";

        while(x.read(reinterpret_cast<char *> (&ac), sizeof(acc)))
    {
        if(ac.return_acc()==n)
        {
            ac.show_account();
            flag=true;
        }
    }
    x.close();
    if(flag==false)
        cout<<"\n\nAccount number does not exist";
}
void modify_acc(int n)
{
    bool found=false;
    acc ac;
    fstream x;
    x.open("info.dat",ios::binary|ios::in|ios::out);
    if(!x)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!x.eof() && found==false)
    {
        x.read(reinterpret_cast<char *> (&ac), sizeof(acc));
        if(ac.return_acc()==n)
        {
            ac.show_account();
            cout<<"\n\nEnter The New Details of account"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(acc));
            x.seekp(pos,ios::cur);
            x.write(reinterpret_cast<char *> (&ac), sizeof(acc));
            cout<<"\n\n\t Record Updated";
            found=true;
          }
    }
    x.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}
void display_all()
{
    acc ac;
    ifstream x;
    x.open("info.dat",ios::binary);
    if(!x)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
   // cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"====================================================\n";
    cout<<"A/c no.      NAME           Type  Balance\n";
    cout<<"====================================================\n";
    while(x.read(reinterpret_cast<char *> (&ac), sizeof(acc)))
    {
        ac.report();
    }
    x.close();
}



int main()
{

    cout<<"\n\n\n\tWelcome To AB BANK MANAGEMENT SYSTEM";
    cout<<"\nPress Enter To Continue........";
    cin.get();
    char ch;
    int num;
    do
    {
        system("cls");
        cout<<"\n\n\n\t MENU";
        cout<<"\n\n\t01. NEW ACCOUNT";
        cout<<"\n\n\t02. DEPOSIT";
        cout<<"\n\n\t03. WITHDRAW";
        cout<<"\n\n\t04. BALANCE ENQUIRY";
        cout<<"\n\n\t05. COMPLETE ACCOUNT HOLDERS LIST";
        cout<<"\n\n\t06. CLOSE AN ACCOUNT";
        cout<<"\n\n\t07. MODIFY AN ACCOUNT";
        cout<<"\n\n\t08. EXIT";
        cout<<"\n\n\tSelect Your Option (1-8) ";
        cin>>ch;
        switch(ch)
        {
        case '1':
            system("cls");
            write_acc();
            break;
        case '2':
            system("cls");
            cout<<"\n\n\tEnter The Account Number : ";
            cin>>num;
            dep_withdraw(num, 1);
            break;
        case '3':
            system("cls");
            cout<<"\n\n\tEnter The Account Number : ";
            cin>>num;
            dep_withdraw(num, 2);
            break;
            case '4':
             system("cls");
            cout<<"\n\n\tEnter The Account Number : "; cin>>num;
            display_sp(num);
            break;
         case '5':
            display_all();
            break;
         case '7':
            cout<<"\n\n\tEnter The Account Number : ";
            cin>>num;
            modify_acc(num);
            break;
         case '8':
            cout<<"\n\n\tThanks For Visiting Our Bank!";
            break;
         default :cout<<"\a";
        }
        cin.ignore();
        cin.get();
    }
    while(ch!='8');
    return 0;
}
