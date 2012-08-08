#!/usr/bin/env python
"""
cTimer: A high resolution, high precision timer.
"""

import os
import sys

from distutils.core import setup, Extension

if sys.platform == 'darwin':
	module1 = Extension('cTimer',
		sources = ['cTimer.c'])
else:
	module1 = Extension('cTimer',
		sources = ['cTimer.c'],
		extra_link_args = ['-lrt'])

f = open(os.path.join(os.path.dirname(__file__), 'ReadMe.md'))
long_description = f.read()
f.close()
version = '0.1.1'

setup (
    name = 'cTimer',
	version = version,
	description = 'A high precision timer.',
    long_description = long_description,
	author = 'Chaordix (Russ Porosky)',
	author_email = 'russ@chaordix.com',
	url = 'https://github.com/chaordix/cTimer/',
    download_url = ('https://github.com/downloads/Chaordix/cTimer/cTimer-%s.tar.gz' % version),
	maintainer = 'Chaordix (Russ Porosky)',
	maintainer_email = 'russ@chaordix.com',
    keywords = ['timer', 'precision'],
    license = 'MIT',
    platforms = 'ALL',
    classifiers=[
        'Development Status :: 4 - Beta',
        'Environment :: Console',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
        'Programming Language :: Python',
        'Programming Language :: Python :: 2.5',
        'Programming Language :: Python :: 2.6',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.2',
        'Programming Language :: Python :: 3.3',
        ],
    ext_modules = [module1]
)
