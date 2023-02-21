import time
import subprocess

def cmd(command):
    subp = subprocess.Popen(command)
    subp.wait(2)
    if subp.poll() == 0:
        print("Success")
    else:
        print("失败")



cmd(["ls", "-l"])
cmd("exit 1")
# subp = subprocess.Popen(["ls", "-l"])
# print(subp)
# subp.wait()