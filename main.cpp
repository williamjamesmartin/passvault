#include "Classes.cpp"


int main ()
{
    string mainhash;
    int choice; string passwordin;
    passwordVault PV;
    
    cout << "Enter 1 if no file is created yet, enter 2 to view/edit encrypted file" << endl;
    cin >> choice;
    system("clear");
    
    if (choice == 1)
    {
        PV.addFieldN();
        mainhash = PV.hashFile();
        cout << endl << endl << "***** Please write down this private key, this key acts as an extra security measure if you forget your password: *****" << endl;
        cout << "*****" << PV.hashFile() << "*****" << endl << endl;
        
        PV.createFile(mainhash);
        system("openssl aes-256-cbc -a -salt -in PassVault.txt -out PassVault.txt.enc -pass pass:file:/Library/Caches/KeyHolder.txt");
        //system(("openssl aes-256-cbc -a -salt -in PassVault.txt -out PassVault.txt.enc -pass pass:"+mainhash).c_str());
        system("rm -f PassVault.txt");
        PV.deleteFile();
        passwordin = PV.mainPassIn();
        system("clear");
        PV.hashencrypt(passwordin, mainhash);
        
        
        
        
        cout << "File now encrypted" << endl;
    }
    
    if (choice == 2)
    {
        PV.reveiwFolderE();
    }
}
