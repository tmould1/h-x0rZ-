   #include "PracticalSocket.h"

   class Client {
     private :
       TCPSocket * mySocket;
       // PlayerInfo
     public :
       Client() { mySocket = 0; }
       ~Client() {  }
       void setSocket( TCPSocket * toSet ) { mySocket = toSet; }
       void getSocket( TCPSocket * sock ) { sock = mySocket; }
       void connectSocket( TCPServerSocket * servSock ) { mySocket = servSock->accept(); }
       int fd;
   };
