set imageName="gtcs2110/hw05-spring24:latest"

docker container ps > nul 2>&1
if "%errorlevel%" neq "0" (
    echo ERROR: Docker not found. Ensure that Docker is installed and is running before running this script. Refer to the CS 2110 Docker Guide.
    exit /b 1
)

echo Attempting to pull down most recent image of %imageName%...
docker pull %imageName%
if "%errorlevel%" neq "0" (
    echo ERROR: Unable to pull down the most recent image of %imageName%
    exit /b 1
)

set curDir=%cd%

docker run --rm -i -v "%curDir%:/autograder/submission/" %imageName% "//autograder/run_local"