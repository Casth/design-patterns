#include <iostream>
#include <string>

/**
 * Abstract Factory Design Pattern
 *
 * In this example, a calendar control system is shown. It can connect to different
 * commercial calendars including Google, Outlook, or local calendar on computer.
 * Calendar entries can be created with given starting time, duration, and title.
 * Everytime an entry is created, a reminder item can be created in the same calendar
 * and is related to the corresponding calendar entry.
 */

/**
 * Abstract calendar entry (Abstract product A)
 */
class CalendarEntry
{
public:
  std::string date;
  std::string time_start;
  std::string duration;
  std::string title;
  virtual ~CalendarEntry(){};
  virtual void ShowCalendarEntryInfo() const = 0;
  CalendarEntry(std::string title, std::string date, std::string time_start, std::string duration)
  {
    this->title = title;
    this->date = date;
    this->time_start = time_start;
    this->duration = duration;
  }
};

/**
 * Concrete calendar entry for Google (Concrete product A1)
 */
class GoogleCalendarEntry : public CalendarEntry
{
public:
  using CalendarEntry::CalendarEntry;
  void ShowCalendarEntryInfo() const override
  {
    std::cout << "Google calendar entry: " + this->title + " on " + this->date + " starting at " + this->time_start + " for " + this->duration << "\n";
  }
};

/**
 * Concrete calendar entry for Outlook (Concrete product A2)
 */
class OutlookCalendarEntry : public CalendarEntry
{
public:
  using CalendarEntry::CalendarEntry;
  void ShowCalendarEntryInfo() const override
  {
    std::cout << "Outlook calendar entry: " + this->title + " on " + this->date + " starting at " + this->time_start + " for " + this->duration << "\n";
  }
};

/**
 * Concrete calendar entry on local computer (Concrete product A3)
 */
class LocalCalendarEntry : public CalendarEntry
{
public:
  using CalendarEntry::CalendarEntry;
  void ShowCalendarEntryInfo() const override
  {
    std::cout << "Local calendar entry: " + this->title + " on " + this->date + " starting at " + this->time_start + " for " + this->duration << "\n";
  }
};

/**
 * Abstract reminder item (Abstract product B)
 */
class ReminderItem
{
public:
  std::string title;
  std::string date;
  virtual ~ReminderItem(){};
  virtual void ShowReminderItemInfo() const = 0;
  ReminderItem(const CalendarEntry &calender_entry)
  {
    this->title = calender_entry.title;
    this->date = calender_entry.date;
  }
};

/**
 * Concrete reminder item for Google (Concrete product B1)
 */
class GoogleReminderItem : public ReminderItem
{
public:
  using ReminderItem::ReminderItem;
  void ShowReminderItemInfo() const override
  {
    std::cout << "Google reminder: " + this->title + " on " + this->date << "\n";
  }
};

/**
 * Concrete reminder item for Outlook (Concrete product B2)
 */
class OutlookReminderItem : public ReminderItem
{
public:
  using ReminderItem::ReminderItem;
  void ShowReminderItemInfo() const override
  {
    std::cout << "Outlook reminder: " + this->title + " on " + this->date << "\n";
  }
};

/**
 * Concrete reminder item on local computer (Concrete product B3)
 */
class LocalReminderItem : public ReminderItem
{
public:
  using ReminderItem::ReminderItem;
  void ShowReminderItemInfo() const override
  {
    std::cout << "Local reminder: " + this->title + " on " + this->date << "\n";
  }
};

/**
 * Abstract calendar system (Abstract factory)
 */
class CalendarSystem
{
public:
  virtual CalendarEntry *CreateCalendarEntry(std::string title, std::string date, std::string time_start, std::string duration) const = 0;
  virtual ReminderItem *CreateReminderItem(const CalendarEntry &calender_entry) const = 0;
};

/**
 * Concrete calendar system of Google (Concrete factory 1)
 */
class GoogleCalendarSystem : public CalendarSystem
{
public:
  CalendarEntry *CreateCalendarEntry(std::string title, std::string date, std::string time_start, std::string duration) const override
  {
    return new GoogleCalendarEntry(title, date, time_start, duration);
  }
  ReminderItem *CreateReminderItem(const CalendarEntry &calender_entry) const override
  {
    return new GoogleReminderItem(calender_entry);
  }
};

/**
 * Concrete calendar system of Outlook (Concrete factory 2)
 */
class OutlookCalendarSystem : public CalendarSystem
{
public:
  CalendarEntry *CreateCalendarEntry(std::string title, std::string date, std::string time_start, std::string duration) const override
  {
    return new OutlookCalendarEntry(title, date, time_start, duration);
  }
  ReminderItem *CreateReminderItem(const CalendarEntry &calender_entry) const override
  {
    return new OutlookReminderItem(calender_entry);
  }
};

/**
 * Concrete calendar system on local computer (Concrete factory 3)
 */
class LocalCalendarSystem : public CalendarSystem
{
public:
  CalendarEntry *CreateCalendarEntry(std::string title, std::string date, std::string time_start, std::string duration) const override
  {
    return new LocalCalendarEntry(title, date, time_start, duration);
  }
  ReminderItem *CreateReminderItem(const CalendarEntry &calender_entry) const override
  {
    return new LocalReminderItem(calender_entry);
  }
};

/**
 * Client code works with factory interface ("CalendarSystem") and product
 * interface ("CalendarEntry" and "ReminderItem").
 */
void ClientCode(const CalendarSystem &calendar_system)
{
  const CalendarEntry *calendar_entry = calendar_system.CreateCalendarEntry("Project meeting", "03.05.2024", "10:30 a.m.", "1 hour");
  const ReminderItem *reminder_item = calendar_system.CreateReminderItem(*calendar_entry);
  calendar_entry->ShowCalendarEntryInfo();
  reminder_item->ShowReminderItemInfo();
}

int main()
{
  std::cout << "Client: Using Google calendar system:\n";
  GoogleCalendarSystem *client_calendar_1 = new GoogleCalendarSystem();
  ClientCode(*client_calendar_1);
  delete client_calendar_1;

  std::cout << std::endl;

  std::cout << "Client: Using Outlook calendar system:\n";
  OutlookCalendarSystem *client_calendar_2 = new OutlookCalendarSystem();
  ClientCode(*client_calendar_2);
  delete client_calendar_2;

  std::cout << std::endl;

  std::cout << "Client: Using local calendar system:\n";
  LocalCalendarSystem *client_calendar_3 = new LocalCalendarSystem();
  ClientCode(*client_calendar_3);
  delete client_calendar_3;

  return 0;
}