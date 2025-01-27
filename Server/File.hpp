#ifndef File_hpp
#define File_hpp

#include <stdio.h>
#include <string.h>

class File {
  
  private: char *url;
  private: char *ext;
  
  public: File(char *ext) {
    url = new char();
    this->ext = ext;
  }
  
  private: void addExt() {
    bool finded = false;
    for (int i=0; i<strlen(url); i++) {
      if (url[i] == '.') {
        finded = true;
        break;
      }
    }
    if (!finded) {
      strcat(url, ext);
    }
  }
  
  public: void create(char *fileName) {
    FILE *me;
    strcpy(url, "Files\\");
    strcat(url, fileName);
    addExt();
    if (!(me = fopen(url, "r"))) {
      me = fopen(url, "w");
      fclose(me);
    } else {
      fclose(me);
    }
  }
  
  public: char *open(char *fileName) {
    strcpy(url, "Files\\");
    strcat(url, fileName);
    addExt();
    HANDLE file = CreateFile(url, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    char* text = new char[32668];
    DWORD read;
    if (ReadFile(file, text, GetFileSize(file, NULL), &read, NULL)) {
      text[GetFileSize(file, NULL)] = '\0';
      CloseHandle(file);
      return text;
    } else {
      CloseHandle(file);
      return NULL;
    }
  }
  
  public: void save(char *fileName, char *text) {
    if (fileName != NULL) {
      strcpy(url, "Files\\");
      strcat(url, fileName);
      addExt();
    }
    if (strcmp(url, "")) {
      HANDLE file = CreateFile(url, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
      DWORD write;
      WriteFile(file, text, strlen(text), &write, NULL);
      CloseHandle(file);
    }
  }
  
};

#endif

