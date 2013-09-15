#Nanomite - Graphical Debugger for x64 and x86 on Windows

## Changelog
###Version 0.1 beta 15
+ fixed a bug which lead to a memory leak when a invalid file was loaded
+ fixed a bug which caused a break when continue was used after a trace
+ fixed a bug which caused problems when scrolling up in disassembler view
+ fixed a bug which returned wrong offset when adding a breakpoint to a wow64 process
+ fixed a bug which did not clean up properly if using the "recent file" menu to debug new process
+ fixed a bug which did not clean up properly if a process terminates in a multiprocess session
+ fixed a bug which did not replace memory breakpoints correctly
+ fixed a bug which did not display the correct source code under certain conditions
+ fixed a bug which did not reload the gui when deleting a patch from patchmanager using hotkey
+ fixed a bug which did not disable trace_stop button when the debuggee terminates while tracing
+ fixed a bug which did not allow breakpoints on int3 instructions
+ fixed a bug which may corrupted the memory breakpoints when a new thread starts
+ fixed a bug which may calculated wrong tls callback offsets
+ added save file dialog to memory dump and patch manager
+ added the correct offsets for loaded module imports in the peeditor
+ added double click handler in trace view, bp manager and patch manager to send a offset to disassembler window
+ added possibility to set nanomite also as wow64 jit debugger
+ added possibility to use Up/Down arrows and PageUp/Down to navigate in disassembler
+ added possibility to create a full process dump
+ added possibility to open function view for selected modules
+ added possibility to restart debugger with admin rights
+ added support for saving patches in dlls
+ added support of multiple tls callbacks
+ added "on execution" and "on write" memory breakpoint types
+ updated function view algorithm
+ updated winapi messagebox to qt

####Notes:
	- The full process dump can be done in detail view -> process tab -> context menu
	- The function view can now be showed also in detail view -> modules tab -> context menu
	
###Version 0.1 beta 14
+ fixed a bug in the options not showing exception wich have been saved using the exception assistant
+ fixed a bug when stepping over a return
+ fixed a bug in breakpoint manager which deleted the wrong bp when removing a selected bp
+ fixed a bug in breakpoint manager which created unusable breakpoints
+ fixed a bug in breakpoint manager which may resolved ModuleName::APIName to wrong offset
+ fixed a bug in assembler which double loaded the gui
+ fixed a bug in hardware breakpoints which did not activate them in running processes
+ fixed a bug in hardware breakpoints which did not activate them on the current thread
+ fixed a bug where by detaching from a suspended process didn't resume the process
+ fixed a bug which did not handle hardware breakpoints for wow64 targets
+ fixed a bug which showed a wrong menu if child processes where present in the debugging session
+ fixed a bug which reloaded the disassembler to the wrong offset after adding a new patch
+ fixed a bug which caused wrong scrolling of disassembler and stack while the process is running
+ fixed paths in attach dialog with SystemRoot enviroment string
+ fixed handling of "call * ptr []" and "jmp * ptr []"
+ fixed some handle and memory leaks
+ added saving of input in goto dialog 
+ added support of functions in goto dialog
+ added different hotkeys see hotkey list for all of them
+ added type column in attach dialog
+ added state update when doing a trace
+ added trace to selected disassembly line
+ added toggle breakpoint on selected disassembly line to context menu
+ added display of FPU, MMX and SSE register
+ updated to qt 4.8.5
+ updated nasm to 2.10.09
+ updated file open dialog to remove annoying messagebox for commandline
+ updated the internal pe handling
+ updated resize event of Disassembler and Stack
+ updated Stack scroll
+ updated PID dropdown to be only displayed if more then 1 process is running
+ updated disassembler logic

####Notes:
	- function in the goto dialog should look like this: "module::function"
	  e.g KERNEL32::IsDebuggerPresent
	  
###Version 0.1 beta 13
+ fixed some crashs related to the qt /MT build, see note for more details
+ fixed some bugs in the patch manager
+ fixed the symbol display in the trace view
+ fixed a bug which showed wrong trace data
+ added Exception Assistant
+ added colors to the state bar
+ added missing edi/rdi register
+ added option to break on tls callback
+ added possibility to show registers of a thread in detailview
+ added possibility to show TEB/TBI of a thread in detailview
+ added possibility to show PEB/PBI of a process in detailview
+ added possibility to set Nanomite as default just in time debugger
+ added possibility in PEEditor to show exports of a loaded module in disassembler
+ added updater (thanks to inisider for this contribution)
+ updated beaengine to rev. 174
+ updated PE-Editor layout
+ updated DetailView layout
+ updated Options to include more options, easier config 

####Notes:
	- Needed to compile Qt with /MD because of issues with the cruntime. If you want to use the
	  debugger you have to install the visual c++ runtime 2010. 
	- You can save an exception to the list in the Options window. The debugger then knows how to handle it.
	  Alternatively you can enable the Exception Assistant. This will show a dialog once a exception occures and
	  offers different ways to handle it.

###Version 0.1 beta 12
+ fixed scrollbar in trace view
+ fixed a possible crash in disassembler
+ fixed a memory leak in the window settings
+ fixed a memory leak in dll and process name receiving
+ fixed a memory leak in trace view
+ fixed display of ascii strings in ascii view
+ fixed a bug which could cause wrong run to user code if debugging more than one process
+ fixed a bug which lead to incorrect restarts on slow systems
+ fixed a bug which caused double calling of some functions in context menus
+ fixed a bug in hex view which may showed wrong data
+ fixed a bug in heap view which caused a crash when copying the whole line to clipboard
+ added PatchManager
+ added process privilege view
+ added commandline options
+ added possibility to set process priorities
+ added possibility to set memory protection
+ added display of current priority in detail view - context menu
+ added display of segment registers in reg view
+ added background worker to string view, hex view and functions view
+ removed processes we can�t access from the attach dialog

####Notes:
	- Patches can be saved to file (only on the debugged one)
	- In the memory view you can set the protection of a page using the context menu
	- Commandline options
		- "-s": specifies a file
		- "-c": specifies the commandline for the target if not given you will be asked later
		- "-p": attachs to the given pid

###Version 0.1 beta 11
+ fixed a bug in options which didn�t save the correct settings
+ fixed display of exceptions if no symbols have been found
+ fixed a bug which made register editor not working in x64
+ fixed a bug which displayed wrong modules in window view
+ fixed a bug which didn�t display exceptions if a breakpoint was set on this offset
+ fixed a bug in disassembler which may caused application crashes due to wrong memory protection
+ fixed a possible crash in context menus
+ fixed display of the offset in string view
+ fixed unvalid breakpoint offsets caused by alsr
+ improvements on AttachDlg
+ added cleanup on debugge termination
+ added process patching
+ added more context menus to DetailView
+ added display of mainthread in DetailView
+ added F5 Hotkey to reload some views
+ added possibility to save debug log to file
+ added possibility to copy data to clipboard
+ added possibility to break on new Processes, Threads or DLL loads
+ added dockable widgets to the mainview
+ added save of window sizes and positions on close

####Notes:
	- You have now the possibility to patch the memory of a process. Currently it is not possible to save the
	  changes to disk but this will be integrated also.
	- Some context menus offer the possibility to copy the data from the table to the clipboard

###Version 0.1 beta 10
+ fixed a bug which displayed a wrong function offset in callstack
+ fixed a bug which didn�t break on module ep if "break on system ep" was selected
+ fixed a bug which lead to a crash if a wow64 file has ordinal imports
+ fixed a bug in the disassembly view which caused ungentle down scrolling
+ fixed a bug in PEManager which double loaded debugged files
+ fixed a bug which may lead to an error in disassembler
+ fixed a crash on context menus if not debugging something
+ improved HeapView
+ added Message in DebugLog if breaking on MemoryBP
+ added PEViewer
+ added native check for Admin rights
+ added warnings if API import fails
+ added display of current PID/TID in mainwindow title
+ added function view
+ added and cleaned context menus

####Notes:
	- I�m happy to announce "En0mis" as a new Developer in this project! :)
	- function view
		- scans the memory of the loaded targets and scanns for functions.

###Version 0.1 beta 9
+ fixed a bug in disassembler
+ fixed a bug in wow64 StepIn
+ fixed a crash when suspending a process and then StepIn
+ fixed a bug which didn�t display all modules in callstack
+ fixed a crash in loading imports of files without IAT
+ fixed a crash in "Goto Offset" context menu
+ small gui improvements
+ added Single Step Tracer
+ added memory dumper
+ removed error message if you cancel the file selection

####Notes:
	- Single Step Tracer
		- only a part is displayed in the window. Use mouse scroll to navigate (will be improved)
	- MemoryDumper
		- RightClick in MemoryView or HeapView shows you the option to dump the selected segment.

###Version 0.1 beta 8
+ fixed a crash in attaching to a process where we don�t have a file path
+ fixed a bug which ignored DbgBreakPoint on attaching
+ fixed a bug which caused double breaking in case we set a breakpoint while beeing on the entrypoint
+ fixed a crash in pe import reader
+ fixed a crash (see github issue #1)
+ fixed a bug in HexView which didn�t display data on x64 processes
+ fixed a possible crash when opening invalid non pe files
+ fixed a small bug in "Restart"
+ added display of current function in windowtitle
+ added support for drag and drop of files
+ added possibility to remove breakpoints with "F2" (needs to be a selected row in disassembler)
+ added "Step back to user code"

####Notes:
	- "Step back to user code"
		- If you use this the debugger will continue the execution until you get to the first function 
		  which is located in the main module

###Version 0.1 beta 7
+ fixed some small handling bugs
+ fixed a bug in disassembler which did not replace old protection on memory after disassembling
+ fixed a bug which did not show terminated processes in DetailView
+ fixed a bug which did not show terminated threads in DetailView
+ fixed a bug which did not clean up memory on manual debugge stop
+ improved DB handler
+ added resolve of jump conditions to improve StepOver
+ added "Return" and "Backspace" Hotkey to navigate in Disassembler
+ added "Clear Log" context menu in LogBox
+ added "Show Source" context menu in Disassembler
+ added "Goto Function" context menu in Callstack
+ added a crash handler
+ added Source Viewer
+ added memory pool for performance improvment and memory leak reduction
+ added mouse scrolling in disassembler and stack
+ added direkt run of target after using menu to select a file

####Notes:
	- CrashHandler
		- if Nanomite crashs a dumpfile will be written to the application folder. 
		  Please send me this file via zer0fl4g[at]gmail[dot]com
	- Hotkey "Return"
		- when you selected a jump / call / ... you can follow this instruction using the "Return" key
	- Hotkey "Backspace"
		- steps back when you used "Return" to follow a call
	- Source Viewer 
		- double click on source line in Callstack view. A new Window will open and show the source code (if found)
		- right click in disassembler opens source view also
	- Memory Pool
		- redericted malloc / new / delete / free to the memory pool
		- heap fragmentation reduction
		- increasing performance

###Version 0.1 beta 6
+ fixed a crash in Step Over
+ fixed load of colors in option window
+ fixed a dead lock when using detach
+ fixed memory overhead in hexview
+ fixed a display issue of the time in log when the debugge finished
+ improved internal PEFile handling
+ added unload of symbols if a DLL gets unloaded during runtime
+ added some more instructions to syntax highlighter
+ added highlight of current EIP
+ added highlight of BPs
+ added possibility to remove BPs from BPManager
+ added auto completion for apis in BPManager
+ added DB Interface
+ added command line support

####Notes:	
	- BPManager
		-	Use the "DEL" Key to remove the entries from BPManager
		-	Type a module name and the box will propose you found apis that match your entry 
			e.g type "Ker" and the BPManager will show all imports of the processes found with Ker* -> Kernel32::*

###Version 0.1 beta 5
+ fixed missing registers in x64 RegView
+ improved entrypoint handling
+ improved the BPManager
+ added some hotkeys
+ added Step Over
+ added refill on mainwindow resize to match size
+ added RegEdit
+ added basic coloring

####Notes:
	- Hotkeys:	STRG + O = open new file
				STRG + B = breakpoint manager
				STRG + F4 = stop debugging
				F12 = options
				F9 = start debugging / continue
				F8 = step over
				F7 = step in
				F2 = set software breakpoint on selected row (a row must be selected in Disassembler)
	
	- RegEdit:	Double click on the regview to open it
	- Colors:	Can be edited via Options Dialog (F12)

###Version 0.1 beta 4:
+ fixed different crashs in disassembler
+ fixed dependencies of cruntime
+ fixed the restart icon
+ fixed little bug in DetachFromProcess
+ improved speed and memory usage of disassembler
+ added a check for valid file
+ added a check for admin rights + warning
+ added right click menu in RegView (send to Disassembler)
+ added right click menu in Disassembler (Goto Offset) 
+ added possibility to resize and maximize the mainwindow
+ changed window style to Qt Plastique

####Notes:
- dependencies:
	- For developers:	You will need a QT Framework which has been compiled with /MT ( or /MTd) else you
						have a dependencie of the cruntime even if qtNanomite has been compiled without.
						If you need help to compile your QT this way just drop me an Email / PM.
	- For all:			I will place the needed QT Dlls into the repro and you shouldn�t need the cruntime to be installed anymore.


###Version 0.1 beta 3:
+ fixed a bug which displayed crap on some x64 Addresses
+ fixed a crash in the Breakpoint Manager
+ fixed RegView for Wow64
+ added dynamic load of Wow64 APIs (first step to XP64)
+ added right click menu in HeapView (send to HexView)
+ added right click menu in MemoryView (send to HexView)
+ added resizability to the different sub windows
+ added dynamic row calc to stack view (prepare for dynamic main window)
+ added own class and thread for disassembler


###Version 0.1 beta 2:
+ Ported to QT 4.8.4
+ Added possibility to ignore custom exceptions in options dialog
+ Added possibility to reload a default config in options dialog
+ Fixed a bug in the detach function
+ Fixed a crash in CleanWorkSpace
+ Improved Breakpoint Manager