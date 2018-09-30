:: PSMoveFreepieBridge.exe -t <ID 1> <ID 2> ... -c <Color for ID 1> <Color for ID 2>...

:: -c flag is optional. Colors use the numbers listed in the prompt when ran without arguments, use -1
:: for its default color (or previously used color, if set prior). Colors are assigned to the ID in the 
:: same position on the -t flag.

:: -x flag will close the console window when PSMoveFreepieBridge finishes.

::The following tracks what is commonly the third controller, with the default color for that controller.
PSMoveFreepieBridge.exe -t 2 -c -1