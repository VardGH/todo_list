#ifndef TODO_HPP
#define TODO_HPP

#include "task.hpp"

#include <vector>
#include <string>
#include <ctime>    // Include this header for std::mktime

class TodoList
{
public:
    TodoList() = default;
    ~TodoList() = default;

public:
    // // Task manipulation functions
    void creat_task(const std::string&, const bool, const time_t);
    void update_task(const int index, const std::string&);
    void delete_task(const int index);
    void mark_as_done(const int index);
    void display_tasks() const;

public:
    // // File operations
    void load_from_file(const std::string& filename);
    void save_to_file(const std::string& filename) const;

    // Utility function for converting date-time string to time_t
    time_t convert(const std::string&);

private:
    std::vector<Task> m_tasks;
    const std::string file_name = "todo_list.txt";
};

#endif // TODO_HPP