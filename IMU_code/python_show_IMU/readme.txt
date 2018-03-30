give euler to show status ;
like below:

'''
s = [i / 100.0 for i in range(314)]

print "roll changing..."
for r in s:
    q = Quaternion(1,0,0,0)
    q.rotate_euler(0, r, 0)

#print "pitch changing..."
#for p in s:
#    q = Quaternion(1,0,0,0)
#    q.rotate_euler(0, 0, p)

#print "yaw changing..."
#for y in s:
#    q = Quaternion(1,0,0,0)
#    q.rotate_euler(y, 0, 0)
