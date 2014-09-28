
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import sys
import os
import shutil
import re
import tempfile
import time

silent = False

def info(msg, newline = True):
    if not silent:
        if newline: print msg
        else: sys.stdout.write(msg)

def err(msg):
    print "Error:", msg

def run(cmd):
    if os.system(cmd) != 0:
        err('Unable to execute command "' + cmd + '"')
        exit()

def quit_if_exist_is(path, exist, err_msg = ""):
    if os.access(path, os.F_OK) == exist:
        if err_msg == "":
            if not exist: err('File path "' + path + '" not found')
            else: err('File path "' + path + '" already exists')
        else: err(err_msg)
        exit()

def cp(src, dst):
    info("Copying: " + src + " -> " + dst)
    quit_if_exist_is(src, False)
    if os.path.isdir(src):
        quit_if_exist_is(dst, True) # `copytree()` requires dst not exist.
        shutil.copytree(src, dst)
    else:
        shutil.copy2(src, dst)

def mkdir(dir):
    if not os.access(dir, os.F_OK): os.makedirs(dir)

def read(msg = '', default = ''):
    if msg != '': info(msg, False)
    s = raw_input()
    if s == '': s = default
    return s

def rm(path, interactive = True):
    if os.access(path, os.F_OK):
        if interactive: user_in = ''
        else: user_in = 'y'
        while user_in != 'y' and user_in != 'n':
            user_in = read(
                'Warning: If "y", existing file(s) will be lost!\n' +
                'Override existing path "' + path + '"? (y/n) ')
        if user_in == 'y':
            if os.path.isdir(path): shutil.rmtree(path)
            else: os.remove(path)
        else:
            err('Unable to override existing path "' + path +
                    '" -- manually remove it first')
            exit()

def find(dir, name_re, exec_func = None):
    found = []
    for root, dirs, files in os.walk(dir):
        for dir in dirs:
            path = os.path.join(root, dir)
            if re.match(name_re, path):
                if not exec_func is None: exec_func(path)
                found.append(path)
        for file in files:
            path = os.path.join(root, file)
            if re.match(name_re, path):
                if not exec_func is None: exec_func(path)
                found.append(path)
    return found

# Can be passed as `replace_func` to `replace()` for simple text replace.
class replace_text:
    def __init__(self, find_re, repl_txt):
        self.__find_re = find_re
        self.__repl_txt = repl_txt
    def __call__(self, ln, unused, file_name, line_num):
        return (re.sub(self.__find_re, self.__repl_txt, ln), unused)

def replace(dir, name_re, replace_func, data = None):
    class _replace_func:
        def __init__(self, func, data):
            self.__func = func
            self.__data = data
        def __call__(self, ifile_name):
            ifile = open(ifile_name, 'rU')
            ofile_name = ifile_name + str(time.time()) # Time for temp file.
            ofile = open(ofile_name, 'w')
            func = self.__func
            data = self.__data # Copy data so self's data not changed.
            ln_num = 0
            for ln in ifile.xreadlines():
                ln_num = ln_num + 1
                (repl_ln, repl_data) = func(ln, data, ifile_name, ln_num)
                data = repl_data # Update data within this file replacement.
                ofile.write(repl_ln)
            ifile.close()
            ofile.close()
            os.remove(ifile.name)
            os.rename(ofile.name, ifile.name)
    f = _replace_func(replace_func, data)
    find(dir, name_re, f)

