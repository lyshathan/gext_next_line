# Get Next Line Project 📖

The **Get Next Line** project aims to create a function that reads a line from a file descriptor, including the newline character. The goal is to implement a program that works without using standard library functions like `getline`, and handles reading from files or standard input efficiently.

---

## 🛠️ How to Get Started

1. **Clone the repository**:
   ```bash
   git clone git@github.com:lyshathan/GNL.git
   cd get_next_line
   ```

2. **Compile the project**:
   Using `Makefile` to compile your code:
   ```bash
   make
   ```

3. **Run the project**:
   After compiling, you can test your `get_next_line` function with a sample program:
   ```bash
   ./get_next_line
   ```

---

## 📝 Project Overview

- **get_next_line**: The main function reads from a file descriptor, returning one line at a time, up until the end of the file or the newline character is encountered.
- **Handling Memory**: Efficient memory management is essential. You need to handle dynamic memory allocation and ensure there are no memory leaks.
- **File Handling**: The function should work with files, and also with input from standard input (`stdin`).

---

Good luck, and may your lines be clear! 🎉
