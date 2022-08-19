#![allow(clippy::needless_return)] // I'm going to keep on returning. It's easier to read
mod misc;
mod os_desc;
mod package_manager;
mod file_setup;

use package_manager::PackageManager;
use misc::Misc as M;
use os_desc::OS;
use file_setup::*;

/* Mainly just as a cookbook or sorts:
 * 1) Run programs easily and see outputs
 * 2) Run programs with elevated privileges
 * 3) Disregard 2, don't do that. Make them use sudo <program> if they want to do that
 */
fn main() 
{
    // Eventually this will be from a file
    // TODO: Get package manager appropriate versions for:
    // Arch, Debian, and Freebsd
    // TODO: Ask if dwmblocks is wanted
    let packages = vec![
        "libX11-devel", "libXft-devel",
        "libXinerama-devel", "xsetroot",
        "wmname", "fontawesome5-fonts-all"
    ]; 

    // Install dependencies
    let package_manager = PackageManager::new();
    package_manager
        .install(packages)
        .expect("Error installing packages");

    // Compile
    M::run("make clean install").unwrap();
    // Setup required files
    DwmDesktop::write_file();
    Xsession::write_file();
    // chmod(args.get(1).unwrap().clone()).unwrap();
}
