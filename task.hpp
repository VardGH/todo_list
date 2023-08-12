#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <time.h>

class Task 
{
public:
    Task();
    Task(const std::string&, const bool, const time_t);

public:
    // Setters
    std::string get_description() const;
    bool get_completed() const;
    time_t get_deadline() const;

    // Setters
    void set_description(const std::string&);
    void set_completed(const bool);
    void set_deadline(const time_t);

public:
    std::string get_status() const; // Get the status of the task (completed or not)
    bool is_approaching_deadline() const; // Check if the task's deadline is approaching

private:
    std::string m_description;
    bool m_completed;
    time_t m_deadline;
};

#endif //TASK_HPP