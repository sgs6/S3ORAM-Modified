#include <iostream>
#include "ClientS3ORAM.hpp"
#include "ServerS3ORAM.hpp"
#include "config.h"
#include "Utils.hpp"

using namespace std;


#include <thread>

unsigned int nthreads = std::thread::hardware_concurrency();  // Returns the number of concurrent threads supported by the implementation. The value should be considered only a hint.

int main(int argc, char **argv)
{    
    
    string mkdir_cmd = "mkdir -p ";
    string mkdir_localState = mkdir_cmd + clientLocalDir;
    string mkdir_unsharedData = mkdir_cmd + clientDataDir;
    string mkdir_log = mkdir_cmd + logDir;
    
    system(mkdir_localState.c_str());
    system(mkdir_unsharedData.c_str());
    system(mkdir_log.c_str());
    for(int i = 0 ; i < NUM_SERVERS; i++)
    {
        string mkdir_sharedData = mkdir_cmd +  rootPath + to_string(i);
        system(mkdir_sharedData.c_str());
    }

    int choice;
    zz_p::init(P);
    //set random seed for NTL
    ZZ seed = conv<ZZ>("123456789101112131415161718192021222324");
    SetSeed(seed);
    
	cout << "CLIENT(1) or SERVER(2): ";
	cin >> choice;
	cout << endl;
	
	if(choice == 2)
	{
		int serverNo;
        int selectedThreads;
		cout << "Enter the Server No (1-"<< NUM_SERVERS <<"):";
		cin >> serverNo;
		cin.clear();
		cout << endl;
        
        do
        {
            cout<< "How many computation threads to use? (1-"<<nthreads<<"): ";
            cin>>selectedThreads;
		}while(selectedThreads>nthreads);
        
		ServerS3ORAM*  server = new ServerS3ORAM(serverNo-1,selectedThreads);
		server->start();
	}
	else if (choice == 1)
	{
        
		ClientS3ORAM* client = new ClientS3ORAM();
        int access, start;
		char response = ' ';
		int random_access;
        int subOpt;
        cout<<"LOAD PREBUILT DATA (1) OR CREATE NEW ORAM (2)? "<<endl;
        cin>>subOpt;
        cout<<endl;
        if(subOpt==1)
        {
            client->load();
        }
        else
        {
			cout << "Calling client init " << endl;
            client->init();
            do
            {
                cout << "TRANSMIT INITIALIZED S3ORAM DATA TO NON-LOCAL SERVERS? (y/n)";
                cin >> response;
                response = tolower(response);
            }
            while( !cin.fail() && response!='y' && response!='n' );
            if (response == 'y')
            {
                client->sendORAMTree();
            }
		    
        }
		cout << "SERVERS READY? (Press ENTER to Continue)";
		cin.ignore();
		cin.ignore();
		cin.clear();
		cout << endl<<endl<<endl;
		
	beginning:
        cout << "SEQUENTIAL WARM-UP(1) OR RANDOM ACCESS(2) OR KEY ACCESS(3)?";
		cin >> choice;
		cout << endl;
		

		
		if(choice == 1)
		{
			cout << "START FROM?(1-" << NUM_BLOCK << ")";
			cin >> start;
			cout << endl;
			//Sequential Access
			auto st = time_now;
			for(int j = start; j <= NUM_BLOCK; j++)
			{
				cout << endl;
				cout << "=================================================================" << endl;
				cout << "[main] Sequential Access for " << j << " IS STARTING!" <<endl;
				cout << "=================================================================" << endl;
				
				client->access(j);
				cout << "=================================================================" << endl;
				cout << "[main] Sequential Access for " << j << " IS COMPLETED!" <<endl;
				cout << "=================================================================" << endl;
				
				if(j % (EVICT_RATE) == 0)
				{	
					auto en = time_now;
					cout << std::chrono::duration_cast<std::chrono::milliseconds>(en-st).count() << " milliseconds to sequentially read evict rate blocks. \n\n";

					cout << endl;
					do
					{
						cout << "DO YOU WANT TO CONTINUE? (y/n)";
						cin >> response;
						response = tolower(response);
					}
					while( !cin.fail() && response!='y' && response!='n' );
					
					if (response == 'n')
					{
						goto beginning;
					}
				}
			}
		}
		else if(choice == 2)
		{
			cout << "HOW MANY RANDOM ACCESS?";
			cin >> access;
			
			auto st = time_now;
			for(int j = 1 ; j <= access; j++)
			{
				random_access = rand() % NUM_BLOCK + 1; 
				cout << endl;
				cout << "=================================================================" << endl;
				cout << "[main] Random Access for " << random_access << " IS STARTING!" <<endl;
				cout << "=================================================================" << endl;
				
				
				client->access(random_access);
				
				cout << "=================================================================" << endl;
				cout << "[main] Random Access for " << random_access << " IS COMPLETED!" <<endl;
				cout << "=================================================================" << endl;
			}
			auto en = time_now;
			cout << std::chrono::duration_cast<std::chrono::milliseconds>(en-st).count() << " milliseconds to randomly querry entire database " << access << " times \n\n";


			
			cout << endl;
			do
			{
				cout << "DO YOU WANT TO START OVER? (y/n)";
				cin >> response;
				response = tolower(response);
			}
			while( !cin.fail() && response!='y' && response!='n' );
			
			if (response == 'y')
			{
				goto beginning;
			}
		}
		else if(choice == 3){
			long long int querry;
			cout << "What key value do you want to querry?";
			cin >> querry;

			cout << endl;
			auto st = time_now;
			cout << "=================================================================" << endl;
			cout << "[main] Key Access for " << access << " IS STARTING!" <<endl;
			cout << "=================================================================" << endl;

			client->accessQuerry(querry);
			
			cout << "=================================================================" << endl;
			cout << "[main] Key Access for " << access << " IS COMPLETED!" <<endl;
			cout << "=================================================================" << endl;
			auto en = time_now;
			cout << std::chrono::duration_cast<std::chrono::milliseconds>(en-st).count() << " milliseconds to querry entire database for all instances of key " << querry << "\n\n";

			cout << endl;
			do
			{
				cout << "DO YOU WANT TO START OVER? (y/n)";
				cin >> response;
				response = tolower(response);
			}
			while( !cin.fail() && response!='y' && response!='n' );

			if (response == 'y')
			{
				goto beginning;
			}
		}
		else
		{
			cout << "COME ON!!" << endl;
		}

		cout << "BYE!" << endl;
	}
	else
	{
		cout << "COME ON!!" << endl;
	}
     
    return 0;
}
