# Path_Finder
Use this program to map out all files and folders stemming from once source file.
This application will be most useful in files where paths are explicitly stated within the code.
## How It Works
To begin, the app will read through the code of the file passed as a command line argument.
```
./a.out /mnt/c/Documents/Project/index.html
```
All strings found within that file are processed and run through a function to determine if any of the strings consist of a valid path within a directory.
Each valid path is added to a temporary directory called `Map` within the Path_Finder directory.
Additionally, all files found whose extension match one of the extensions set in the beginning of `Process.h` will each be read and searched for more paths.
Finally, all directories are searched for a default file which can be set at the beginning of `Process.h`. Default files will be read and searched.
This builds a realistic model of your working directory and will help you determine which files and folders are neccessary to your working product and which are no longer needed.
