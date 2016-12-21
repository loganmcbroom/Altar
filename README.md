This is a non-realtime programmatic audio processing system. 
It is built on Trevor Wishart's CDP tools.
MIT license and all that. You're free to do anything with this besides sell it, if it does something bad I'm not responsible.
Source is here but I don't keep it updated very well: https://github.com/loganmcbroom/Altar
Any questions, comments, or fat stacks can be sent to loganmcbroom@gmail.com

Setup =============================================================

You'll need to download the cdp here: http://www.unstablesound.net/cdp.html
Install that somewhere.
If you're grabbing this out of my google drive delete Settings.lua if it exists
Open Altar.exe and it will ask for a _cdprogs folder 
Navigate to the cdpr7 directory and select cdpr7/_cdp/_cdprogs
If neither of us messed it up, Altar is ready to go

You will also need:
If you want to spend more than a quick sec looking at this you'll need a code editor of some kind for Lua.
I rec notepad++. Once installed and opened you can hit Language->L->Lua for proper highlighting. 
It also has some nice color options in Settings->Style Configurator (I rec Solarized).
	
You'll need audio of some sort. 
Record youself saying your name if you can't think of anything.
If you need some quality sources send me an email.

Usage==============================================================

Firstly, you need to put some audio into Altar. You can use the file button, or just drag and drop files from your computer.
The files should appear on the left column (The input column).

Nextly you'll need to describe what you want to do to the audio in a script. The text box at the top of Altar decides what script is run. 
By default, Altar.lua is run, so pop Altar.lua open in your favorite text editor.
All that is possible is listed here: http://www.ensemble-software.co.uk/CDPDocs/html/cdphome.htm
You can access (almost) all of these processes through functions Altar adds to the Lua enviornment.
You can also access all your input files using f[1] through f[n]. unpack( f ) accesses all the input files.
For example, if you want to take the first input and force it to max volume you could write "return modify_loudness( 4, f[1] )".
Maybe you want to make all your inputs go to half the max volume? Write "return modify_loudness( 4, "-l0.5", unpack( f ) )".

Finally, click that pi button in Altar. It will start a new thread in the middle column and start churning audio.
If it runs into an error it will be displayed in the logger at the bottom. Otherwise it will eventually say [PROCESSING END].
If it works out, any outputs you returned from the script will be listed in the right column (output column).
You can listen to it, save it if you like it, and if it needs more poking you can drag it back to the input column for further manipulation.

===================================================================

Linear Transformation Multi Processing:
Processes mapping a set number of inputs to a set number of outputs use a special functionality called the LTMP system.
This is what allows "return modify_loudness( 4, "-l0.5", unpack( f ) )" to work with any number of files.
It runs the described function on each input file and returns all outputs.

There is an additional functionality for using LTMP. Take a look at this code.
	return distort_average( {5, 10, 15}, unpack( f ) )
Assuming 5, 10, and 15 are valid inputs for that parameter, this will apply those values cyclically to each input coming from unpack.
Note: distort_average only takes mono files, although with a quick bit of code you can use it on multichannel files

How about this:
	return distort_average( {5, 10, 15}, f[1] )
This is also valid, it will return 3 files, each a copy of f[1] with distort_average applied with the listed parameters

The LTMP system is likely the most powerful feature in Altar so make sure you give it a try!

===================================================================

Extra stuff you need to know:
Flags like -l0.5 always go in quotes. You can combine flags into single arguments in a single pair of quotes e.g. "-l0.5 -z".
The order of arguments is mode (if applicable), parameters, flags, files.
Don't expect everything to work, I haven't tested the majority of processes. A lot of it works though.
If you want to use something in the spectral domain you have to use pvoc_anal( 1, files ) first, and pvoc_synth( files ) after.
A lot of processes only take mono files. Use housekeep_chans in mode 2 or 4 to split stereo to mono.
Here is a function for putting those mono files back into stereo files:
	function makestereo( ... )
		local arg = {...}
		local stereos = {}
		for i = 1, #arg/2 do stereos[i] = multichannel_interlx( arg[2*i-1], arg[2*i] ) end
		return unpack( stereos )
	end
If you are using channels beyond stereo you are competent enough to figure it out.
Audio at different sample rates? Use housekeep_respec( 1, 48000, files ).

===================================================================

I worked really hard on this so if you make something neat send me a copy! 
And if you have any CDP questions try the forum here: http://unstablesound.net/cdpforum/index.php?board=3.0
I check it a lot.
 - Logan McBroom

