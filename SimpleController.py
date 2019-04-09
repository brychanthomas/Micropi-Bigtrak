from tkinter import *
import requests

IP="192.168.4.1"

previousSelection=0

def update(): #check what is selected every 0.2 seconds
    global previousSelection
    if selection.get() != previousSelection:
        previousSelection = selection.get()
        if selection.get() == 1:
            send_speeds(150,150)
        elif selection.get() == 2:
            send_speeds(-150,150)
        elif selection.get() == 3:
            send_speeds(150,-150)
        elif selection.get() == 4:
            send_speeds(-150,-150)
        else:
            send_speeds(0,0)
    root.after(200, update)

def send_speeds(left, right): #send speeds to Bigtrak with a POST request
    if left < 0:
        leftNegative = 1
        left=left*-1
    else:
        leftNegative = 0
    if right < 0:
        rightNegative = 1
        right=right*-1
    else:
        rightNegative = 0
    args = '?l='+str(left)+'&r='+str(right)+'&ln='+str(leftNegative)+'&rn='+str(rightNegative)
    print(args)
    try:
        r = requests.post("http://"+IP+"/"+args,timeout=0.2)
    except Exception as e: #if connection timed out or closed by Bigtrak (it doesn't send a response)
        print("sent")

def forwards(event): #when up arrow pressed
    f.select()

def left(event): #when left arrow pressed
    l.select()

def right(event): #when right arrow pressed
    r.select()

def backwards(event): #when down arrow pressed
    b.select()

def stop(event): #when space key pressed
    s.select()

root = Tk()
selection = IntVar()
f=Radiobutton(root,text="Forwards",variable=selection,indicatoron=0,value=1,font=("Courier", 30),width=10)
f.pack()
l=Radiobutton(root,text="Left",variable=selection,indicatoron=0,value=2,font=("Courier", 30),width=10)
l.pack()
r=Radiobutton(root,text="Right",variable=selection,indicatoron=0,value=3,font=("Courier", 30),width=10)
r.pack()
b=Radiobutton(root,text="Backwards",variable=selection,indicatoron=0,value=4,font=("Courier", 30),width=10)
b.pack()
s=Radiobutton(root,text="STOP",variable=selection,indicatoron=0,value=5,font=("Courier", 30),width=10)
s.pack()

root.after(200, update) #run the 'update' function in 0.2 seconds

root.bind('<Up>', forwards) #bind keys to functions
root.bind('<Down>',backwards)
root.bind('<Left>',left)
root.bind('<Right>',right)
root.bind('<space>',stop)
root.mainloop() #open window
