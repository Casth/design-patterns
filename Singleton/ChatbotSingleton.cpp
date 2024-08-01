/**
 * Singleton Desgin Pattern
 * 
 * In this example, a chatbot platform is shown. The user can create new chatbot by
 * naming a category of topic, such as "math", "language", "drawing", etc. Only one 
 * chatbot instance is allowed, which can deal with all the topics. This means
 * That after a chatbot is created, further creation requests will return the already 
 * created bot to the user.
*/

#include <iostream>
#include <string>
#include <thread>

/**
 * Singleton class: Chatbot instance cannot be cloned or assigned. This makes sure
 * that only one instance of a specific chatbot exsits.
*/
class Chatbot {
  protected:
    Chatbot(const std::string chatbot_name): chatbot_name_(chatbot_name) {}
    static Chatbot* chatbot_;
    std::string chatbot_name_;

  public:
    Chatbot(Chatbot &other) = delete;   // cloning forbidden
    void operator=(const Chatbot &) = delete; // assignment forbidden
    
    // static method will be defined outside of the class
    static Chatbot *GetChatBotInstance(const std::string& chatbot_name);  

    // other methods of Chatbot, such as get name of the bot
    std::string GetChatbotName() const {
        return chatbot_name_;
    }
};

// Assign the static attribute chatbot_ outside of the class, pointing to nothing
Chatbot* Chatbot::chatbot_ = nullptr;

/**
 * Define the static method outside of the class, which creates the already instantiated
 * chatbot, or creates a new chatbot instance if no chatbot exists.
*/
Chatbot *Chatbot::GetChatBotInstance(const std::string& chatbot_name) {
    if (chatbot_ == nullptr) {
        chatbot_ = new Chatbot(chatbot_name);
    }
    return chatbot_;
}

/**
 * Thread which acquires the chatbot for math topics.
*/
void ThreadChatbotMath() {
    std::this_thread::sleep_for(std::chrono::seconds(2));   // emulates slow initialization
    Chatbot* chatbot = Chatbot::GetChatBotInstance("Math");
    std::cout << chatbot->GetChatbotName() << "\n";
}

/**
 * Thread which acquires the chatbot for language topics.
*/
void ThreadChatbotLanguage() {
    std::this_thread::sleep_for(std::chrono::seconds(1));   // emulates slow initialization
    Chatbot* chatbot = Chatbot::GetChatBotInstance("Language");
    std::cout << chatbot->GetChatbotName() << "\n";
}

/**
 * Client code
*/
int main() {
    std::cout << "Creating chatbots:\n";
    std::thread t1(ThreadChatbotMath);
    std::thread t2(ThreadChatbotLanguage);
    std::thread t3(ThreadChatbotMath);
    t1.join();
    t2.join();
    t3.join();

    return 0;
}