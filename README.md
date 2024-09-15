# yt-download


This repository contains two main components:

1. **Download Scripts**: Batch scripts for downloading media files from URLs. These scripts support downloading in MP4 and MP3 formats.
2. **Clipboard Saver**: A C program that allows you to save clipboard contents to a file using a hotkey. **Ctr+Shift+S**
   
### Setup

1. Make sure `yt-dlp` is installed and available in your system's PATH.
2. Create the following `.txt` files:
   - `download.txt`: A list of URLs to download.
   - `log.txt`: (Automatically created if not present) Used to keep track of downloaded files.
   - `download.txt`: (Used by the clipboard saver program) Will be created automatically when the hotkey is pressed.
3. Ensure the C program executable is in your PATH or provide its full path when running the clipboard saver program.
