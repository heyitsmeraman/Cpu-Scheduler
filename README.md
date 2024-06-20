# CPU Scheduler 

-used to Schedule Processes according with different algorithms: FCFS, SJF(Preemptive/Non-Preemptive), Priority(Preemptive/Non-Preemptive) and Round Robin.
- Displaying Gannt Chart, burst time, turnaround time and remaining time for each process.


# project Description :

A CPU scheduler, also known as a process scheduler, is a crucial component of an operating system responsible for determining which processes or threads should be executed by the CPU at any given time. Its main goal is to manage the execution of processes in a way that maximizes CPU utilization and ensures efficient and fair process execution.

Key Functions of a CPU Scheduler
Process Selection: The scheduler selects processes from the ready queue (a list of processes that are ready to be executed) based on a specific scheduling algorithm.

Context Switching: When the scheduler switches the CPU from one process to another, it performs a context switch. This involves saving the state of the currently running process and loading the state of the next process to be executed.

Resource Allocation: The scheduler allocates CPU resources to processes, balancing the needs of various processes to optimize performance and responsiveness.

# How to run the project :
clone the repo to your and run the .exe file 


# Internal Working of the projects :

For this particular project QTcreator was used to make to project.
Qt Creator is a powerful integrated development environment (IDE) designed primarily for developing applications using the Qt application framework. Qt is widely used for developing cross-platform applications with graphical user interfaces, but it also supports non-GUI applications. Qt Creator provides a comprehensive set of tools to facilitate development, including a code editor, design tools, and debugging features.
Creating a CPU scheduler in C++ using Qt Creator involves several steps, from setting up the development environment to implementing the scheduling algorithms.

Project Structure :

# main.cpp: Entry point of the application.

This code is the starting point for a Qt application, which is a type of program with a graphical user interface. Here's explanation:

Including Necessary Parts:
The code begins by including two important files. One file sets up the main window of the application, and the other manages the overall application and its resources.

Setting Up Variables:
It defines several global variables, which are used throughout the program:

Arrays and a temporary variable for storing information about processes.
A queue for managing process IDs or related numbers.
Two integers, possibly for counting processes and storing user choices.
Main Function:
The main part of the program does the following:

Initializes the application with command-line arguments.
Creates the main window of the application.
Makes the main window visible on the screen.
Starts the event loop, which keeps the application running and responsive to user interactions until the user closes the main window.
In short,this code sets up a basic Qt application with a main window and starts it, allowing it to run and interact with the user.

# mainwindow.cpp:
This code is for a Qt application where the main window allows users to input parameters for a CPU scheduling algorithm. Here's a simplified summary:

Includes and Declarations:

The code includes necessary Qt libraries and headers for user interface elements.
It also includes a custom header (sub_window.h) and declares several global variables (condition, time_slice, num, ch) that are used throughout the program.
Main Window Initialization:

The MainWindow class is initialized, which represents the main window of the application.
User interface elements are set up (setupUi function sets up the UI defined in mainwindow.ui).
Input Handling:

When the user clicks the "Input" button (pushButton_Input), the program reads the number entered in a text field (QLineEdit_Process_Num).
Depending on which radio button (algorithm) is selected:
It sets a global variable (ch) to indicate the chosen algorithm.
Depending on the algorithm chosen (FCFS, NSJF, PSJF, RR, PR, or PR_2), additional input might be required (like entering a time slice for Round Robin (RR) scheduling).
If the user selects an algorithm and inputs a valid number of processes (num), it opens a sub-window (sub_window) where further details can be entered.
Validation and Error Handling:

It checks if the user has selected an algorithm and entered a valid number of processes.
It handles cases where input is missing or invalid, displaying warning messages (QMessageBox) to guide the user.
Sub-Window Interaction:

If all conditions are met (num and algorithm selected), it opens a modal sub-window (sub_window) for additional input related to the chosen scheduling algorithm.
This code essentially sets up the interface and logic for configuring a CPU scheduling algorithm through a Qt GUI, ensuring user inputs are validated and guiding them through the process step by step.

# priority.cpp :
This code defines a priority queue data structure and operations for managing processes based on their priority levels. Here’s a simplified explanation:

Comparison Function (comparePriority):

Defines a function comparePriority that compares two processes based on their priority (pr).
If two processes have the same priority, it compares them based on their burst time (bt).
PriorityQueue Class:

Insertion (insert):

Adds a new process to the priority queue (processes vector).
Ensures the heap property (higher priority processes are at the root) by bubbling up the newly inserted process.
Extraction (extractMin):

Removes and returns the process with the highest priority from the priority queue (processes vector).
Places the last process at the root and maintains the heap property by bubbling down the root to find the correct position for the next highest priority process.
Empty Check (isEmpty):

Checks if the priority queue is empty by verifying if the processes vector has any elements.
Key Points:
Priority Handling: Processes are managed based on their priority values, ensuring that higher priority processes are processed first.
Heap Operations: Insertion and extraction operations maintain the heap property, where the highest priority process is always accessible quickly.
Error Handling: There's a commented-out section (if (processes.empty())) for handling an empty queue scenario, suggesting a potential way to handle errors if the queue is empty during extraction.
This code is essential for implementing scheduling algorithms like Priority Scheduling, where processes with higher priorities are given preference for execution over lower priority ones.

# subwindow.cpp :
This code appears to be a simulation of various CPU scheduling algorithms using Qt and C++. Here’s a summarized explanation of what it does:

Initialization: The program initializes a GUI window using Qt, sets up a table to display process information, and prepares a graphical scene for visualizing process execution.

Process Input: Users can input process details (ID, arrival time, burst time, etc.) through the GUI, and these details are stored in arrays (p[] and p1[]) for further processing.

Algorithms Implemented:

FCFS (First Come, First Served): Processes are executed in the order they arrive.
SJF (Shortest Job First):
Non-preemptive: Executes the shortest job among available processes.
Preemptive: If a shorter job arrives while another is running, it switches to the new job.
Priority Scheduling: Processes with higher priority execute first.

Visualization: The execution of processes is visualized using graphical elements (rectangles) in the Qt scene. Each process's execution is depicted with a colored rectangle moving across a timeline.

Output: After simulation completes, it displays the turnaround time and waiting time for each process in a table.

Interaction: Users can interact with the simulation through buttons and checkboxes to control live updates and start the simulation.

Overall, the program provides a visual and numerical representation of how different CPU scheduling algorithms work and their impact on process execution times.

# Learnings:
Building a CPU scheduler using Qt Creator involves combining core concepts of CPU scheduling algorithms with graphical user interface (GUI) development. Here are some key learning takeaways:

Integration of Algorithms with GUI: Understanding how to integrate complex algorithms (such as round robin, priority scheduling) with Qt's graphical components is crucial. It requires managing data structures, algorithms, and real-time visual updates effectively.

Visualization and User Interaction: Implementing visual feedback (like timelines, process execution bars) helps in understanding the behavior of scheduling algorithms. It enhances user experience and aids in debugging and optimizing algorithms.

Event Handling and Multithreading: Qt's event-driven architecture necessitates handling events, especially during simulation delays and updates. Understanding when and how to process events without blocking the main thread is important for smooth GUI operation.

Data Structures and Algorithms: Working with priority queues, sorting algorithms, and data management techniques (like array manipulation, dynamic memory allocation) is critical for implementing scheduling algorithms efficiently.

Real-time Simulation Challenges: Dealing with real-time updates and synchronization (e.g., updating graphical elements while ensuring correctness of algorithmic operations) provides insights into managing concurrent tasks in GUI applications.

Performance Considerations: Balancing between real-time updates for visualization and algorithmic efficiency requires careful design. Qt's profiling tools can help identify performance bottlenecks and optimize code.

Error Handling and Debugging: Implementing error handling mechanisms and debugging techniques (using Qt's debugging tools and logging) is essential for identifying and fixing issues in complex GUI applications.

Software Design Patterns: Applying design patterns (such as MVC - Model-View-Controller) for separating concerns between GUI, algorithmic logic, and data management helps in maintaining a modular and scalable codebase.

User Feedback and Iterative Development: Incorporating user feedback during iterative development cycles helps in refining the GUI design, enhancing usability, and improving overall user experience.

Documentation and Collaboration: Documenting code, especially when integrating complex algorithms with GUI elements, aids in code maintenance and collaboration among team members.

Overall, building a CPU scheduler with Qt Creator provides valuable experience in integrating computational logic with modern GUI frameworks, making it a rewarding learning opportunity for software development and systems programming.


# Resources and references : 
i refered to the resourses provide by the club and youtube (their is a video on how to make simulator)
and with senoir help who is good at gui creation.