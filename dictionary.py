from PyDictionary import PyDictionary
import os
import inspect
def get_module_dir():
    mod_file = inspect.getfile(inspect.currentframe())
    mod_dir = os.path.dirname(mod_file)
    return mod_dir

def open_input_file(file, mode="rt"):
    mod_dir = get_module_dir()
    test_file = os.path.join(mod_dir, file)
    return open(test_file, mode)

dic=PyDictionary()
f = open_input_file("words.txt")
f2 = open_input_file("inputs.txt","a")
lines = []
c=0
while True:
    line = f.readline()
    if not line:
        break
    x=PyDictionary.meaning(line)
    if x is not None:
        f2.write(line[:-1]+" "+str(x)+"\n")
        c+=1
    print(c)
f2.close()