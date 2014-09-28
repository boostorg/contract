
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import sys
import os;
import re;
import getopt;
import sh;

def parse_args():
    COMMENT_FOR_FILE = { # Comment line start and end characters.
        '.cpp': ['// ', ''],
        '.hpp': ['// ', ''],
        '.qbk': ['[/ ', ' ]'],
        '.jam': ['# ', ''],
        '.v2':  ['# ', ''],
        '.py':  ['# ', ''],
        '.sh':  ['# ', ''],
        '.bat': ['REM ', ''],
    }
    START_WORD_DFLT = 'Copyright' # Default header starting word.
    HEADER_FILE_DFLT = "../COPYRIGHT.txt" # Default header text file.
    
    try:
        (opts, args) = getopt.getopt(sys.argv[1:], '', [])
        if len(args) == 0:
            raise getopt.GetoptError('Missing DIR argument')
        elif len(args) == 1:
            dir = args[0]
            header_file = HEADER_FILE_DFLT
            start_word = START_WORD_DFLT
        elif len(args) == 2:
            dir = args[0]
            header_file = args[1]
            start_word = START_WORD_DFLT
        elif len(args) == 3:
            dir = args[0]
            header_file = args[1]
            start_word = args[2]
        else:
            raise getopt.GetoptError('Too many arguments')
    except getopt.GetoptError, err:
        print "Error: ", err
        print """
Usage: python %s DIR [HEADER_FILE] [START_WORD]
Replace text starting with the work START_WORD at file's header with the test
from HEADER_FILE.

All files in DIR with the following extensions are recursively processed:
    %s

Defaults:
    HEADER_FILE     %s
    START_WORD      %s
""" % (os.path.split(sys.argv[0])[1], COMMENT_FOR_FILE.keys(),
                HEADER_FILE_DFLT, START_WORD_DFLT)
        exit(1)
    return (dir, header_file, start_word, COMMENT_FOR_FILE)

class header:
    def __init__(self, header_file):
        f = open(header_file, 'rU')
        self.__lines = []
        for ln in f.xreadlines(): self.__lines.append(ln.rstrip('\n'))
        f.close();

    def text(self, line_start = '// ', line_end = ''):
        s = ''
        for ln in self.__lines: s = s + line_start + ln + line_end + '\n'
        return s

class replace_header:
    def __init__(self, header_file, start_word, comment_for_file):
        self.__header = header(header_file)
        self.__start_word = start_word
        self.__comment_for_file = comment_for_file

    def __call__(self, ln, inheader, file_path, line_num):
        if line_num <= 1: sh.info('Updating "' + file_path + '"...')
        (ret_ln, ret_inheader) = ('', None)

        (file_root, file_ext) = os.path.splitext(file_path)
        comment_start = self.__comment_for_file[file_ext][0]
        comment_end = self.__comment_for_file[file_ext][1]
        new_header = '\n' + self.__header.text(comment_start,
                comment_end) + '\n'
        header_start_re = '^' + re.escape(comment_start +
                self.__start_word) + '.*$'
        header_continue_re = '^' + re.escape(comment_start) + '.*$'

        if inheader is None: # At very top of file.
            if re.match('^ *$', ln): # Skip empty lines at top.
                (ret_ln, ret_inheader) = ('', None)
            elif re.match(header_start_re, ln): # Old header starts.
                (ret_ln, ret_inheader) = ('', True)
            else: # Old header ends -- replace it.
                (ret_ln, ret_inheader) = (new_header + ln, False)
        elif inheader:
            if re.match(header_continue_re, ln): # In old header -- skip it.
                (ret_ln, ret_inheader) = ('', True)
            elif re.match('^ *$', ln): # Skip empty lines after old header.
                (ret_ln, ret_inheader) = ('', True)
            else: #  Old header ends -- replace it.
                (ret_ln, ret_inheader) = (new_header + ln, False)
        else: # Not in nor entering header.
            (ret_ln, ret_inheader) = (ln, False)
        return (ret_ln, ret_inheader)

(dir, header_file, start_word, comment_for_file) = parse_args()
replacer = replace_header(header_file, start_word, comment_for_file)
name_re = ''
for file_ext in comment_for_file.keys():
    if name_re != '': name_re = name_re + '|'
    name_re = name_re + '(.*' + re.escape(file_ext) + '$)'

sh.replace(dir, name_re, replacer)

