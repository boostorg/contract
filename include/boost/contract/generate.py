
import fnmatch
import os

for root, dirs, files in os.walk('.'):
    for file in fnmatch.filter(files, '*-generate.py'):
        cwd = os.getcwd()
        os.chdir(root)
        os.system("python " + file)
        os.chdir(cwd)

