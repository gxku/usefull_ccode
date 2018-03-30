
import pygame
import pygame.draw
import pygame.time
from euclid import *
from ponycube import * 
'''
s = [i / 100.0 for i in range(314)]

print "roll changing..."
for r in s:
    q = Quaternion(1,0,0,0)
    print q.rotate_euler(0, r, 0)

#print "pitch changing..."
#for p in s:
#    q = Quaternion(1,0,0,0)
#    print q.rotate_euler(0, 0, p)

#print "yaw changing..."
#for y in s:
#    q = Quaternion(1,0,0,0)
#    print q.rotate_euler(y, 0, 0)

print q.get_matrix()
'''
def fake_data_show():
    s = [i / 100.0 for i in range(314)]

    print "roll changing..."
    for r in s:
        q = Quaternion(1,0,0,0)
        q.rotate_euler(r,0,0)
        cube.draw(screen,q)
        pygame.display.flip()
        pygame.time.delay(50) 
        cube.erase(screen)

def file_data_show():
    file = open("result.txt") 
    for line in file:
        q = Quaternion(1,0,0,0)
        q.rotate_euler(float(line.split()[2]),float(line.split()[0]),float(line.split()[1]))
        cube.draw(screen,q)
        pygame.display.flip()
        pygame.time.delay(5000) 
        cube.erase(screen)


if __name__ == "__main__":
    pygame.init()
    screen = Screen(800,800,scale=1.5)
    cube = Cube(120,12,120)
    q = Quaternion(0,1,0,0)
    #incr = Quaternion(0.96,0.01,0.01,0).normalized()

    print q.get_matrix()

    while True:
        #fake_data_show()
        file_data_show()

