   // Entry Point for Server/Client
   // CSC 3380
   //   H@x0rZ!

#include "ServerManager.h"

void GameLoop( ServerManager & boss );

int main(int argc, char * argv[]) {
	ServerManager servBoss; // Default Constructor sets port to 9999
	Client testClient;
	Client testClient2;

	servBoss.acquireClient(testClient);
	servBoss.acquireClient(testClient2);

	GameLoop( servBoss );
	
	return 0;
}

void GameLoop( ServerManager & boss) {

	while (boss.isRunning()) {
		boss.checkSockets();
	}
	
}