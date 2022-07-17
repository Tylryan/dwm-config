#!/usr/bin/bash

STARTER_SCRIPT_PATH="/usr/share/X11/Xsession"
DWM_SOURCE_LOCATION="https://git.suckless.org/dwm"

main()
{
    # install_xorg
    install_st_terminal &&
    # download_dwm
    install_with_dependencies &&
    create_xsession &&
    create_starter_script
    # chown_dwm
}

download_dwm()
{
    git clone $DWM_SOURCE_LOCATION
    mv dwm .. && cd ../dwm
}

install_with_dependencies()
{
    sudo dnf install libX11-devel libXft-devel libXinerama-devel 
    sudo make clean install
}

create_xsession()
{
    #This goes in /usr/share/xsessions/dwm.desktop
    sudo echo -e "[Desktop Entry]\r
Encoding=UTF-8\r
Name=DWM\r
Comment=Dymanic window manager\r
Exec="${STARTER_SCRIPT_PATH}"\r
Icon=dwm\r
Type=Xsession"  > /usr/share/xsessions/dwm.desktop
}

create_starter_script() 
{
    # This goes in /usr/share/X11/Xsession
    cur_dir="$(pwd)"
    sudo echo -e "# source for the terminal\r
xrdb -merge $HOME/.xres &\r
#font\r
xset fp+ $HOME/.fonts &\r
xset fp rehash &\r 
# Set keyboard layout to us\r 
setxkbmap us & \r 
setxkbmap -option caps:swapescape & \r
\r 
exec "${cur_dir}"/dwm" > $STARTER_SCRIPT_PATH
    sudo chmod +x $STARTER_SCRIPT_PATH
}

install_st_terminal()
{
    sudo dnf install st
}

chown_dwm()
{
    cd .. && sudo chown $USER dwm
}

install_xorg()
{
    sudo dnf install xorg-x11-server xorg-x11-xinit-session xorg-x11-xauth
}
main
