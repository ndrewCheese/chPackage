/* Package installer 
 * unknownversion 2025 */
#include <gtkmm.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <regex>
void isRoot(); // We need root for installing packages
std::string checkDistro(); // Use the correct package manager
void installPkg(std::string name, std::string text); // Install said packages
void buttonClicked(Gtk::Entry* entry); // For the install button
int main(int argc, char* argv[]){
	isRoot();
	Gtk::Main kit(argc, argv);
	// Init GUI
	Gtk::Window window;
	Gtk::Box box(Gtk::ORIENTATION_VERTICAL);
	Gtk::Box vbox(Gtk::ORIENTATION_VERTICAL, 10); // For the junk
	Gtk::Entry entry;
	Gtk::Button button("Install!");
	Gtk::Label label("Install your packages here!");
	
	// Window properties
	window.set_default_size(250,140);
	window.set_title("chePackage");
	window.set_position(Gtk::WIN_POS_CENTER);
	window.set_resizable(false);
	
	// Heading
    label.set_halign(Gtk::ALIGN_CENTER);
    label.set_margin_top(15);
    vbox.pack_start(label, Gtk::PACK_SHRINK);
    
    // Entry field
	entry.set_placeholder_text("Enter package name...");
	entry.set_size_request(200, -1);
	entry.set_halign(Gtk::ALIGN_CENTER);
	vbox.pack_start(entry, Gtk::PACK_SHRINK);
    
	// Button event & stuff
	button.signal_clicked().connect(
		sigc::bind(sigc::ptr_fun(&buttonClicked), &entry) // Funky stuff right there.
	);
	button.set_size_request(150, 50);
	button.set_halign(Gtk::ALIGN_CENTER);
	vbox.pack_start(button, Gtk::PACK_SHRINK);
	
	// Wrap it up nicely
	window.add(vbox);
	vbox.show_all();
	Gtk::Main::run(window);
	return 0;
}

void buttonClicked(Gtk::Entry* entry){ 
	std::string text = entry->get_text();
	static std::string name = checkDistro();
	installPkg(name, text);
}
std::string checkDistro(){
	std::ifstream stream("/etc/os-release");
    std::string line;
    std::regex nameRegex("^NAME=\"(.*?)\"$");
    std::smatch match;
    std::string name;
    while (std::getline(stream, line)) {
        if (std::regex_search(line, match, nameRegex)) {
            name = match[1].str();
            break;
        }
    }
    std::cout << name << std::endl;
	return name;
}

void installPkg(std::string name, std::string text){
	std::string install;
	if (name == "Debian" || name == "Ubuntu" || name == "Linux Mint"){
		install = "sudo apt install -y " + text;
	}
	else if (name == "Arch Linux" || name == "CachyOS" || name == "endeavourOS"){
		install = "sudo pacman -S --noconfirm " + text;
	}
	else {
		std::cout << "Unsupported Linux distribution." << std::endl;
		exit(1);
	}
	std::cout << install << std::endl;
	system(install.c_str());
}

void isRoot(){
	if (getuid()){
		 std::cout << "Please run as Root. Exiting." << std::endl;
		 exit(1);
	}
}

