TempStr = input("请输入温度符号：")
Temp = eval(input("请输入温度值："))
if  TempStr  in ['F','f']:
    C = (Temp-32)/1.8
    print("转换后的温度是{:.0}C".format(C))
elif TempStr in ['C','c']:
    F = 1.8 * Temp + 32
    print("转换后的温度是{:.0}F".format(F))
else:
	print("输入格式错误")

