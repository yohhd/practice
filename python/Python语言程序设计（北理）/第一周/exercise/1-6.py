diet = ['西红柿','花椰菜','黄瓜','牛娃','虾仁']
for x in range(0,5):
    for y in range(0,5):
        if  not(x==y):
            print("{}{}".format(diet[x],diet[y]))