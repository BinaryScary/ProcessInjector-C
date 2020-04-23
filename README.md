# ProcessInjector-C
A Process Injector build in C using windows API.
```
Usage: ProcessInjector [PID] [DLL.dll]
```

Procedure:
  - Obtains Handle from PID
  - Allocates memory in target process
  - Writes path of DLL
  - Creates a remote thread with a LoadLibraryA starting address, and the DLL allocation passed
