# Multi-Threaded Programming & Deadlock Detection

## **Project Overview**
This project is designed to demonstrate **multi-threading**, **deadlock detection**, and **inter-process communication (IPC)** using **C++**. It simulates **banking transactions** between customer accounts, illustrating how improper thread synchronization can lead to **deadlocks** and how a monitor can detect and recover from them.
## **Usage**
- **Multi-threading**: Simulates concurrent transactions between multiple bank accounts.
- **Deadlock Creation**: Demonstrates how improper thread locking can cause a deadlock.
- **Deadlock Avoidance**: Implements **lock ordering** to prevent deadlocks.
- **Deadlock Detection & Recovery**: A **monitor thread** detects circular waits and recovers by unlocking resources.
- **Inter-Process Communication (IPC)**: Implements **pipes** for data transfer between processes.

---

## **SetUp**
- Linux Environment (Virtual Machine was used to create)
- C++ Complier (g++)

## **Installation**
- Open Linux based 
- Clone the repository: git clone https://github.com/riakau/Multi-Threaded-and-IPC-Implementatons.git
- Change Directory: cd Multi-Threaded-and-IPC-Implementatons

## **Know Problems**
- **Printing of Banking threads activiy is difficult to read
- **Implementations are mostly hard-coded

