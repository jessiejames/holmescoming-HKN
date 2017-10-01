import serial
import Tkinter
import tkMessageBox
from Tkinter import *
import datetime
import time
import tkFont
import os
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

    
gui = Tkinter.Tk()
gui.configure(cursor = "crosshair", bg = "black")
gui.title("HKN Holmescoming Dashboard")
gui.geometry("1920x1080")

player_font = tkFont.Font(size= 35)
score_font = tkFont.Font(size = 100)
start_font = tkFont.Font(size = 20)
time_font = tkFont.Font(size = 35)
logo = PhotoImage(file = 'logo.gif')


p1 = 0
p2 = 0
time1 = datetime.datetime.now()

def read_score():
    score_file = open('output.txt', "r")
    for line in score_file:
        scores = line
    score_file.close()
    scores = line.split()
    #player1, player 2, round
    win_score = scores[2] #score to win
    p1 = scores[0]  #player 1 score
    p2 = scores[1]  #player 2 score
    blue_score.set(p1)
    orange_score.set(p2)
    if((int(p1) >= (int(win_score) +1)) or (int(p2) >= (int(win_score) + 1))):
        if(int(p1) > int(p2)):
            time_label.config(text = "Tesla wins!", bg = "blue")
        elif(int(p2) > int(p1)):
            time_label.config(text = "Curie wins!", bg = "orange")
        else:
            time_label.config(bg = "green")
    gui.after(100, read_score)
    
def end_python():
    sys.exit()
    
gui.protocol('WM_DELETE_WINDOW', end_python)

def en_game():
    time1 = datetime.datetime.now()
    time_elapsed()
    read_score()
    time_label.configure(bg = "green")    

label = Label(image = logo, bg = "black")
label.grid(column = 2, row = 1, padx = 600, pady = 25)

b1 = Tkinter.Button(gui, text = "Start", font = start_font, command = en_game, cursor = "crosshair")
b1.grid(column = 2, row = 2)

time_label=Label(gui,justify='center', font = time_font, relief = "sunken", cursor = "crosshair", bg = "red", pady = 10)
time_label.config(text = "Disabled", font = 'times 25')
time_label.grid(column = 2, row = 3, pady = 25)

def time_elapsed():
    time2 = datetime.datetime.now()
    t = str(time2-time1)
    t = t[2:-3]
    time_label.config(text=t,font='times 25')
    gui.after(100,time_elapsed)


blue_pl = StringVar()
blue_pl.set("Tesla")
stat_indicator = Message(gui, textvariable = blue_pl, font = player_font, relief = "sunken", width = 500, cursor = "crosshair", bg = "blue")
stat_indicator.grid(column = 1, row = 4, pady = 50)


orange_pl = StringVar()
orange_pl.set("Curie")
stat_indicator = Message(gui, textvariable = orange_pl, font = player_font, relief = "sunken", width = 500, cursor = "crosshair", bg = "orange")
stat_indicator.grid(column = 3, row = 4, pady = 50)

blue_score = StringVar()
stat_indicator = Message(gui, textvariable = blue_score, font = score_font, relief = "sunken", width = 500, cursor = "crosshair", bg = "gray")
stat_indicator.grid(column = 1, row = 5, pady = 50)

orange_score = StringVar()
stat_indicator = Message(gui, textvariable = orange_score, font = score_font, relief = "sunken", width = 500, cursor = "crosshair", bg = "gray")
stat_indicator.grid(column = 3, row = 5, pady = 50)



if __name__ == '__main__':
    gui.mainloop()

