 // Server Entry Point
   // LSU Letter
   // CSC3380 Class Project
   // Authors:  Hardika Patel
   //           Jonathan Nguyen
   //           Todd Moulder
   //           William Raziano

   //  Below contains licensing info for "PracticalSockets"
/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

   #include <iostream>
//   #include <socket>
   #include <thread>            // For cout, cerr
   #include <mutex>
   #include <condition_variable>
   #include <vector>
   #include "PracticalSocket.h" // For Socket, ServerSocket, and SocketException
   #include <cstdlib>           // For atoi()
   #include <pthread.h>         // For POSIX Threads
   #include <fstream>

   using namespace std;

   const char * cardFileStr = "../txt/cards.data";
   const char * logFileStr = "../log/initial.log";

   const int RCVBUFSIZE = 32;                // Restricting receiving to 32 bytes
   const int MAXMSG     = 20;                // Restrict message buffers to 20

   // Global Variables Section
   bool serverStatus = false;
   const int maxSockets = 100;
   int numConnecting = 0;
   int numPlaying = 0;
   TCPServerSocket * serverSock;
   TCPSocket ** toConnectSocket;
   TCPSocket ** playingSocket;
   string * clientMessageBuffer;
   string * responseMessageBuffer;
   int numMessages = 0;

   // Mutex Section
   mutex socketMutex;
   bool handlingSock = false;

   // Main Functions
   void HandleTCPClient( TCPSocket *sock );   // TCP client handling fxn
   void *ThreadMain( void *arg );             // Main program of thread
   void HandleRequest();

   bool startServer( int port );
   bool serverLoop();
   void shutDownServer();
   void getClient( TCPServerSocket & servSock );
   void log( string logString );

   void SetupFiles( ifstream & inFile, ofstream & outFile );
   void HouseKeeping( ifstream & inFile, ofstream & outFile );
   void SetupSockets();
   void CleanSockets();
   void SetupBuffers();
   void CleanBuffers();

   void cleanSocket( TCPSocket * );

   // Global for global access to logfile
   ofstream logFile;

   int main( int argc, char * argv[] ){

     // File Setup, Put in function later
     ifstream cardFile;

     SetupFiles( cardFile, logFile );
     SetupSockets();
     SetupBuffers();

     if ( argc != 2 ) {
       cerr << "Usage: " << argv[0] << " <Server Port> " << endl;
       exit(1);
     }

     unsigned short serverPort = atoi( argv[1] );   // First arg, local port
     serverStatus = true;

       serverSock = new TCPServerSocket(serverPort);      // Socket descriptor for server

       // Game Loop
       while(serverStatus) {
         getClient( *serverSock );
         HandleRequest();
         cout << "Looping" << endl;

       }//End For
     // Never reached

     HouseKeeping( cardFile, logFile );
     CleanSockets();
     CleanBuffers();

     return 0;
   }


   // Should be threadsafe
   void HandleRequest() {
     if ( numMessages-- > 0 ) {
       if ( clientMessageBuffer[0].compare("quit") == 0 ) {
         serverStatus = false;
       }
     }
   }

   void SetupBuffers(){
     clientMessageBuffer = new string[MAXMSG];
     responseMessageBuffer = new string[MAXMSG];
   }

   void CleanBuffers(){
     delete [] clientMessageBuffer;
     delete [] responseMessageBuffer;
   }

   void SetupSockets(){
     toConnectSocket = new TCPSocket*[maxSockets];
     playingSocket = new TCPSocket*[maxSockets];
   }

   void cleanSocket( TCPSocket * toClean ){
     delete toClean; 
   }

   void CleanSockets(){
     for( int i = 0; i < numConnecting; i++ ){
       cleanSocket( toConnectSocket[i] );
     }
     for( int i = 0; i < numPlaying; i++ ){
       cleanSocket( playingSocket[i] );
     }
     delete [] toConnectSocket;
     delete [] playingSocket;
   }

   void getClient(TCPServerSocket & servSock) {
     toConnectSocket[numConnecting++] = servSock.accept();

     pthread_t threadId;
     if ( pthread_create( &threadId, NULL, ThreadMain, (void *) toConnectSocket[numConnecting-1]) != 0 ) {
       cerr << "entry:getClient:Unable to create thread" << endl;
       exit(1);
     }
   }

   // TCP client handling function
   void HandleTCPClient(TCPSocket *sock) {
     try {

       logFile << sock->getForeignAddress() << " : ";

     } catch(SocketException &e){
       cerr << "Unable to get foreign address" << endl;
     }
     try {
       logFile << sock->getForeignPort();
     } catch(SocketException &e) {
       cerr << "Unable to get foreign port" << endl;
     }
     logFile << " with thread " << pthread_self() << endl;

     // Send recvd string and receive again until end of transmission
     char echoBuff[RCVBUFSIZE];
     int recvMsgSize;
     unsigned int msgSize=0;
     char tempBuff[RCVBUFSIZE];
     string tempMessage;

     logFile << sock->getForeignAddress() << ":" << sock->getForeignPort() << " says ";
     while ((recvMsgSize = sock->recv(echoBuff, RCVBUFSIZE)) > 0){ // Zero is end of transmission
       msgSize += recvMsgSize;
       logFile << echoBuff;
       tempMessage += echoBuff;
       sock->send(echoBuff, recvMsgSize);
       cout << "Working on Processing" << endl;
     }
     logFile << endl;
     cout << "Message Receive Complete." << endl;
     tempMessage.resize(msgSize-1);  // This should chop off the newline
     clientMessageBuffer[numMessages++] = tempMessage;
     // Destructor closes Socket
   }

   void *ThreadMain(void *clientSock) {
     // Guarantess that thread resources are deallocated upon return
     pthread_detach(pthread_self());

     while ( handlingSock ) {
       socketMutex.unlock();
     }

     socketMutex.lock();
     handlingSock = true;
     // Extract socket file descriptor from argument
     HandleTCPClient((TCPSocket*) clientSock);
     handlingSock = false;
     socketMutex.unlock();

     return NULL;
   }

   void SetupFiles( ifstream & inFile, ofstream & outFile){
    inFile.open(cardFileStr, ifstream::in );
    outFile.open(logFileStr, ofstream::out);

    if (! inFile.is_open() ){
    	cout << "Error opening " << cardFileStr << endl;
    	exit(0);
    }

    if (! outFile.is_open() ){
    	cout << "Error opening " << logFileStr << endl;
    	exit(0);
    }

   }

   bool startServer( int port ){
   	bool success = false;
   	// Load Cards
   	// Start Lobby
   	// Start Game0
   	// set up listen(), maybe? listen may have to be in threadpool
     return success;
   }
   bool serverLoop(){
     bool serverState = true;
     // Check for new connections
     //  Add new thread for each
     // Update State of each client, game and lobby
     // check for funny things,
     return serverState;
   }
   void shutDownServer(){
     // Clean up threads
     // Clean up Memory
     // Clean up Sockets
     // Log shutdown conditions "../log/TIMEDATESTAMP.log"
   }
   void log( string logString ) {
     logFile << logString << endl;
   }
   void HouseKeeping( ifstream & inFile, ofstream & outFile){
    inFile.close();
    outFile.close();
   }
