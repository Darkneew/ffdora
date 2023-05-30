# FFdora

## How to use? 

First make sure you have everything you need. You will need a GCC cross-compiler to compile the OS. You can find instructions [here](https://wiki.osdev.org/GCC_Cross-Compiler#Preparing_for_the_build) to build it. You will also need qemu to launch the code, if you want to test it. Our bash script automatically launches qemu-i286. 

When everything is ready, download this repository and open a terminal inside. Make sure your cross-compiler and qemu are accessible from your folder, for exemple by specifying it in the global $PATH variable. Then, just type `make` and let the magic happen. To delete all unecessary files after you are done, type `make clean`.

If you only want to build the kernel, run `./build.sh`. If you only want to build the iso, run `./iso.sh`
