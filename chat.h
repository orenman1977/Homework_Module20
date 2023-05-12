/*
    Чат на основе контейнеров библиотеки STL
*/

#pragma once

#include <map>
#include <set>
#include <memory>
#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "sha1.h"

using namespace std;

class Chat{

    // структура для хранения сообщения
    struct Message{
        string _from;
        string _to;
        string _message;

        Message():
            _from(""),
            _to(""),
            _message("")
            {}

        Message(string& from, string& to, string& message):
            _from(from),
            _to(to),
            _message(message)
            {}

        ~Message(){
            //cout << "Message " << _message << " destroyed" << endl;
        }
    };



public:
    Chat();     // init
    ~Chat();
    void enter();

private:
    void registerUser(string name, string login);
    void loginUser(string name, string login);

    void input(string& str, int len);                   // ввод с фильтрацией
    void mainLoop(string& name);                        // чат
	void otsev(const char* buf,int len);
    Message* fillMessage(string& name, string& buf);    // парсинг введённой строки

    map<string, unique_ptr<uint[]>> _registeredUsers;   // <name, SHA-1 hash>
    set<string> _loginedUsers;                          // users in chat
    set<unique_ptr<Message>> _storedMessages;           // all messages
	int socket_file_descriptor;
};
