TP Assignment 2 - Operating Systems 2025/2026
Chat Application based on Named Pipes (FIFOs)


Made By:
- Name: Baris Efe Turkmen | Student Number: m323031 | Student Mail: m323031@alunos.ipb.pt
- Name: Dumitru Vleju | Student Number: m323241 | Student Mail: m323241@alunos.ipb.pt

1. OVERVIEW
This application implements a multi-user chat room using Linux Named Pipes 
(FIFOs) as the primary Inter-Process Communication (IPC) mechanism. 
The system follows a client-server architecture where a central server manages 
client registration and message dissemination.

2. ARCHITECTURE
- server.c: Manages the chat room, registers new clients (S1), and broadcasts 
  incoming messages to all active readers (S2).
- client-writer.c: Collects user input and sends it to the server's central 
  FIFO (C1).
- client-reader.c: Creates a private FIFO based on its PID and displays 
  messages received from the server (C2).
- same.h: Common header containing data structures (Message struct) and 
  constants.

3. COMPILATION
To compile the application, we have to do the following commands in the terminal:
   gcc server.c -o server
   gcc client-reader.c -o reader
   gcc client-writer.c -o writer

4. EXECUTION INSTRUCTIONS
To run a single chat instance with multiple clients, follow these steps:

Step 1: Start the Server
   Open a terminal and run: ./server

Step 2: Connect Clients (Each client requires TWO terminals)
   For Client A:
   - Terminal 2: Run ./reader 
   - Terminal 3: Run ./writer
   
   For Client B:
   - Terminal 4: Run ./reader
   - Terminal 5: Run ./writer

5. IMPLEMENTATION DETAILS
- The server uses a well-known FIFO (/tmp/chat_server_fifo) to listen for messages.
- Each reader creates a unique private FIFO (/tmp/client_[PID]_fifo) to receive 
  broadcasted messages without interference.
- The server dynamically registers up to 10 clients by tracking their PIDs.
- Independent processes are used for writing and reading to simulate a real-time 
  chat environment as specified in the assignment.

6. CLEANUP
- Closing the server will unlink the central server FIFO.
- Closing a client-reader will unlink its private PID-based FIFO.
