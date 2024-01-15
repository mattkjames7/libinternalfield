setlocal enabledelayedexpansion

:: Get the data directory
set "dataDir=%cd%\data"

cd src
call compile.bat "!dataDir!"
cd ..

