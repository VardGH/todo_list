#include "menu.hpp"

Menu::Menu()
{
    m_todo.load_from_file("todo_list.txt");
}

void Menu::display_menu() const
{
    std::cout << "---------------------------" << std::endl;
    std::cout << "|        Todo List        |" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "|1. Create Task           |" << std::endl;
    std::cout << "|2. Update Task           |" << std::endl;
    std::cout << "|3. Delete Task           |" << std::endl;
    std::cout << "|4. Mark as Done          |" << std::endl;
    std::cout << "|5. Display Tasks         |" << std::endl;
    std::cout << "|0. Exit                  |" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Enter your choice: ";
}

void Menu::play() {
    int choice {};

    while (true) {
        display_menu();
        std::cin >> choice;

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            handle_create_task();
        } else if (choice == 2) {
            handle_update_task();
        } else if (choice == 3) {
            handle_delete_task();
        } else if (choice == 4) {
            handle_mark_as_done();
        } else if (choice == 5) {
            m_todo.display_tasks();
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

void Menu::handle_create_task() {
    std::string description;
    std::cout << "Enter task description: ";
    std::cin.ignore();
    std::getline(std::cin, description);

    std::string deadline_str;
    std::cout << "Enter deadline (YYYY-MM-DD HH:MM:SS): ";
    std::getline(std::cin, deadline_str);

    std::tm timeinfo = {};
    std::istringstream iss(deadline_str);
    iss >> std::get_time(&timeinfo, "%Y-%m-%d %H:%M:%S");

    if (iss.fail()) {
        std::cout << "Invalid deadline format. Please use YYYY-MM-DD HH:MM:SS." << std::endl;
    } else {
        time_t deadline = std::mktime(&timeinfo);
        if (deadline == -1) {
            std::cout << "Error converting deadline to time_t." << std::endl;
        } else {
            m_todo.creat_task(description, false, deadline);
        }
    }
}

void Menu::handle_update_task() {
    int index;
    std::cout << "Enter task index to update: ";
    std::cin >> index;

    std::string new_description;
    std::cout << "Enter new task description: ";
    std::cin.ignore();
    std::getline(std::cin, new_description);

    m_todo.update_task(index, new_description);
}

void Menu::handle_delete_task() {
    int index;
    std::cout << "Enter task index to delete: ";
    std::cin >> index;

    m_todo.delete_task(index);
}

void Menu::handle_mark_as_done() {
    int index;
    std::cout << "Enter task index to mark as done: ";
    std::cin >> index;

    m_todo.mark_as_done(index);
}