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
bool isFileEmpty(const std::string& filename); // For readErr();
void readErr(Gtk::Label* poplabel); // Get error from install_log.txt
void installPkg(std::string name, std::string text); // Install said packages
void buttonClicked(Gtk::Entry* entry, Gtk::Window* popwindow, Gtk::Label* poplabel); // For the install button
int main(int argc, char* argv[]){
	isRoot();
	Gtk::Main kit(argc, argv);
	// Init GUI
	Gtk::Window window;
	Gtk::Window popwindow;
	Gtk::Box vbox(Gtk::ORIENTATION_VERTICAL, 10); // For the junk
	Gtk::Entry entry;
	Gtk::Button button("Install!");
	Gtk::Label label("Install your packages here!");
	Gtk::Label poplabel("Your package was being processed :-)");
	poplabel.set_halign(Gtk::ALIGN_CENTER);
	
	// Window properties
	window.set_default_size(250,140);
	window.set_title("chePackage");
	window.set_position(Gtk::WIN_POS_CENTER);
	window.set_resizable(false);
	popwindow.set_default_size(200,100);
	popwindow.set_title("Package status");
	popwindow.set_position(Gtk::WIN_POS_CENTER);
	popwindow.set_resizable(false);
	
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
		sigc::bind(sigc::ptr_fun(&buttonClicked), &entry, &popwindow, &poplabel)
	);
	button.set_size_request(150, 50);
	button.set_halign(Gtk::ALIGN_CENTER);
	vbox.pack_start(button, Gtk::PACK_SHRINK);
	
	// Wrap it up nicely
	window.add(vbox);
	popwindow.add(poplabel);
	vbox.show_all();
	Gtk::Main::run(window);
	return 0;
}

void buttonClicked(Gtk::Entry* entry, Gtk::Window* popwindow, Gtk::Label* poplabel){ 
	std::string text = entry->get_text();
	static std::string name = checkDistro();
	system("> install_log.txt");
	popwindow->resize(200,100); // Pkg names resize the window to fit content but don't resize it back
	installPkg(name, text);
	readErr(poplabel);
	popwindow->show_all();
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
		install = "sudo apt-get install -y " + text;
	}
	else if (name == "Arch Linux" || name == "CachyOS" || name == "endeavourOS"){
		install = "sudo pacman -S --noconfirm " + text;
	}
	else {
		std::cout << "Unsupported Linux distribution." << std::endl;
		exit(1);
	}
	install += " 2> install_log.txt";
	std::cout << install << std::endl;
	system(install.c_str());
}
bool isFileEmpty(std::ifstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}
void readErr(Gtk::Label* poplabel){
	std::string s;
	std::ifstream f("install_log.txt");
	if (!f.is_open()) {
        std::cerr << "Error opening the file!";
        exit(1);
    }
    if (isFileEmpty(f)){
		poplabel->set_text("Success!");
	} else {
		getline(f, s);
		poplabel->set_text(s);
	}

}
void isRoot(){
	if (getuid()){
		 std::cout << "Please run as Root. Exiting." << std::endl;
		 exit(1);
	}
}

