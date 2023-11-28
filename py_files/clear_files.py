def fileClean(fileName):
    fileOpen = open(fileName, "w")
    fileOpen.close()

files = ["thrust.txt", "rthrust.txt", "time.txt"]

for fn in files:
    fileClean(fn)