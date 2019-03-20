# OS - team8
![final5](https://user-images.githubusercontent.com/25524539/54601604-c7cfd080-4a82-11e9-81fd-bd870b4ff151.png)
- Taebum Kim
- Hyunseok Oh
- Seong-hoon Seo

---

# Project 1 - Implementing a New System Call
## Table of Contents
- [Edited Files](#edited-files)
- [High Level Design and Implementation](#high-level-design-and-implementation)
- [Investiagation of Process Tree](#investigation-of-process-tree)
- [Test Result](#test-result)
- [Lessons Learned](#lessons-learned)

## Edited Files
- arch/arm64/include/asm/**unistd.h**
  - Increase the number of total system calls
- arch/arm64/inlcude/asm/**unistd32.h**
  - Add a new system call
- include/linux/**syscalls.h**
  - Add an assembly linkage for a new system call 
- kernel/**Makefile**
  - Add a new rule in Makefile
- include/linux/**prinfo.h**
  - Define prinfo struct for each process
- kernel/**ptree.c**
  - Implement ptree system call
  - Search all running processes by DFS algorithm and return the process tree information
- test/**test_ptree.c**
  - Implement testing file for ptree system call
  
**Total Edited LOC: 153**

## High Level Design and Implementation

(Schematic of program structure)

## Investigation of Process Tree

## Test Result
### Case 1 - nr value 30
![nr 30](https://user-images.githubusercontent.com/25524539/54693633-523f2f80-4b6a-11e9-9c47-7fbc642fac59.png)

- Print process tree with **30** process information
- Return value **30**
- Keep nr value at **30**

---

### Case 2 - nr value 200
![nr 200](https://user-images.githubusercontent.com/25524539/54693640-5408f300-4b6a-11e9-9b2b-8762289a9113.png)

- Print process tree with **entire** process information (**118** in test case)
- Return value **118**
- Change nr value to **118**

---

### Case 3 - nr value 0
![nr 0](https://user-images.githubusercontent.com/25524539/54693649-566b4d00-4b6a-11e9-9de6-90bd518c4ab3.png)

- Return value **-1**
- Keep nr value at **0**


## Lessons Learned
- A journey of a thousand miles begins with a single step.
- Kernel has a quite complex structure more than we have expected.
- Step 0 of development : Hardware checking
- It is hard and important to find appropriate macros in the kernel source.
- 
