#ifndef STRING_H
#define STRING_H
#include <fstream>

using uint = unsigned int;

class String {
  private:
    char* buffer;
    uint _size;
    uint _strlen(const char* str);
  public:
    String() {}
    String(const char* str);
    String(const String &other);
    ~String();

    String& operator= (const String& other);
    bool operator== (const String &other);
    String& operator+= (const String& other);
    char& operator[] (uint index);
    const char& operator[] (uint index) const;
    friend std::ostream& operator<< (std::ostream& os, const String &string);
    const uint size() const;
    const char* c_str() const;

    static String toString(double number);
};

#endif