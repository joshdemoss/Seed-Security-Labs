# Seed Security Labs

# Spectre Attack
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


