# mmid_private
A Poc module manual map Injection Detector.

# Information

This is simply a PoC (Proof of Concept) program that will continously check it's PEB (Process Environment Block) to get the process module's and compare it's current SizeOfImage to the one on disk.

If you are unsure what the PEB is check out the following links :

[MSDN 1](https://docs.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb)

[MSDN 2](https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/-peb)

[Wikipedia](https://en.wikipedia.org/wiki/Process_Environment_Block)

# Usage and Notes
Simply run the program, manually map your dll (dynamic link library) into one of the process modules, and see if your injection gets detected by the process.

There are many ways to bypass this, Such as :
- Inject outside of Process Modules
- Spoof the Process PEB
- Get creative, there are many ways to bypass this.

Since Windows's PEB structures are incomplete and their names are missing (the Reserved for internal use variables), I do not reference "winternl.h" in my code.

If you are compiling the program as x86, make sure you adjust the GetProcessPEB() accordingly (read my notes.)
