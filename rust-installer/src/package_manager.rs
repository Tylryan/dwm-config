use crate::M;
use crate::OS;

#[derive(Debug)]
pub struct PackageManager
{
    pub name: String,
    pub install: String,
    pub uninstall: String
}

impl PackageManager 
{
    pub fn new() -> Self 
    {
        let package_manager_name = get_package_manager_name()
            .expect("Error: get_package_manager_name()");
        let (name, install, uninstall) = set_package_manager_info(package_manager_name).unwrap();

        Self { name, install, uninstall }
    }

    pub fn install(&self, packages: Vec<&str>) -> Result<(), std::io::Error>
    {
        println!("Installing Packages...");
        M::flush();
        for package in packages
        {
            let command = format!("{} {} {}", self.name, self.install, package);
            /* The below command is used for testing. Don't actually use 
             * sudo in your code */
            // let command = format!("sudo {} {} {}", self.name, self.install, package);
            M::run(&command)?;
        }
        Ok(())
    }

    pub fn uninstall(&self, packages: Vec<&str>) -> Result<(), std::io::Error>
    {
        for package in packages
        {
            let command = format!("sudo {} {} {} -y", self.name, self.uninstall, package);
            M::run(&command)?;
        }
        Ok(())
    }
}

fn set_package_manager_info(name: String) -> Option<(String, String, String)>
{
    match name.as_str()
    {
        "pacman" => Some((String::from("pacman"), String::from("-S"), String::from("-Rnsc"))),
        "apt"    => Some((String::from("apt"), String::from("install"), String::from("remove"))),
        "dnf"    => Some((String::from("dnf"), String::from("install"), String::from("remove"))),
        // TODO: Add Freebsd
        _        => None
    }
}

fn get_package_manager_name() -> Option<String>
{
    // Find distro automatically
    if let Ok(name) = OS::get_name()
    {
        let first_letter = name
            .chars()
            .next()
            .unwrap()
            .to_string();
        if let Some(package_manager) = match_distro_response(first_letter)
        {
            return Some(package_manager);
        };
    }

    M::print_title_screen();
    loop 
    {
        let response = M::prompt(Some("Which distro are you running? "));
        if let Some(package_manager) = match_distro_response(response)
        {
            return Some(package_manager);
        };
    }
}

fn match_distro_response(distro: String) -> Option<String>
{
    match distro.as_str()
    {
        "a" | "A" => Some(String::from("pacman")),
        "d" | "D" => Some(String::from("apt")),
        "f" | "F" => Some(String::from("dnf")),
        //TODO: Add Freebsd (B)
        _ => None
    }
}
