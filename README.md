# Altar
GUI and friends for programming with the Composers Desktop Project.

This is a system for working with the CDP using Lua. It consists of a gui for dealing with input and output files, a Lua script describing how the audio should be processed, and a set of (currently just one actually) c functions to be called from Lua to invoke CDP modules.

Drag files in, hit the pi and see what pops out. 

On the Lua side, use the cdp function to invoke any module. The first argument is taken as the name of the module (e.g. "modify"), subsequent arguments are simply added as command line argument with a space between them. There are some special tokens you can but into cdp that will be replaced. Here is the current list of token replacements:
$ -> Replaced by an unused file name in the working directory with a .wav extension. Wherever you need an outfile name use this.

Depends on Lua and JUCE. You'll need the Composers Desktop Project installed with the _cdprogs directory set in the Altar.lua script, as well as an arbitrary working directory, also set in Altar.lua. 
