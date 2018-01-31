# keylogger #

# Description #

This is a keylogger.  I created it so that I could understand how one could go about detecting keyloggers that may have different behavior.  Rather than finding one every time I wanted a particular behavior, I decided to write one.

# Details #

This was created using Code::Blocks in Windows (with included mingw compiler).  It has been successfully compiled and tested in 32- and 64-bit versions of Windows 7, 8, and 10.  You should be able to download Code::Blocks and open it.  It compiles as a statically-linked binary, so no dependencies necessary from the OS.

It currently stores the log as output.txt.  Every 10 minutes, it uploads the contents of the log to an FTP server that you specify.  Feel free to adjust to your needs.  It also adds a key to the registry for persistence across reboots.

# Disclaimer #

This was written for research purposes only.  Please do not do anything stupid with it.  If you get caught, that's on you.  I cannot be held responsible for others' bad decisions.
Though I wrote most of this code, I'm sure I grabbed pieces from other places.
