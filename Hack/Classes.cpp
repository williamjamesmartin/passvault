#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include<cstdlib>
#include "sha256.h"


using namespace std;

class passwordVault
{
private:
    string aType, userName, password, moreInfo, fstring;
    string keyin;
    string b;
    
    
    void reviewFolderN ()
    {
        cout << "Folder Contents Below:" << endl;
        
        ifstream reader;
        reader.open("PassVault.txt");
        
        while (!reader.eof())
        {
            
            getline(reader, aType,' ');
            getline(reader,userName,' ');
            getline(reader, password, ' ');
            getline(reader,moreInfo,'\n');
            
            
            cout << "Type: " << aType << "  " << "Username: " << userName << "  " << "Password: " << password << "  " << "More info: " << moreInfo << endl;
            
        }
        reader.close();
    }
    
    
    

public:
    
    
    void reveiwFolderE ()
    {
        string key;
        string hash;
        string x;
        
        verification();
        
        key = verification();
        createFile(key);
        system("openssl aes-256-cbc -d -a -in PassVault.txt.enc -out PassVault.txt -pass pass:file:/Library/Caches/KeyHolder.txt");
        //system(("openssl aes-256-cbc -d -a -in PassVault.txt.enc -out PassVault.txt -pass pass:"+key).c_str());
        //system("openssl enc -d -aes-256-cbc -in ENCPassVault.txt -out PassVault.txt -pass pass:env:key");
        deleteFile();
        ifstream reader;
        reader.open("PassVault.txt");
        
        cout << "Current vault content below: " << endl << endl << endl;
        
        while (!reader.eof())
        {
            
            getline(reader, aType,' ');
            getline(reader,userName,' ');
            getline(reader, password, ' ');
            getline(reader,moreInfo,'\n');
            
            
            cout << "Type: " << aType << "   " << "Username: " << userName << "   " << "Password: " << password << "   " << " More info: " << moreInfo << endl;
            
        }
        
        reader.close();
        
        cout << endl << endl << "Would you like to add more information to the file? (Y/N)" << endl;
        cin >> x;
        
        if (x == "y" || x == "Y")
        {
            addFieldN();
            cout << "Your new private key is : " << hashFile() << endl;
        }
        
        if (x == "N" || x == "n")
        {
            cout << "No information added, file will encrypt" << endl;
        }
        

        hash = hashFile();
        createFile(hash);
        system("openssl aes-256-cbc -a -salt -in PassVault.txt -out PassVault.txt.enc -pass pass:file:/Library/Caches/KeyHolder.txt");
        //system(("openssl aes-256-cbc -a -salt -in PassVault.txt -out PassVault.txt.enc -pass pass:"+hash).c_str());
        //system("openssl enc -aes-256-cbc -in PassVault.txt -out ENCPassVault.txt -pass pass:env:hash");
        deleteFile();
        system("rm -f PassVault.txt");
        
    }
    
    
    
    
    
    
    void addFieldN ()
    {
        ofstream adder;
        adder.open("PassVault.txt", ios::app);
        int x;
        string y;
        string h = "Y";
        
        
        
        cout << "File Password input, you will be asked to input 'Account Type' 'User Name' 'Password' 'More Info'" << endl;
        cout << "Input '1' to contine" << endl;
        cin >> x;
        system("clear");
        
        if (x==1)
        {
            while (h == "Y")
            {
                
                cout << "Enter Account Type/Name" << endl;
                getline (cin,aType);
                cout << "Enter Username" << endl;
                getline (cin,userName);
                cout << "Enter Password" << endl;
                getline (cin,password);
                cout << "Enter More Info:" << endl;
                getline (cin,moreInfo);
                
                adder << aType << " " << userName << " " << password << " " << moreInfo << endl;
                system("clear");
                cout << "Would you like to add another password 'Y' or 'N'" << endl;
                cin >> h;
                system("clear");
            }
            
            adder.close();
            cout << "Your passwords have been added to the file" << endl << endl;
            system("clear");
            cout << "Would you like to review all data being added to file before encryption? ('Y' or 'N')" << endl;
            cin >> b;
            system("clear");
            
            if (b == "Y" || b == "y")
            {
                reviewFolderN();
            }
            
            else
            {
                cout << "Time to proceed to encryption" << endl;
            }
            
            return;
            
        }
        
        else
        {
            cout << "Are you sure you would like to add no data to vault?" << endl;
            cout << "If you would like to go back and add data to your vault input 'YES' if not input 'NO'" << endl;
            cin >> y;
            system("clear");
            if (y == "YES" || y == "yes" || y == "Yes")
            {
                addFieldN();
            }
            
            else
            {
                cout << "Time to proceed to encryption" << endl;
                return;
            }
        }
        
        adder.close();
    }
    
    
    
    
    
    string makeFile ()
    {
        ifstream reader;
        reader.open("PassVault.txt");
        
        while (!reader.eof())
        {
            
            getline(reader, aType,' ');
            getline(reader,userName,' ');
            getline(reader, password,' ');
            getline(reader,moreInfo,'\n');
            
            
            fstring = fstring + " **" + aType + "  " + userName + "   " + password + "   " + moreInfo;
        }
        reader.close();
    
        return fstring;
    }
    
    
    
    
    
    string hash(string input)
    {
        string hashk = sha256(input);
        
        //cout << "sha256('"<< input << endl << "'):" << hashk << endl;
        return hashk;
    }
    
    
    
    
    
    string hashFile ()
    {
        return hash(makeFile());
    }
    
    
    
    
    void hashencrypt (string passwordz, string hencrypt)
    {
        string passe;
        passe = passwordz;
        ofstream writer;
        writer.open("hash.txt");
        writer << hencrypt << endl;
        writer.close();
        createFile(passe);
        system("openssl aes-256-cbc -a -salt -in hash.txt -out hash.txt.enc -pass pass:file:/Library/Caches/KeyHolder.txt");
        //system(("openssl aes-256-cbc -a -salt -in hash.txt -out hash.txt.enc -pass pass:"+passe).c_str());
        //system("openssl enc -aes-256-cbc -in hash.txt -out ENChash.txt -pass pass:env:passe");
        deleteFile();
        system("rm -f hash.txt");
    }
    
    

    
    
    string hashdecrypt (string passwordin)
    {
        string hashtext, pass;
        pass = passwordin;
        createFile(pass);
        system("openssl aes-256-cbc -d -a -in hash.txt.enc -out hash.txt -pass pass:file:/Library/Caches/KeyHolder.txt");
        //system(("openssl aes-256-cbc -d -a -in hash.txt.enc -out hash.txt -pass pass:"+pass).c_str());
        //system("openssl enc -d -aes-256-cbc -in ENChash.txt -out hash.txt -pass pass:env:pass");
        deleteFile();
        ifstream reader;
        reader.open("hash.txt");
        getline(reader,hashtext,'\n');
        reader.close();
        hashencrypt(passwordin, hashtext);
        return hashtext;
    }
    
    
    
    
    string verification ()
    {
        int choice;
        string attemptpass, hash1, in;
        cout << "Enter 1 to enter password or 2 to if you forgot your password." << endl;
        cin >> choice;
        
        if (choice == 1)
        {
            cout << "Please enter passcode: " << endl;
            cin >> attemptpass;
            system("clear");
            hash1 = hashdecrypt(attemptpass);
        }
            
            
        if (choice == 2)
        {
            cout << "Enter your recovery key" << endl;
            cin >> in;
            system("clear");
            hash1 = in;
        }
        
        return hash1;
    }
    
    
    
    
    void createFile(string key)
    {
        string keys;
        keys = key;
        ofstream writer;
        writer.open("/Library/Caches/keyHolder.txt");
        writer << keys << endl;
        writer.close();
    }
    
    
    
    
    void deleteFile()
    {
        system("rm -r /Library/Caches/keyHolder.txt");
    }
    
    
    
    
    //******
    //******
    //******
    //BELOW IS PASSWORD CHECK FUNCTIONS

    
    bool isShorter(const string pword)        // lower limit
    {
        if (pword.size() > 10)
        {
            return false;
        }
        
        else
        {
            return true;
        }
    }
    
    
    bool isLonger(const string pword)         // upper limit
    {
        if (pword.size() > 30)
        {
            return true;
        }
        
        else
        {
            return false;
        }
    }
    
    bool hasUpperCase(const string pword)      // checks uppercase
    {
        for (auto &c : pword)
        {
            if (isupper(c))
                return true;
        }
        return false;
    }
    
    bool hasLowerCase(const string pword)    // checks lowercase
    {
        for (auto &c : pword)
        {
            if (islower(c))
                return true;
        }
        return false;
    }
    
    bool hasNumber(const string pword)       // checks a number
    {
        for (auto &c : pword)
        {
            if (isdigit(c))
                return true;
        }
        return false;
    }
    
    bool hasSpecialCharacters(const string pword) // checks special characters
    {
        for (auto &c : pword)
        {
            if (isalnum(c))
                return false;
        }
        return true;
    }
    
    bool passwordCheck (const string password)
    {
        bool isGood = true;
        
        if (!isLonger(password) && !isShorter(password) && hasUpperCase(password)
            && hasLowerCase(password) && hasNumber(password) && !hasSpecialCharacters(password))
        {
            cout << endl << "Proper password." << endl << endl;
            isGood = true;
        }
        
        else
        {
            cout << endl << "Improper password! Reason..." << endl;
            
            if (isShorter(password))
                cout << "Your password is shorter than 10 characters." << endl;
            if (isLonger(password))
                cout << "Your password can not be longer than 30 characters." << endl;
            if (!hasUpperCase(password))
                cout << "Your password must have at least one upper case letter." << endl;
            if (!hasLowerCase(password))
                cout << "Your password must have at least one lower case letter." << endl;
            if (!hasNumber(password))
                cout << "Your password must have at least one number." << endl;
            if (!hasSpecialCharacters(password))
                cout << "At least one special character is required." << endl;
            isGood = false;
        }
        return isGood;
    }
    
    
    string mainPassIn()
    {
        string Password;
        cout << "Time to create your passcode, enter your password below. Your vault is as secure as your passcode." << endl;
        cout << "Your password must contain an uppercase letter, lowercase letter, special character, must be at least 10 characters, no more than 30 characters, and contain a number" << endl;
        cin >> Password;
        system("clear");
        while (!passwordCheck(Password))
        {
            cout << endl << "Try another password: ";
            cin >> Password;
        }
        
        return password;
        
    }
};








