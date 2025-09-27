#include <gtkmm.h>
#include <iostream>
void isRoot(); // We need root for installing packages
std::string checkDistro(); // Use the correct package manager
bool isFileEmpty(std::ifstream& file); // For readErr();
void readErr(Gtk::Label* poplabel); // Get error from install_log.txt
void removePkg(std::string name, std::string text); // Remove said packages
void installPkg(std::string name, std::string text); // Install said packages
void abuttonClicked(Gtk::Window* aboutwindow); // For the about button
void rbuttonClicked(Gtk::Entry* entry, Gtk::Window* popwindow, Gtk::Label* poplabel); // For the remove button
void ibuttonClicked(Gtk::Entry* entry, Gtk::Window* popwindow, Gtk::Label* poplabel); // For the install button
