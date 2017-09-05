
REM Copyright (C) 2008-2012 Lorenzo Caminiti
REM Distributed under the Boost Software License, Version 1.0
REM (see accompanying file LICENSE_1_0.txt or a copy at
REM http://www.boost.org/LICENSE_1_0.txt)
REM Home at http://sourceforge.net/projects/contractpp

@ECHO OFF

set BOOST_ROOT=%HOMEDRIVE%%HOMEPATH%\Desktop\code\boost\trunk.windows
set PATH="C:\Program Files (x86)\boost\xml\bin";%BOOST_ROOT%;%PATH%

ECHO HOME=%HOMEDRIVE%%HOMEPATH%
ECHO BOOST_ROOT=%BOOST_ROOT%
ECHO.
ECHO Make sure "%HOMEDRIVE%%HOMEPATH%\user-config.jam" exists and it is correct

