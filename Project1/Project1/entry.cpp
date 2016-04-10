   // Entry Point for Server/Client
   // CSC 3380
   //   H@x0rZ!

#include "ServerManager.h"
#include <iostream>

void GameLoop( ServerManager & boss );

int main(int argc, char * argv[]) {
	ServerManager * servBoss; // Default Constructor sets port to 9999
	Client testClient;
	Client testClient2;
	Account toddAccount("Todd", "MyPassword", "127.0.0.1");
	Account willAccount("Will", "HisPassword", "127.0.0.2");
	Account jonAccount("Jon", "TurtleFarts", "127.0.0.0");
	Account hardikaAccount("Hardika", "Kolaches", "5");

	servBoss = servBoss->get();

	servBoss->acquireClient(testClient);
	servBoss->acquireClient(testClient2);

        servBoss->setRunning();

        cout << " is Running is " << (servBoss->isRunning()? "True" : "False") << endl;

	GameLoop( *servBoss );

	return 0;
}

void GameLoop( ServerManager & boss) {

	while (boss.isRunning()) {
		// Select Magic is in checkSockets()
		boss.checkSockets();
		// Get the Input from all the Clients and Put them in the Server Mailbox for Processing
		//boss.getInput();
		// Process the input from serverMailbox ( Should be a bunch of Commands )
		//boss.processInput();
		// Do all autonomic game functions
		//boss.gameUpdate();
		// Load the Client Mailboxes and Send any messages
		//boss.handleOutput();
	}

}
