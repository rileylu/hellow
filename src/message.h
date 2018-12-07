#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <unordered_map>

class Message
{
public:
    Message();
private:
    std::unordered_map<std::string,std::string> headers_;
    std::string body_;
};

#endif // MESSAGE_H
