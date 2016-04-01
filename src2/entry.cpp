   #include <iostream>
   #include <thread>
   #include <mutex>
   #include <string>
   #include <ctime>
   #include <sys/time.h>
   #include <sys/types.h>
   #include <unistd.h>
   #include "PracticalSocket.h"
   #include "Client.h"
//   #include "Timer.h"

   using namespace std;

   // Global Variables -> Singleton?
   mutex mtx;

   bool systemDown = false;

   unsigned short int serverPort;
   int procId;

   TCPServerSocket * serverSock;

   string cryptPassword;

   time_t currentTime;

   Client ** clientList;
   const int maxClients = 100;
   int numClients;

   const int maxBuffer = 256;

   char inBuffer[maxBuffer];
   char outBuffer[maxBuffer];

   //  End Global Variables Section

   //  Main Functions
   void makeClientList();
   void cleanClientList();
   void GameLoop();

   // GameLoop Functions
   void autonomousGameHandler();





   int main ( int argc, char * argv[] ) {
     bool serverStatus = true;

     // Server Startup BEGIN
     makeClientList();
     // Get Process ID
     procId = getpid();

     // Default Port Number and Get Routine
     serverPort = 9999;

     if ( argc > 1 ) {
       if ( (serverPort = atoi(argv[1])) <= 1024 ) {
         cout << "Port Number must be above 1024" << endl;
//         log << "Port set below 1025" << endl;
       }
     }

     if (serverSock = new TCPServerSocket(serverPort)) == NULL ) {
       serverStatus = false;
     }
     // Initialize Lobby
/*
 *   if ( !MainLobby.Initialize() )  {
       serverStatus = false;
     }
*/



     // Server Startup END

     // Main Game Loop
     if ( serverStatus ) {
       GameLoop( );
     }


     // CleanUp
     cleanClientList();

     return 0;
   }





   void GameLoop() {
     static struct timeval nullTime;
     struct timeval lastTime;
     time_t timer;
     struct tm finished = { 0 };

     gettimeofday( &lastTime, NULL );
     currentTime = (time_t) lastTime.tv_sec;

     while (!systemDown) {
       // File Descriptor Sets
       fd_set inSet;
       fd_set outSet;
       fd_set excSet;
       int maxDesc;

       FD_ZERO( &inSet );
       FD_ZERO( &outSet );
       FD_ZERO( &excSet );
       FD_SET( serverSock->getSockDesc() , &inSet );

      for( int i = 0; i < numClients; i++ ) {
         maxDesc = ( maxDesc > numClients ? maxDesc : numClients );
         FD_SET( clientList[i]->fd, &inSet  );
         FD_SET( clientList[i]->fd, &outSet );
         FD_SET( clientList[i]->fd, &excSet );
       }

       if( select( maxDesc+1, &inSet, &outSet, &excSet, &nullTime ) < 0 ) { 
//         log << "GameLoop: Select: Returned a value less than 0" << endl;
       }

       if( FD_ISSET(serverSock->getSockDesc(), &inSet ) ) {
         // New Connection
         // newClient( serverSock->fd );
       }

       // Any Exception Cases?  I.E. Removing Clients
/*
       for ( auto& client : clientList ) {
         if ( FD_ISSET( client->fd, &excSet )) {
           FD_CLR( client->fd, &inSet );
           FD_CLR( client->fd, &outSet );
           client->fd = NULL;
         }
       }
*/

       // Process Input
/*
       for ( auto& client : clientList ) {
         if ( FD_ISSET( client->fd, &inSet ) ) {
           //do ( clientf->fd.recv( inBuffer, maxBuffer ) );
         }
       }
*/
       // Game Update Handler
       autonomousGameHandler();

       // Process Output
/*
       for ( auto& client: clientList ) {
         if( FD_ISSET( client->fd, &outSet ) ) {
         // show( client->fd.send( client->outBox[0], sizeof(client->outBox[0]) );
         }
       }
*/
       // CPU Sleep Section
       // Sleep( Until Ready to Process Next Pulse );

       gettimeofday( &lastTime, NULL );
       currentTime = (time_t) lastTime.tv_sec;

     }
   }


   void makeClientList(){
     clientList = new Client*[maxClients];
   }

   void cleanClientList() {
     delete [] clientList;
   }
