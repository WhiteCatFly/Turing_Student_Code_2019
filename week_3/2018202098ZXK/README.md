# Spider of RUC
A navie spider that you can use your own config file.
#Config
Your config file should be like the default one  
default.ini: #please ignore #  
Web_Base=http://econ.ruc.edu.cn/ #must has the ending char /  
Num_Thread=100 #number of threads  
Time_Sleep=300 #in microseconds  
Num_Tries=2 #try at most 2 times  
Time_Out=2 #in seconds  
Error_File=errfile.data #override the errfile if there exists one  
# Usage
If you don't provide the config file, use the default.ini automaticly.
```bash
$ make
0 ./prog [your config file]
```
# Output

Crawled webs will be saved in the current working directory.
