Edison Jr.
==========

#### Prerequisites

For a complete guide to install MiniAT go to [miniat.org](http://www.miniat.org/getting-started/build)

- SDL2
- MiniAT

Make sure you are able to run the example on [miniat.org](http://www.miniat.org/getting-started/running-an-example) before you run Edison Jr.

#### Download Edison Jr.

##### Using Git:
- Clone it into your systems directory of MiniAT ` miniat/system/ `  
` cd ~/miniat/systems/ `  
` git clone https://bitbucket.org/miniat_amos/edison_jr.git `  

#### Environment paths for Edison Jr.
Edison Jr. requires the user to add a path to the image directory.
##### Temporary path  
Bash:  
- Add the image path which Edison Jr. uses  
` export EDISON_PATH=~/miniat/system/edison_jr/SDL/images/ `  

Tcsh:  
- Add the image path  
` setenv EDISON_PATH ~/miniat/system/edison_jr/SDL/images/ `  

If your wish to have this path added every time you are in terminal then add the command to your ` .bash_profile `, ` .bashrc `, or ` .profile ` file



#### Running Edison Jr. Examples
- Run the command from your ` miniat ` dir  
- First test and see if Edison Jr. loads  
` miniat_edisonJr out/bin/hello_world.bin `  
- Now to run the example that has some functionality  
` miniat_edisonJr out/bin/example1.bin `  
- You can also run our segment display test  
` miniat_edisonJr out/bin/testssd.bin `  
