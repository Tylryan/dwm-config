#!/usr/bin/bash

STARTER_SCRIPT_PATH="/usr/share/X11/Xsession"
DWM_SOURCE_LOCATION="https://git.suckless.org/dwm"

main()
{
    install_st_terminal &&
    download_dwm &&
    install_with_dependencies &&
    create_xsession &&
    create_starter_script &&
}

download_dwm() 
{
    git clone $DWM_SOURCE_LOCATION
    cd dwm
}

install_with_dependencies()
{
    sudo dnf install $(cat dwm-requirements.txt)
    sudo make clean install
}

create_xsession()
{
    #This goes in /usr/share/xsessions/dwm.desktop
    echo -e "[Desktop Entry]\r
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
    echo -e "# source for the terminal\r
xrdb -merge $HOME/.xres &\r
#font\r
xset fp+ $HOME/.fonts &\r
xset fp rehash &\r 
# Set keyboard layout to us\r 
setxkbmap us & \r 
setxkbmap -option caps:swapescape & \r
\r 
exec "${cur_dir}"/dwm" > $STARTER_SCRIPT_PATH
}

install_st_terminal()
{
    sudo dnf install st
}

main
