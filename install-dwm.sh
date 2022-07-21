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
    sudo dnf install libX11-devel libXft-devel libXinerama-devel xsetroot
    sudo make clean install
}

create_xsession()
{
    #This goes in /usr/share/xsessions/dwm.desktop
    sudo echo -e "[Desktop Entry]
Encoding=UTF-8
Name=DWM
Comment=Dymanic window manager
Exec="${STARTER_SCRIPT_PATH}"
Icon=dwm
Type=Xsession"  > /usr/share/xsessions/dwm.desktop
}

create_starter_script() 
{
    # This goes in /usr/share/X11/Xsession
    cur_dir="$(pwd)"
    sudo echo -e "# source for the terminal
xrdb -merge $HOME/.xres &
#font
xset fp+ $HOME/.fonts &
xset fp rehash &
# Set keyboard layout to us
setxkbmap us &
setxkbmap -option caps:swapescape &
feh --bg-fill "${cur_dir}"/background.jpg
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
