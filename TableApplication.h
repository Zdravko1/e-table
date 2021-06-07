#ifndef TABLE_APPLICATION_H
#define TABLE_APPLICATION_H
#include "Table.h"
#include "util/Vector.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using string = std::string;

class TableApplication {
  private:
    Table table;
    bool running;
  public:
    TableApplication() {
      running = true;
    }
    void run() {
      cout << "Application has started." << endl;
      while (running) {
        cout << "> ";
        char input[256];
        cin.getline(input, 256);
        Vector<string> commands;
        commands = splitCommand(string(input));

        if (commands[0] == "open") {
          table.open(commands[1].c_str());
        } else if (commands[0] == "print") {
          table.print();
        } else if (commands[0] == "edit") {
          // int validation?
          table.edit(stoi(string(commands[1].c_str())), stoi(string(commands[2].c_str())), string(commands[3].c_str()));
        } else if (commands[0] == "save") {
          table.save();
        } else if (commands[0] == "saveas") {
          table.saveAs(commands[1].c_str());
        } else if (commands[0] == "close") {
          table.close();
        } else if (commands[0] == "exit") {
          cout << "Exitig..." << endl;
          running = false;
        } else if (commands[0] == "help") {
          cout << "Following commands are available:" << endl
               << "open <file_name> - opens a file" << endl
               << "close            - closes the currently opened file" << endl
               << "save             - saves the currently opened file" << endl
               << "saveas           - saves the currently opened file in a new <file_name>" << endl
               << "exit             - exits the program." << endl;
        } else {
          cout << "Invalid command." << endl;
        }
      }
    }

    Vector<string> splitCommand(const string &command) {
      string delimiter = " ";
      int start = 0;
      int end = command.find(delimiter);
      Vector<string> commands;

      while (end != string::npos) {
        string splittedCommand = command.substr(start, end - start);
        commands.add(splittedCommand);
        start = end + 1;
        end = command.find(delimiter, start);
      }

      commands.add(command.substr(start, command.size() - end));
      return commands;
    }
};

#endif