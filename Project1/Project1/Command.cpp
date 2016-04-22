
#include "Command.h"
#include <iostream>

Command::Command()
{
	argList = new vector<std::string>();
	// Populate arglist from CmdList
}

Command::~Command() {
}

void Command::GetClient(Client * actor) {
	clientActor = actor;
}

// All Commands Should be Initialized before Executing.  Consider Initialization in Execute
void Command::Initialize(string inArgs) {
	cmdArgs = inArgs;
	splitArgs();
        sm = sm->get();
}

void Command::splitArgs() {
	stringstream ss(cmdArgs);
	string arg;
	char delimiter = ' ';

	while (getline(ss, arg, delimiter)) {
		argList->push_back(arg);
	}
}


// Command Execute Section
// Commands From Client

bool DisconnectCommand::Execute() {
	HaxorSocket * clientSock = &(clientActor->getSocket());
	sm->releaseClient(clientActor);
	return true;
}

bool NewAccountCommand::Execute() {
	Account * tempAccount;
	string name, pass, ip, email, admin;
	bool bAdmin = false;
	bool success = false;

        if ( argList->size() == 6 ) {
  	  name = argList->at(1);
	  pass = argList->at(2);
	  ip = argList->at(3);
	  email = argList->at(4);
          admin = argList->at(5);
	  if (admin == "true") {
		bAdmin = true;
	  }
          else {
     		bAdmin = false;
	  }
	  tempAccount = new Account(name, pass, ip, email, bAdmin);
	  if (sm->AddAccount(*tempAccount)) {
		success = true;
		// Success
	  }
	  else {
		// Failure
	  }

	  delete tempAccount;
        }

	return success;
}

bool LoginCommand::Execute() {
	bool status = false;
	sm->checkAccount(argList->at(1), argList->at(2), argList->at(3));
        status = true;
        return status;
}

bool CreateGameCommand::Execute() {
	Player * pc = clientActor->GetPlayer();
	myLobby = pc->WhichLobby();
	myLobby->MakeGame(argList->at(1));
}

// Commands From Server

bool LoginCheckCommand::Execute() {
	bool status = false;
	if (cmdArgs.find("Login") != std::string::npos) {
		std::cout << "Sending Back Login Success Info" << endl;
		sm->SendMessageToSocket(clientActor->getSocket(), "LoginCheck Login " +argList->at(4));
	}
	else if (cmdArgs.find("NewAccount") != std::string::npos) {
		sm->SendMessageToSocket(clientActor->getSocket(), "LoginCheck NewAccount " + argList->at(6));
	}
	status = true;
	return status;
}

// PRECONDITIONS :
// Assume initialize is called,
// cmdArgs Populated
// We have received a client request to play a card, we assume it is legit.
// RESPONSE : 
// What Actions should the server take?  
//    Player must put card from hand into their discard pile
//****** begin switch
//    We must apply the effect of the card, (e.g. apply protection, make a guess, compare hands, target player discards hand, trade hands
//    This may result in someone being marked as "out" (isOut()) for the remainder of the round
//****** end switch/selection
//    Player Signals Pass of Turn to Game Instance
//    Check for Winner
//    Deal Card
bool PlayCardCommand::Execute() {
	//Choose
	  // Card 1 :
	    
}
