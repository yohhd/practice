import turtle
i = 0
while i<=500:
    i  = i+5
    turtle.seth(90)
    turtle.fd(i)
    turtle.seth(180)
    turtle.fd(i)
    i = i+5
    turtle.seth(270)
    turtle.fd(i)
    turtle.seth(0)
    turtle.fd(i)