# Unreal P2P Tutorial Project

This project will help you to give an example of how to integrate P2P Feature using the AccelByte SDK into your current project. If you need a guide on how to configure Unreal SDK into your current project, you can follow https://docs.accelbyte.io/initial-setup/sdk-guides/unreal-engine-sdk-getting-started.html.

## Setup Project

1. Click the `Setup.bat` file to add all of AccelByte Submodules into the project.
2. Go to `OssTutorialProject.uproject` by accessing `<FolderCloneDestination>/OssTutorialProject` and right click at `OssTutorialProject.uproject`, select `Generate Visual Studio project files`.
3. After the generating Visual Studio done, there will be `OssTutorialProject.sln` ready to be opened. You can also opening Solution with other IDE, but we recommend you using Visual Studio 2019 since it's already tested and works well.
4. Build the project by clicking `Local Windows Debuger` or `Ctrl + F5` buttons to build the project and run it.

## How to Test the game

### Run using Batch File

1. Make sure you have build the project.
2. Run `StartClient.bat` by accessing `<FolderCloneDestination>` and the game will be run in standalone game.

### Run using Unreal Editor

1. Open `OssTutorialProject.uproject` by accessing `<FolderCloneDestination>/OssTutorialProject`. You need to rebuild if you build the project for the first time.
2. Click small arrow in the right `Play` button.
3. Change the number of players in the multiplayer options into 2.
4. Change from play using selected viewport into standalone game.
