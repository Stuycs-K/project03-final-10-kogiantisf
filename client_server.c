#include "client_server.h"

int listen_to_connections(){
  char * pp_name = (char *) calloc(sizeof(char*),20);
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  char* PORT = "9998";


  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server
  getaddrinfo(NULL, PORT , hints, &results);  //NULL is localhost or 127.0.0.1

  //create socket
  int listen_socket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  //this code allows the port to be freed after program exit.  (otherwise wait a few minutes)
  int yes = 1;
  if ( setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1 ) {
      printf("sockopt  error\n");
      printf("%s\n",strerror(errno));
      exit(-1);
  }

  int err = bind(listen_socket, results->ai_addr, results->ai_addrlen);
  if(err == -1){
      printf("Error binding: %s",strerror(errno));
      exit(1);
  }


  listen(listen_socket, 3);//3 clients can wait to be processed
  printf("Listening on port %s\n",PORT);
//  printf("TEST\n");

  socklen_t sock_size;
  
  
  struct sockaddr_storage * client_addresses = (struct sockaddr_storage *) calloc(sizeof(struct sockaddr_storage *),10); //up to 10 connections
  
  sock_size = sizeof(struct sockaddr_storage);

  fd_set read_fds;

  char buff[19]=""; //newline later
  int address_ind = 0;
  
  int pid_index = 0;
  while(1){ //while server is active
    struct sockaddr_storage client_address;
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(listen_socket,&read_fds);
    int i = select(listen_socket+1, &read_fds, NULL, NULL, NULL);

    //if standard in, use fgets
//    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
//        fgets(buff, sizeof(buff), stdin);
//        buff[strlen(buff)-1]=0;
//        printf("Recieved from terminal: '%s'\n",buff);
//    }

    // if socket
    if (FD_ISSET(listen_socket, &read_fds)) {
      //accept the connection
      int client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
      printf("Connected, waiting for data.\n");

      //read the whole buff
      read(client_socket,buff, sizeof(buff));
      //trim the string
      buff[strlen(buff)-1]=0; //clear newline
      if(buff[strlen(buff)-1]==13){
          //clear windows line ending
          buff[strlen(buff)-1]=0;
      }
      
      
      printf("\nRecieved from client '%s'\n",buff); //these will be private pipe names
      
//      strcpy(pp_name,buff);
//      pid_index += 1;
      printf("writing pp_name: %s\n",buff);
      store_private_pipe(buff);
      printf("wrote pp_name\n");
      
      client_addresses[address_ind] = client_address;
      address_ind += 1;
      
      close(client_socket);
    }
  }



  free(hints);
  freeaddrinfo(results);
  return 0;
}

int send_pp_name(char * pp_name){
//  struct sockaddr_in * server_address;
  struct addrinfo * hints, *server_address;
  hints = calloc(1,sizeof(struct addrinfo));
  char* PORT = "9998";

  
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server

  // Resolve the server's address
  char* SERVER_IP = "127.0.0.1";
  if (getaddrinfo(SERVER_IP, PORT, hints, &server_address) != 0) {
    printf("getaddrinfo failed\n");
    err();
  }

  // Create a socket
  int client_socket = socket(server_address->ai_family, server_address->ai_socktype, server_address->ai_protocol);
  if (client_socket == -1) {
    printf("Socket creation failed\n");
    err();
  }

  // Connect to the server
  if (connect(client_socket, server_address->ai_addr, server_address->ai_addrlen) == -1) {
    printf("connection failed\n");
    close(client_socket);
    if (errno == 61){
      printf("server not online\n");
      exit(0);
    }else{
      err();
    }
  }

  printf("connected to server\n");

  // send private pipe name
  if (send(client_socket, pp_name, strlen(pp_name), 0) == -1) {
    printf("message sending failed\n");
    close(client_socket);
    err();
  }

  printf("message sent: %s\n", pp_name);

  // Close the socket
  close(client_socket);
  printf("connection closed\n");
  
  free(hints);
  return 0;
}

void store_private_pipe(char* pp_name){
  FILE * f = fopen("open_connections.txt","a");
  fwrite(pp_name,strlen(pp_name),1,f);
  printf("pp_name written\n");
  fwrite("\n",sizeof(char),1,f);
  fclose(f);
}

char * read_line(FILE * f){
  char * line = calloc(sizeof(char),100);
  char * buff = (char *) calloc(sizeof(char),2);
  
  int i = 0;
  int bytes_read = fread(buff,sizeof(char),1,f);
  while (bytes_read > 0 && strcmp(buff,"\n") != 0){
    line[i] = buff[0];
    i += 1;
    bytes_read = fread(buff,sizeof(char),1,f);
  }
  return line;
}

char ** get_private_pipes(){
  char ** pp_list = (char **) calloc(sizeof(char*),100);
  char * pp_name = (char *) calloc(sizeof(char),20);
  
  FILE * f = fopen("open_connections.txt","r");
  int pp_index = 0;
  pp_name = read_line(f);
  while (pp_name[0] != '\0'){
//    printf("%s",pp_name);
    pp_list[pp_index] = (char *) calloc(sizeof(char),20);
    strcpy(pp_list[pp_index],pp_name);
    pp_index += 1;
    pp_name = read_line(f);
  }
  fclose(f);
//  printf("%s",pp_name);
  return pp_list;
}
