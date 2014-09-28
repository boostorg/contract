
REM Copyright (C) 2009-2011 Lorenzo Caminiti
REM Use, modification, and distribution is subject to the Boost Software
REM License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
REM copy at http://www.boost.org/LICENSE_1_0.txt).

@ECHO OFF

set BOOST_ROOT=%HOMEDRIVE%%HOMEPATH%\Desktop\code\boost_1_50_0.win
set PATH="C:\PROGRA~2\boost\xml\bin";%BOOST_ROOT%;%PATH%

ECHO HOME=%HOMEDRIVE%%HOMEPATH%
ECHO BOOST_ROOT=%BOOST_ROOT%
ECHO BOOST_BUILD_PATH=%BOOST_BUILD_PATH%
ECHO.
ECHO Make sure "%HOMEDRIVE%%HOMEPATH%\user-config.jam" exists and it is correct

