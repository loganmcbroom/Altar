# Altar
GUI and friends for programming with the Composers Desktop Project. Drag files in, hit the pi and see what pops out. 

Here's documentation of all processes: http://www.ensemble-software.co.uk/CDPDocs/html/cdphome.htm
For Altar, functions are named with a shorthand for the module, an underscore, and the process name e.g. modify loudness becomes mod_loudness(). Modes are always the first argument if needed. Files go at the end, and if it takes a set number of files and maps them to a set number of outputs you can send any number of files in as long as the total files is divisible by the fixed input size. Wrap flags with quotes e.g. foo_bar( 8, "-f16000", file ). Processes that output data into the console aren't supported (the output is hard to mind for the actual data). Good luck!

Depends on Lua and JUCE. You'll need the Composers Desktop Project installed with the _cdprogs directory set in the Settings.lua script, as well as an arbitrary working directory, also set in Settings.lua. 
