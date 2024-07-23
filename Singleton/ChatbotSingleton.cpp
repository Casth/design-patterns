/**
 * Singleton Desgin Pattern
 * 
 * In this example, a chatbot platform is shown. The user can create new chatbot by
 * calling the corresponding category of the bot, such as "math", "language", 
 * "drawing", etc. A chatbot of a category can only be instantiated once. This means
 * That after a specific chatbot is created, further creation request will return 
 * the already created bot to the user.
*/

#include <iostream>
#include <string>
#include <thread>


/**
 * Singleton class
*/
class Chatbot {
  protected:
    Chatbot(const std::string chatbot_name): chatbot_name_(chatbot_name) {}
    static Chatbot* chatbot_;
    std::string chatbot_name_;

  public:
    Chatbot(Chatbot &other) = delete;
    void operator=(const Chatbot &) = delete;
    static Chatbot *GetChatBotInstance(const std::string& chatbot_name);
    std::string GetChatbotName() const {
        return chatbot_name_;
    }
};

Chatbot* Chatbot::chatbot_ = nullptr;

Chatbot *Chatbot::GetChatBotInstance(const std::string& chatbot_name) {
    // xxxxx
}

void ThreadChatbotMath() {
    // xxxxx
}

void ThreadChatbotLanguage() {
    // xxxxx
}

int main() {
    // xxxxx
}