# intel-os - A wide-variety of important os capabilities that are implemented in the form of a operating system.

This repository was the center for storing all projects relating to the course **Operating Systems**, CSC 4100. This course was taken during my second senior semester.

The concepts that I worked on are seen below. Each concept builds on the last to successfully make a barebones intel operating system.

 * [Simple Boot](https://github.com/justincpresley/intel-os/tree/master/simple_boot)
 * [Cooperative Multitasking](https://github.com/justincpresley/intel-os/tree/master/cooperative_multitasking)
 * [Preemptive Multitasking](https://github.com/justincpresley/intel-os/tree/master/preemptive_multitasking)

Throughout every concept, I did include extra features and make the code modular.

If you would like to try out any of the concepts that are implemented, the following requirements are needed for the following reasons:

 * **nasm**: compiling the intel assembly code
 * **gcc**: compiling the c code
 * **objcopy**: removing extra symbols and such that my os can not handle
 * **ld**: link object code into a executable
 * **bximage**: create a image
 * **mkdosfs**: make the image microsoft compatible
 * **dd**: convert the image
 * **mcopy**: modify the image
 * **qemu-system-i386**: running and debug an image

All of above is either standard on a Linux distro already or can simply be installed through a package tool.

For Build instructions, please see the "Makefile" corresponding to the concept that you are running. For simplest option, you can just run "make complete" which will build, install, and begin running the os.

NOTE: This is repository is an archive representing previous experience / knowledge.
