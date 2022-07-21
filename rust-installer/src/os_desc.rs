use std::io::Error;

// Eventually add more info about the OS
pub struct OS 
{
    pub name: String
}

impl OS
{
    pub fn new() -> Self 
    {
        let name = OS::get_name().expect("Error: Could not get OS Name");
        Self {name}
    }

    pub fn get_name() -> Result<String, String>
    {
        let os_info_path = "/etc/os-release";
        let contents = match OS::read_file(os_info_path)
        {
            Ok(c) => c,
            Err(_) => return Err(String::from("Error: Need to find out where this Distro hides it's info."))
        };

        return OS::grep_for("ID", contents, os_info_path);
    }

    fn grep_for(string: &str, file_contents: String, os_info_path: &str) -> Result<String, String>
    {
        for line in file_contents.lines()
        {
            // Save memory and do it only if you find a match
            if line.contains(string) 
            {
                let cleaned = line
                    .split('=')
                    .last()
                    .unwrap()
                    .trim_matches('"')
                    .to_string();
                return Ok(cleaned)
            }
        }
        let error_msg = format!("Error: Could not find \"ID\" in {os_info_path}");
        Err(error_msg)

    }

    fn read_file(file_path: &str) -> Result<String, Error>
    {
        std::fs::read_to_string(file_path)
    }
}
