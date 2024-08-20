/**
 * Singleton Desgin Pattern
 * 
 * In this example, a chatbot platform is shown. The client can create new chatbot by
 * giving choosing a name of the chatbot. But only one chatbot instance is allowed, 
 * which will also deal with all chatbot requests after the instantiation. This means
 * That after a chatbot is created, further creation requests will return the already 
 * created bot to the client.
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
 * Thread which acquires the chatbot A.
*/
void ThreadChatbotA() {
    std::this_thread::sleep_for(std::chrono::seconds(2));   // emulates slow initialization
    Chatbot* chatbot = Chatbot::GetChatBotInstance("Chatbot A");
    std::cout << chatbot->GetChatbotName() << "\n";
}

/**
 * Thread which acquires the chatbot B.
*/
void ThreadChatbotB() {
    std::this_thread::sleep_for(std::chrono::seconds(1));   // emulates slow initialization
    Chatbot* chatbot = Chatbot::GetChatBotInstance("Chatbot B");
    std::cout << chatbot->GetChatbotName() << "\n";
}

/**
 * Client code
*/
int main() {
    std::cout << "Creating chatbots:\n";
    std::thread t1(ThreadChatbotA);
    std::thread t2(ThreadChatbotB);
    std::thread t3(ThreadChatbotA);
    t1.join();
    t2.join();
    t3.join();

    return 0;
}