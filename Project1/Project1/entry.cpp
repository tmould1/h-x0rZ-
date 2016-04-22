   // Entry Point for Server/Client
   // CSC 3380
   //   H@x0rZ!

#include "ServerManager.h"
#include <iostream>
#include <signal.h>

void GameLoop( ServerManager & boss );

int main(int argc, char * argv[]) {
	ServerManager * servBoss;
	Client testClient;
	Client testClient2;
	Account toddAccount("Todd", "MyPassword", "127.0.0.1", "toddmoulder88@gmail.com", true);
	Account willAccount("Will", "HisPassword", "127.0.0.1", "will@awesome.com", true);
	Account jonAccount("Jon", "TurtleFarts", "127.0.0.1", "jon@strange.net", true);
	Account hardikaAccount("Hardika", "Kolaches", "127.0.0.1", "hardika@amazing.org", true);

	servBoss = servBoss->get();
        servBoss->registerClientManager();

        servBoss->AddAccount( toddAccount );
        servBoss->AddAccount( willAccount );
        servBoss->AddAccount( jonAccount );
        servBoss->AddAccount( hardikaAccount );

	servBoss->acquireClient(testClient);
	servBoss->acquireClient(testClient2);

        servBoss->setRunning();

        cout << "H@x0rZ! Server is up and running on default port 9999" << endl;
        cout << "Server Initialization success is " << (servBoss->isRunning()? "True" : "False") << endl;

	GameLoop( *servBoss );

	return 0;
}

void GameLoop( ServerManager & boss) {

#ifdef __linux__
	signal(SIGPIPE, SIG_IGN);
#endif
	while (boss.isRunning()) {
		// Select Magic is in checkSockets()
		boss.checkSockets();

		// Get the Input from all the Clients and Put them in the Server Mailbox for Processing
		// Process the input from serverMailbox ( Should be a bunch of Commands )
		boss.processInput();

		// Do all autonomic game functions
		boss.gameUpdate();
			// Load the Client Mailboxes and Send any messages
		boss.handleOutput();
//                cout << "Every .10secs?" << endl;
	}

}
