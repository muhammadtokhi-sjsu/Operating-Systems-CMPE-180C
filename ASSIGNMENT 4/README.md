# Operating-Systems-CMPE-180C

Programming Assignment 4: Signal Handlers (SIGINT / SIGUSR1)<br>

Instructions:<br>
1. Compile the `.c` file using the command `cc Signal_Handlers.c -o Signal_Handlers.o`<br>
2. Run the program using the command `./Signal_Handlers.o`<br>

Program behavior:<br>
- The program runs an infinite loop, sleeping for 2 seconds on each iteration.<br>
- By default, the program does not print any iteration information (debug output is off).<br>
- When the process receives `SIGINT` (for example, by pressing `Ctrl+C` in the terminal), it toggles a debug flag:<br>
  - If debug was off, it turns on and the program starts printing a short message showing the current iteration count each loop.<br>
  - If debug was on, it turns off and the program stops printing iteration messages.<br>
- When the process receives `SIGUSR1`, it terminates gracefully and returns exit status `0`.<br>

How to send signals:<br>
1. Start the program: `./Signal_Handlers.o`<br>
2. Note the printed PID (process ID) from the program output.<br>
3. In another terminal, send signals as follows:<br>
   - Toggle debug output on/off: `kill -SIGINT <PID>`<br>
   - Terminate gracefully: `kill -SIGUSR1 <PID>`<br>

Expected output (example):<br>
- On program start, it prints its PID:<br>
  `PID: 12345`<br>
- After sending `SIGINT` once, you will see lines similar to:<br>
  `flag: 1`<br>
  `Iteration: 1`<br>
  `Iteration: 2`<br>
  `Iteration: 3`<br>
  ... every 2 seconds, with the iteration count increasing.<br>
- After sending `SIGINT` again, you will see the flag toggle and iteration printing stop:<br>
  `flag: 0`<br>
- After sending `SIGUSR1`, the program exits cleanly with status code `0` and no further output.<br>

Learning Outcomes:<br>
- Understand how Unix signal handling works in a user-level C program using `sigaction` and custom handlers.<br>
- Practice writing long-running processes that respond asynchronously to external events (signals).<br>
- Gain experience toggling internal program state (debug flag) in response to signals without restarting the process.<br>
- Learn how to terminate a process gracefully with a specific exit status when receiving a designated signal.<br>
- Reinforce skills in compiling, running, and debugging C programs in a Linux environment using the terminal and basic shell tools.<br>
