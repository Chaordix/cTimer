# cTimer - High Precision Timer Extension

`cTimer` provides a nanosecond-precision timer to Python.

##Usage

	import cTimer as timer
	
	start = timer.start()
	
	# Do a bunch of things here that take some time.
	
	checkpoint = timer.checkpoint()
	
	# Do some more time-vampire things here.
	
	stop = timer.stop()
	
	print timer.diff(start, stop) # Total execution time
	print timer.diff(start, checkpoint) # Execution time of first half
	print timer.diff(checkpoint, stop) # Execution time of second half
	
	print timer.get() # Time since cTimer was imported

## Methods

**`start()`** - returns an `int` referencing the current time stamp.

**`checkpoint()`** - returns an `int` referencing the current time stamp.

**`stop()`** - returns an `int` referencing the current time stamp.

**`diff(int A, int B)`** - returns the difference between two timestamp references provided by `start()`, `checkpoint()` or `stop()`. Order does not matter, result is always a positive `float` representing seconds.

**`get()`** - returns the number of seconds as a `float` since the `cTimer` library was `import`ed.

## Installation

Clone the repository into a new folder. Run the following commands (you *may* need to `sudo` the second one):

	python setup.py build
	python setup.py install

## Notes

This is a lightweight extension and has not been thouroughly tested on all combinations of platforms and Python versions.

It has been tested on CentOS 5, Ubuntu 10.4, and OSX 10.5 to 10.8 using Python 2.7 and Python 3.2. All platforms were 64-bit.

This *should* work with 32-bit hosts, but that has not been tested yet.

This *does not* work on Windows hosts yet.