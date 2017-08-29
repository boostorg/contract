# source this `$ source THIS_FILE'.

# Can be executed, for example under Cygwin, to setup enviroment to run
# Microsoft Visual C++ command line compiler `cl.exe'.

msvc="E:\bin\Microsoft Visual Studio 8"
echo "bin/env-MSVC8.sh: Assuming MVSC 8 installed at \"$msvc\" -- is this correct?"

# Setup Cygwin PATH.
export PATH="$PATH:/cygdrive/c/Program Files/Microsoft Visual Studio 8/Common7/IDE:/cygdrive/c/Program Files/Microsoft Visual Studio 8/VC/BIN:/cygdrive/c/Program Files/Microsoft Visual Studio 8/Common7/Tools:/cygdrive/c/Program Files/Microsoft Visual Studio 8/Common7/Tools/bin:/cygdrive/c/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/bin:/cygdrive/c/Program Files/Microsoft Visual Studio 8/SDK/v2.0/bin:/cygdrive/c/WINDOWS/Microsoft.NET/Framework/v2.0.50727:/cygdrive/c/Program Files/Microsoft Visual Studio 8/VC/VCPackages:/cygdrive/c/oracle/ora81/bin:/cygdrive/c/Program Files/Oracle/jre/1.1.7/bin:/cygdrive/c/WINDOWS/system32:/cygdrive/c/WINDOWS:/cygdrive/c/WINDOWS/System32/Wbem:/cygdrive/c/Program Files/TortoiseSVN/bin:/cygdrive/c/Program Files/Windows Imaging/:"

# MSVC INCLUDE for this libray ./include, Boost 1.34.0, and MSVC 8.
export INCLUDE="./include;C:\Program Files\boost\boost_1_34_0;$msvc\VC\ATLMFC\INCLUDE;$msvc\VC\INCLUDE;$msvc\VC\PlatformSDK\include;$msvc\SDK\v2.0\include;"

# MSVC LIB.
export LIB="$msvc\VC\ATLMFC\LIB;$msvc\VC\LIB;$msvc\VC\PlatformSDK\lib;$msvc\SDK\v2.0\lib;"


