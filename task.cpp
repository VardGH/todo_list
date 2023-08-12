#include "task.hpp"

Task::Task()
    : m_description("")
    , m_completed(false)
    , m_deadline(0)
{
}

Task::Task(const std::string& description, const bool completed, const time_t deadline)
    : m_description {description}
    , m_completed {completed}
    , m_deadline {deadline}
{
}

std::string Task::get_description() const
{
    return m_description;
}

bool Task::get_completed() const
{
    return m_completed;
}

time_t Task::get_deadline() const
{
    return m_deadline;
}

std::string Task::get_status() const
{
    return m_completed ? "done" : "unfulfilled";
}

bool Task::is_approaching_deadline() const 
{
    time_t current_time = time(nullptr);
    return !m_completed && (m_deadline - current_time < 24 * 60 * 60);
}

void Task::set_description(const std::string& description)
{
    m_description = description;
}

void Task::set_deadline(const time_t deadline)
{
    m_deadline = deadline;
}

void Task::set_completed(const bool completed)
{
    m_completed = completed;
}