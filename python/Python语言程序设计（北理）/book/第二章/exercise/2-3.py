import turtle as t 
week = ['black','grey','darkgreen','gold','violet','purple','green','red'] 
def drawSnake(radius,angle,length): 
    t.seth(-40)
    for i in range(length):
        t.pencolor(week[i%8])
        t.circle(radius,angle)
        t.pencolor(week[(i+1)%8])
        t.circle(-radius,angle)
    t.circle(radius,angle/2)
    t.fd(40)
    t.circle(16,180)
    t.fd(40*2/3)
t.setup(650,350,200,200)
t.penup()
t.fd(-250)
t.pendown()
t.pensize(25)
drawSnake(40,80,6)
t.done()
