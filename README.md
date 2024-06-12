pdcurses.lib was built in 'x86', so need to build all project in 'x86'.

Commands to build project: 

- cmake -A Win32 -S .. -B "build32"
- cmake --build build32 --config Release
