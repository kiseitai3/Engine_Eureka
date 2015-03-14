swig.exe -help
swig.exe -c++ -Wall -E -python ..\..\swig_test.i
swig.exe -c++ -Wall -python ..\..\Eureka.i 
swig.exe -c++ -Wall -lua -o ..\..\Eureka_lua.cxx ..\..\Eureka.i  
pause