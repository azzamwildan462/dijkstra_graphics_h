# Dijkstra
Tested on vscode with powershell terminal

## Delete old library if exist
```
rm DB.a
```

## Compile library
```
g++ -c DB.cpp 
ar rvs DB.a DB.o
```

## Compile main program
```
g++ main.cpp DB.a -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```

## Run
```
./a.exe
```

## One command run
```
rm DB.a; g++ -c DB.cpp; ar rvs DB.a DB.o; g++ main.cpp DB.a -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32; .\a.exe
```

## Run fast 
```
g++ main.cpp DB.a -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32; .\a.exe
```