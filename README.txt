NOTE: THE APPLICATION WORKS PERFECTLY IN DEFAULT (80*24) TERMINAL SIZE AND ANY SIZE ABOVE THAT. 

1. Normal Mode:
	a.When the application is launched ,it starts in normal mode.
	b.Use up and down arrow keys to navigate between files and directories in the list.
	c.Use Enter key to open files and directories. 
	d. User should be able to navigate up & down the file list using
	e.On pressing left arrow key the file explorer goes back to the previously visited directory.
	f.On pressing right arrow key the file explorer goes forward to the next directory.
	g.On pressing backspace it goes up one level.	
	h.On pressing ‘h’ key,it goes to the home folder.
	i.On pressing colon key(:) the application goes to command mode.

2.Command Mode:
	NOTE:COMMANDS WORK WITH RELATIVE AS WELL AS ABSOLUTE PATH.
	NOTE:FILENAME SHOULD NOT CONTAIN SPACES.
	THE FOLLOWING COMMANDS HAVE BEEN IMPLEMENTED:
	a.Copy :copy <source_file(s)> <destination_directory>
	b.Move :move <source_file(s)> <destination_directory>
	c.Rename :rename <old_filename> <new_filename>
	d.Create file :create_file <file_name> <destination_path>
	e.Create directory :create_dir <dir_name> <destination_path>
	f.Delete file​ :delete_file <file_path>
	g.Delete directory :delete_dir <directory_path>
	h.Goto :goto <location>
	i.Snapshot :snapshot <folder> <dumpfile>​ 
NOTE:
ESCAPE KEY FUNCTIONALITY : To Switch from normal mode to command mode :Type "esc" + Enter Key or "n" + Enter Key
	
TO QUIT THE APPLICATION: Type quit and enter.
