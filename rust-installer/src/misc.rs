use std::io::{Write,Error};
pub struct Misc { }


impl Misc 
{
    pub fn prompt(msg: Option<&str>) -> String
    {
        match msg 
        {
            Some(e) => {
                print!("{e}");
                Misc::flush();
            },
            None => ()
        };

        let mut buffer = String::new();
        std::io::stdin().read_line(&mut buffer).expect("Error Reading Stdin");
        Misc::flush();
        let buffer = buffer.trim().to_string();
        return buffer;
    }

    pub fn run(command: &str) -> Result<(), Error>
    {
        std::process::Command::new("bash")
            .arg("-c")
            .arg(command)
            .status()?;
        Ok(())


    }
    pub fn flush() 
    { 
        std::io::stdout().flush().unwrap(); 
    }

    pub fn print_title_screen()
    {
        println!("
[A/a] Arch
[D/d] Debian
[F/f] Fedora");
    }
}
