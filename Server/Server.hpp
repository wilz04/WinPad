#ifndef Server_hpp
#define Server_hpp

#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include "File.hpp"

class Server {
  
  private: SOCKET cx;
  private: File *myFile;
  
  public: Server() {
    myFile = new File(".txt");
    bool success = false;
    WSADATA info;
    sockaddr_in meAddr;
    SOCKET newCx;
    sockaddr clientAddr;
    int size = sizeof(sockaddr);
    char *cmd = new char();
    char *argA = new char();
    char *argB = new char();
    char *argC = new char();
    
    if (!WSAStartup(MAKEWORD(1, 1), &info)) {
      cx = socket(AF_INET, SOCK_STREAM, 0);
      if (cx != INVALID_SOCKET){
        meAddr.sin_family = AF_INET;
        meAddr.sin_addr.s_addr = INADDR_ANY;
        meAddr.sin_port = htons(4000);
        if (!bind(cx, (sockaddr*) &meAddr, sizeof(sockaddr_in))) {
          if(!listen(cx, SOMAXCONN)) {
            newCx = accept(cx, &clientAddr, &size);
            if (newCx != INVALID_SOCKET) {
              success = true;
            }
          }
        }
      }
    }
    if (!success) {
      exit(0);
    } else {
      printf("WinPad Server started!");
    }
    do {
      recv(newCx, cmd, 32668, 0);
      argA = parse(cmd, 0);
      argB = parse(cmd, 1);
      argC = parse(cmd, 2);
      switch (atoi(argA)) {
        case 1:
          myFile->create(argB);
          break;
        case 2:
          argB = myFile->open(argB);
          if (argB != NULL) {
            send(newCx, argB, strlen(argB)*2, 0);
          }
          break;
        case 3:
          myFile->save(NULL, argB);
          break;
        case 4:  
          myFile->save(argB, argC);
          break;
        default:
          break;
      }
    } while (strcmp(argA, "5"));
    closesocket(cx);
    closesocket(newCx);
    WSACleanup();
  }
  
  private: char *parse(char *cmd, int n) {
    char *args[] = {"", "", ""};
    char *temp = new char[32668];
    int i = 0;
    int j = 0;
    int k = 0;
    for (i=0; i<=strlen(cmd); i++) {
      if ((cmd[i] != '|') && (cmd[i] != '\0')) {
        temp[j] = cmd[i];
        j++;
      } else {
        temp[j] = '\0';
        args[k] = temp;
        temp = new char[32668];
        j = 0;
        k++;
      }
    }
    return args[n];
  }
  
};

#endif

