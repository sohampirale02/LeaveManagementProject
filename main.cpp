#include<bits/stdc++.h>
#include<filesystem>
#include<fstream>
using namespace std;

class employee{
    public:
        string name;
        int age;
        long long salary;
        employee(string name,int age,long long salary):name(name),age(age),salary(salary){}

        ~employee(){
            cout<<this->name<<" is deleted"<<endl;
        }
};

void addLeavesTxt(string path){
    ofstream casual(path+"casualLeave.txt",ios::out);
    ofstream medical(path+"medicalLeave.txt",ios::out);
    ofstream leavesHistory(path+"leaveHistory.txt",ios::out);
  
    if(!casual.is_open()||!medical.is_open()||!leavesHistory.is_open()){
        cout<<"Couldn't create leaves file"<<endl;
        return;
    }
    casual<<10;
    medical<<20;

    leavesHistory.close();
    casual.close();
    medical.close();
}

void addUser(){
    string name,path="all_users/";
    cout<<"Enter name of new user : ";
    cin>>name;
    if(filesystem::exists(path+name)){
        cout<<"User "<<name<<" already exists in the database"<<endl;
        return;
    } 
    int age,id;
    long long salary;
    cout<<"Enter id : ";
    cin>>id;
    cout<<"Enter age : ";
    cin>>age;
    cout<<"Enter salary of "<<name<<" : ";
    cin>>salary;
    filesystem::path dirPath = name;
    filesystem::create_directory(path+name);
    cout<<"New folder with name "<<name<<" is created"<<endl;
    ofstream create(path+name+"/"+name+".txt",ios::out);
    if(!create.is_open()){
        cout<<"Couldn't create "<<name<<".txt file"<<endl;
        return;
    } 
    create<<name<<endl<<id<<endl<<age<<endl;
    ofstream salaryOut(path+name+"/"+"salary.txt",ios::out);
    salaryOut<<salary<<endl;
    salaryOut.close();
    addLeavesTxt(path+name+"/");
    cout<<"New user created successfully"<<endl;
}

int tellRemainning(string path){
    ifstream remainnning(path,ios::in);
    if(!remainnning.is_open()){
        cout<<"Error finding no o fleaves remainning"<<endl;
        return -1;
    }
    int remianningLeaves;
    remainnning>>remianningLeaves;
    return remianningLeaves;
}

void applyLeave(){
    string path="all_users/";
    string name;
    cout<<"Enter name of the employee : ";
    cin>>name;
    if(!filesystem::exists(path+name)){
        cout<<"User with the name "<<name<<" does not exists"<<endl;
        return;
    }
    path+=(name+"/");
    int type,remainningLeaves,requestedLeaves;
    cout<<"For which leave you want to apply\n1 : Casual Leave\n2 : Medical Leave\nYour choice : ";
    cin>>type;
    if(type==1){
        remainningLeaves=tellRemainning(path+"casualLeave.txt");
        if(remainningLeaves<=0){
            cout<<name<<" you have already used all you casual leaves"<<endl;
        } else {
            cout<<name<<" how mnay casual leaves you want(remainning : "<<remainningLeaves<<") : ";
            cin>>requestedLeaves;
            if(requestedLeaves>remainningLeaves){
                cout<<"You only have "<<remainningLeaves<<" casual leaves"<<endl;
                return;
            }
            string startingDate,endDate;
            cout<<"Enter starting data : (dd-mm-yyyy) : ";
            cin>>startingDate;
            cout<<"Enter ending data : (dd-mm-yyyy) : ";
            cin>>endDate;
            remainningLeaves-=requestedLeaves;
            ofstream update(path+"casualLeave.txt",ios::out);
            update<<remainningLeaves;
            update.close();
            ofstream leaveHistoryUpdate(path+"leaveHistory.txt",ios::app);
            leaveHistoryUpdate<<"Leave type : Casual -> Starting data : "<<startingDate<<" & End date : "<<endDate<<endl;
            leaveHistoryUpdate.close();
        }
    } else {
        remainningLeaves=tellRemainning(path+"medicalLeave.txt");
        if(remainningLeaves<=0){
            cout<<name<<" you have already used all you medical leaves"<<endl;
        } else {
            cout<<name<<" how mnay medical leaves you want(remainning : "<<remainningLeaves<<") : ";
            cin>>requestedLeaves;
            if(requestedLeaves>remainningLeaves){
                cout<<"You only have "<<remainningLeaves<<" medical leaves"<<endl;
                return;
            }
            string startingDate,endDate;
            cout<<"Enter starting data : (dd-mm-yyyy) : ";
            cin>>startingDate;
            cout<<"Enter ending data : (dd-mm-yyyy) : ";
            cin>>endDate;
            remainningLeaves-=requestedLeaves;
            ofstream update(path+"medicalLeave.txt",ios::out);
            update<<remainningLeaves;
            update.close();
            ofstream leaveHistoryUpdate(path+"leaveHistory.txt",ios::app);
            leaveHistoryUpdate<<"Leave type : Medical -> Starting data : "<<startingDate<<" & End date : "<<endDate<<endl;
            leaveHistoryUpdate.close();
        }
    }

}

int getChoice(){
    int choice;
    cout<<"1 : Add new user"<<endl;
    cout<<"2 : Apply Leave"<<endl;
    cout<<"3 : Display data about an employee"<<endl;
    cout<<"Your choice : ";
    cin>>choice;
    return choice;
}

void displayInfo() {
    filesystem::path basePath = "all_users";
    string name;

    cout << "Enter name of the user: ";
    cin >> name;

    filesystem::path userPath = basePath / name;

    if (filesystem::exists(userPath) && filesystem::is_directory(userPath)) {
        cout << "Name: " << name << endl;

        cout << "No of Casual leaves remaining: "
             << tellRemainning((userPath / "casualLeave.txt").string()) << endl;

        cout << "No of Medical leaves remaining: "
             << tellRemainning((userPath / "medicalLeave.txt").string()) << endl;

        cout << "Leave history of " << name << ":" << endl;

        ifstream leaveHistory((userPath / "leaveHistory.txt").string());
        if (leaveHistory) {
            string line;
            while (getline(leaveHistory, line)) {
                cout << line << endl;
            }
            leaveHistory.close();
        } else {
            cout << "No leave history available." << endl;
        }
    } else {
        cout << "User with name: " << name << " does not exist in the database." << endl;
    }
}

int main(){
    int choice=1;
    while(choice){
        choice=getChoice();
        if(choice==1){
            addUser();      
        } else if(choice==2){
            applyLeave();
        } else if(choice==3){
            displayInfo();
        }
    }
}