# "ch" as in "🧀"
### When you're too scared to install a package using your terminal.
## Install
Make sure you have g++ and gtkmm-3.0 (libgtkmm-3.0-dev for debian-based) installed.
### Note
Works correctly only in X11. In wayland, a workaround is to execute
```cpp
xhost si:localuser:root
```
right before executing chPkg with sudo.

```cpp
git clone https://github.com/ndrewCheese/chPackage
cd chPackage/
./install.sh
sudo ./chPkg
```

