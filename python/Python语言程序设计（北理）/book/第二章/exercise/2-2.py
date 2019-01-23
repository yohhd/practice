MoneyStr = input("请输入带符号的钱数：")
if  MoneyStr[-1]  in ['D','d']:
    Y = eval(MoneyStr[0:-1]) * 6.0
    print("转换后的温度是{:.2}Y".format(Y))
elif MoneyStr[-1] in ['Y','y']:
    D = eval(MoneyStr[0:-1]) / 6.0
    print("转换后的温度是{:.2}D".format(D))
else:
	print("输入格式错误")

