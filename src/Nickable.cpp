#include "Nickable.h"

void Nickable::setNickname(const char* nick) { nickname = nick; }
const char* Nickable::getNickname() const { return nickname; }
const char* Nickable::getPrintNickname() const { return (nickname ? nickname : "(unnamed)"); }
Nickable::Nickable(const char *nick) : nickname(nick) { }