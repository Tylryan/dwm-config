use crate::M;

static XSESSION_PATH: &str    = "/usr/share/X11/Xsession";
static DWM_DESKTOP_PATH: &str = "/usr/share/xsessions/dwm.desktop";

pub struct DwmDesktop {}
pub struct Xsession {}


impl DwmDesktop 
{
    pub fn write_file()
    {
        let cwd      = cwd();
        let contents = format!("[Desktop Entry]
Encoding=UTF-8
Name=DWM
Comment=Dynamic Window Manager
Exec={XSESSION_PATH}
Icon={cwd}/dwm.png
Type=Xsession");

        std::fs::write(DWM_DESKTOP_PATH, contents).expect("Could not write to dwm.desktop");
    }
}

impl Xsession 
{
    pub fn write_file() 
    {
        let cwd = cwd();
        let home = std::env::var("HOME").unwrap();
        let contents = format!("# source for the terminal
xrdb -merge {home}/.xres &
#font
xset fp+ {home}/.fonts &
xset fp rehash &
setxkbmap us &
# Swap escape and caps
setxkbmap -option caps:swapescape &
feh --bg-fill {cwd}/background.jpg &
wmname LG3D &
flameshot &
exec {cwd}/dwm");

        std::fs::write(XSESSION_PATH, contents).expect("Could not Write Xsession");
        let command = format!("chmod +x {}", XSESSION_PATH);
        M::run(&command).unwrap();
    }
}

fn cwd() -> String
{
    let cwd: String = std::env::current_dir()
        .unwrap()
        .to_string_lossy()
        .to_string();
    return cwd;
}
