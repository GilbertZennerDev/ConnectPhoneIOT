import subprocess as sp

def test():
    print("Testing iot.py")

    limx = limy = 1000
    distance = 50
    startid = 0
    endid = 2
    phonescount = 10000
    for distance in range(100, 10, -10):
        print('distance', distance)
        cmds = ['python3', 'iot.py', str(phonescount), str(startid), str(endid), str(distance), str(limx), str(limy)]
        sp.run([*cmds])

if __name__ == "__main__":
    test()