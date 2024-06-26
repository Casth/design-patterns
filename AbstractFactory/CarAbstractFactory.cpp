#include <iostream>
#include <string>

/**
 * Abstract Factory Design Pattern
 * 
 * In this example, a calendar control system is shown. It can connect to different
 * commercial calendars including Google, Outlook, or local calendar on computer. 
 * Calendar entries can be created with given starting time, duration, and title. 
 * Everytime an entry is created, a reminder item is also created in the same calendar.
*/

/**
 * Abstract calendar entry (Abstract product A)
*/
class CalendarEntry {
  public:
    std::string time_start;
    std::string duration;
    std::string title;
    virtual ~CalendarEntry(){};
    virtual std::string ShowCalendarEntryInfo() const = 0;
};



/**
 * Concrete calendar entry for Google (Concrete product A1)
*/
class GoogleCalendarEntry : public CalendarEntry {
  public:
    std::string ShowCalendarEntryInfo() const override {
        return "Google calendar entry: " 
                + this->title
                + " starting at " 
                + this->time_start
                + " for duration of "
                + this->duration;
    }
};




/**
 * Concrete calendar entry for Outlook (Concrete product A2)
*/




/**
 * Concrete calendar entry on local computer (Concrete product A3)
*/










/**
 * Abstract reminder item (Abstract product B)
*/
class ReminderItem {
  public:
    std::string title;
    virtual ~ReminderItem(){};
    ReminderItem(CalendarEntry &calender_entry){};
    std::string ShowReminderItemInfo() {
        return this->title;
    }

};



/**
 * Concrete reminder item for Google (Concrete product B1)
*/
class ReminderItemGoogle : public ReminderItem {
  public:
    ReminderItemGoogle(CalendarEntry &calender_entry) : ReminderItem(calender_entry) {
        this->title = "Google reminder: " + calender_entry.title;
    }
};




/**
 * Concrete reminder item for Outlook (Concrete product B2)
*/




/**
 * Concrete reminder item on local computer (Concrete product B3)
*/








/**
 * Abstract calendar system (Abstract factory)
*/
class CalendarSystem {
  public:
    virtual CalendarEntry *CreateCalendarEntry() const = 0;
    virtual ReminderItem *CreateReminderItem(CalendarEntry &calender_entry) const = 0;
};



/**
 * Concrete calendar system of Google (Concrete factory 1)
*/
class GoogleCalendarSystem : public CalendarSystem {
  public:
    CalendarEntry *CreateCalendarEntry() const override {
        return new GoogleCalendarEntry();
    }
    ReminderItem *CreateReminderItem(CalendarEntry &calender_entry) const override {
        return new ReminderItemGoogle(calender_entry);
    }
};



/**
 * Concrete calendar system of Outlook (Concrete factory 2)
*/




/**
 * Concrete calendar system on local computer (Concrete factory 3)
*/






/**
 * Client code
*/