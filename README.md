<h2>Application for visualizing sorting algorithms made in C++ using openFrameworks</h2>  

<h3>Two modes available:</h3>  
Learning mode\
Visualization mode\
\
<h3>Implemented algorithms:</h3>  
Bubble sort\
Insertion sort\
Merge sort\
Quicksort\
Radix sort\
Selection sort\
\
Feel free to use, share or modify the application.\
If you have any questions regarding the code, found some bug that you want to report or simply want\
to improve the application in any way, please create an issue.\
\
<h3>Hotkeys:</h3>
F - full screen\
H - hide UI\
R - reset array\
\
\
\
<h3>How to setup the project on Windows for Visual Studio.</h3>  
1. Download openFrameworks for Visual Studio from: https://openframeworks.cc/download/\
3. Follow the steps here: https://openframeworks.cc/setup/vs/\
4. Download the following addon: https://github.com/frauzufall/ofxGuiExtended/ and put it into the addons folder in your openFrameworks directory\
5. Use the project generator found in projectGenerator folder in your openFramework directory to create a new project. Select ofxGuiExtended addon\
6. Download the source files from this repository and copy them to your project's folder\
7. Open the project in Visual Studio\
8. Click Project -> YourProjectName Properties or press alt + f7\
9. Under C/C++ -> General select "Additional Include Directories" and press edit. Here you have to add every directory from this repository\
For example "src\helpers", "src\service\display", "src\services\logic" and so on. This step is needed in order for the compiler to find the required files\ 
If any folder is missing you will get a compile error but it should be relatively easy to figure our which folder is missing based on error messages\
9. After all is done the program should be ready to compile\
  
<h3>How to add a new sorting algorithm:</h3>
1. The easiest way is just to copy an existing class and rename it\
You have to remember to rename not only the files themselves but also the classes inside the files\
2. Open SortDefinitions.h and create a new SortType\
3. Open SortFactory.cpp and add references to your SortType\
4. All that is left is to create your own sorting implementation. It will be easier to start with visualization mode implementation\ 
5. In order to test your implementation you will need to add a button for your algorithm AlgoritmSelectionView.cpp\
