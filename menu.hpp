#ifndef MENU_HPP
#define MENU_HPP

#include "todo_list.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

class Menu 
{
public:
    Menu();
public:
    void play(); // Initiates the menu interaction loop
    void display_menu() const; // Displays the menu options to the user

private:
    // Handle different menu options
    void handle_create_task();
    void handle_update_task();
    void handle_delete_task();
    void handle_mark_as_done();

private:
    TodoList m_todo;
};

#endif // MENU_HPP