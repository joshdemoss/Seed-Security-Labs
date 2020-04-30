# Seed Security Labs Descriptions

# Spectre Attack:
File: spectreattack.c

This program exploits a former vulnerability in many modern systems that allowed for the breaking
of intra and inter process isolation. This program is able to steal secret information by exploiting
the out of order execution feature that existed using a timing side channel attack.

How it works:
First train a sandbox function to access infromation using appropriate requests. For the 
Sandbox function, that would be giving restrictedAccess() an input less than the buffer size.

Then after the function is trained, request information that is not allowed. In the sandbox
function, this would be giving an input greater than the buffer size.

Out of order execution works by loading the answer to the request before it checks for access.
It does this in order to save time due to similar requests being permitted in the past. When the program
processes the access part, it throws does not provide the information that was requested. The flaw in the
design, though, is that while it does not provide the requested information, the requested information was loaded
into cache. Thus one can figure out what the secret value was by examining the cache after the access.

This is what this program does. It uses a cache timing side channel attack to discover secret information stored
in cache. This vulnerability is essentially used to perform a buffer overflow attack on a function that protects against
typical buffer overflow attacks.

# Arp Poisoning:
File: arppoisoning.py

In this project I was able to poison the ARP cache of neighboring systems by associating my MAC address with the IP address of other devices stored in other host's ARP cache. This way when Alice wants to send something to Bob, traffic will be forwarded to me where I can modify it before sending it on to Bob. Likewise I can also modify the replys sent back from Bob.

# XSS Attack:
File: xss.java | XSS.pdf

This attack was done on a out dated and vulnerable social media application. By inserting JavaScript into specific fields, I was able to develop a worm that would spread to other users and steal secret information. Since multiple different attacks were performed, it seemed more appropriate to include a pdf of the report along with the main attack which is stored as a java file (xss.java) for the sake of having github color code the file.

