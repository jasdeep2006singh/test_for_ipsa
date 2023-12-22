import subprocess
import os
import tqdm
time_max=0
for i in tqdm.trange(500):
    #out=subprocess.check_output("time ./a.out",shell=True)
    os.system("/usr/bin/time --output=outtime -p sh -c './a.out > /dev/null'")
    file=open("outtime","r")
    file.seek(0)
    f=file.readline()
    file.close() 
    #print(f)    
    time=f[5:9]
    #print(time)
    #print(type(time))
    #t=float(time)
    if float(time)>time_max:
        time_max=float(time)
print(time_max)