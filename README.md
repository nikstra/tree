# tree
A Unix/Linux version of the MS-DOS tree command.

tree README file
================

First of all, this is the first program I've
written for the Unix patform. Thus, there may
be some things that looks a bit awkward or work
in a way not common to Unix platforms.

I got the idea for this little program from my
classmate Anna. She asked if there was a command
on Solaris 7 similar to the MS-DOS command tree.
As far as I know, there isn't.
That's why I wrote tree.

tree simply prints the directory structure as a
graphical tree on the screen. Very similar to
the MS-DOS command tree.

In the output form tree, directory names ends with a
slash ( e.g. "dirname/" ), if a file is a link an at sign
is appended to the name ( e.g. "linkname@" ).

By typing "tree" alone at the prompt, the command displays
the directory tree from the current directory and
down throug all sub directories.

If you type a path as argument to tree, it will display
all sub directories of the directory in the path.

You can use the following switches to alter the output
of tree:

	-a	By default, tree doesn't display hidden directories
		or files. With -a, all dirs ( and files ) are displayed,
		including dirs ( and files ) beginning with a dot.

	-f	Display files in every directory. Whitout -f, only
		directories are displayed.

	-s	Sort output. With -s all output is sorted alphabetically.

	-v	Display version information. Use alone only.

	-h	Display a simple help text. Use alone only.


e.g.

	List all sub directories and files in the /etc directory
	and sort the output alphabetically:

	$ tree -afs /etc

	List only directories and hidden directories in current directory:

	$ tree -a

Author:
Niklas Strand

