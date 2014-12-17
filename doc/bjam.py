
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import os
import sys
import shutil

# Simple script that customizes Boost's navbar before building the docs.
# Unfortunately, Boost does not have mechanism to customize its navbar
# (essentially only on/off is supported), this script replaces files manually.

BOOST_ROOT = os.getenv("BOOST_ROOT")
boost_navbar = BOOST_ROOT + "/tools/boostbook/xsl/navbar.xsl"
backup_navbar = "navbar.xsl.bak"
my_navbar = "navbar.xsl"

args = " "
for i in range(1, len(sys.argv)): args = args + sys.argv[i] + " "

print 'Saving Boost "navbar.xsl"...'
shutil.copyfile(boost_navbar, backup_navbar)

try:
    print 'Installing customized "navbar.xsl"...'
    shutil.copyfile(my_navbar, boost_navbar)
    print 'Building documentation...'
    print
    os.system("bjam" + args + " bjampy")
    print
except:
    print 'Error: Unable to build documentation'

try:
    print 'Restoring Boost "navbar.xsl"...'
    shutil.copyfile(backup_navbar, boost_navbar)
except:
    print 'Error: Unable to restore Boost "navbar.xsl"'

