#include "todo_list.hpp"

#include <iostream> 
#include <fstream>
#include <limits>
#include <sstream>
#include <iomanip>
#include <cstring>

void TodoList::creat_task(const std::string& description, const bool completed, const time_t deadline)
{
    // Create a new Task object
    m_tasks.emplace_back(Task(description, completed, deadline));

    // Save the updated task list to the file after adding the new task
    save_to_file(file_name);
}

void TodoList::update_task(const int index, const std::string& new_description)
{
    // Check if the provided index is within the valid range
    if (index >= 0 && index < m_tasks.size()) {
        // Update the description of the task at the specified index
        m_tasks[index].set_description(new_description);

        // Save the updated task list to the file after updating the task description
        save_to_file(file_name);
    } else {
        // Display an error message if the provided index is out of range
        std::cout << "Incorrect index!" << std::endl;
    }
}

void TodoList::delete_task(const int index)
{
    // Check if the provided index is within the valid range
    if (index >= 0 && index < m_tasks.size()) {
        // Erase the task at the specified index from the task vector
        m_tasks.erase(m_tasks.begin() + index);

        // Save the updated task list to the file after deletion
        save_to_file(file_name);
    } else {
        // Display an error message if the provided index is out of range
        std::cout << "Incorrect index!" << std::endl;
    }
}

void TodoList::mark_as_done(const int index)
{
    // Check if the provided index is within the valid range
    if (index >= 0 && index < m_tasks.size()) {
        // Mark the task at the specified index as completed
        m_tasks[index].set_completed(true);

        // Save the updated task list to the file after marking as done
        save_to_file(file_name);
    } else {
        // Display an error message if the provided index is out of range
        std::cout << "Incorrect index!" << std::endl;
    }
}

void TodoList::display_tasks() const
{
    std::cout << "Task List:" << std::endl;
    for (int i = 0; i < m_tasks.size(); ++i) {
        const Task& task = m_tasks[i];
        std::string description = task.get_description();
        std::string status = task.get_status();

        // Check if the task's deadline is approaching, and mark it as urgent if true
        if (task.is_approaching_deadline()) {
            description += " URGENT!";
        }

        // Display the task index, status, and description
        std::cout << i << " | [" << status << "] description: " << description;
        std::cout << std::endl;
    }
}

void TodoList::save_to_file(const std::string& filename) const 
{
    std::ofstream save_file(filename);

    if (!save_file.is_open()) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return;
    }

    for (const Task& task : m_tasks) {
        save_file << "description: " << task.get_description() << std::endl;
        save_file << "status: " << task.get_status() << std::endl;

        // Format the deadline using strftime and local time
        char buffer[80];
        time_t t = task.get_deadline();
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&t));

        // Split the formatted deadline into date and time components
        std::istringstream iss(buffer);
        std::string deadline_date, deadline_time;
        iss >> deadline_date >> deadline_time;

        save_file << "deadline_date: " << deadline_date << std::endl;
        save_file << "deadline_time: " << deadline_time << std::endl;
        save_file << std::endl; // Add a newline between tasks
    }
    save_file.close();
}

void TodoList::load_from_file(const std::string& filename) 
{
    std::ifstream load_file(filename);

    if (!load_file.is_open()) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return;
    }

    m_tasks.clear(); // Clear existing tasks before loading

    while (load_file) {
        std::string description;
        std::string status;
        std::string deadline_date;
        std::string deadline_time;

        // Read task information directly using formatted input
        load_file.ignore(std::numeric_limits<std::streamsize>::max(), ':');
        std::getline(load_file, description);
        load_file.ignore(std::numeric_limits<std::streamsize>::max(), ':');
        std::getline(load_file, status);
        load_file.ignore(std::numeric_limits<std::streamsize>::max(), ':');
        std::getline(load_file, deadline_date);
        load_file.ignore(std::numeric_limits<std::streamsize>::max(), ':');
        std::getline(load_file, deadline_time);

        if (!description.empty() && !status.empty() && !deadline_date.empty() && !deadline_time.empty()) {
            // Combine date and time strings to create a full deadline string
            std::string deadline_str = deadline_date + " " + deadline_time;

            time_t time = convert(deadline_str);
            if (time != -1) { 
                bool completed = (status == "done");
                m_tasks.push_back(Task(description, completed, time));
            }
        }
    }

    load_file.close();
}

time_t TodoList::convert(const std::string& deadline_str) 
{
    // Specify the expected format of the deadline string
    const char* format = "%Y-%m-%d %H:%M:%S";

    struct tm time_struct;
    memset(&time_struct, 0, sizeof(struct tm)); // Initialize to zeros

    // Set tm_isdst to -1 to allow the system to determine Daylight Saving Time
    time_struct.tm_isdst = -1;

    // Parse the deadline string using the specified format
    if (strptime(deadline_str.c_str(), format, &time_struct) == nullptr) {
        return -1; // Return -1 to indicate parsing error
    }

    // Convert the parsed time components to a time_t value
    time_t converted_time = mktime(&time_struct);

    if (converted_time == -1) {
        return -1; // Return -1 to indicate conversion error
    }

    // Return the successfully converted time_t value
    return converted_time;
}
