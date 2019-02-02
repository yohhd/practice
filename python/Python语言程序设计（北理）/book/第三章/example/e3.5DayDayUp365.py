# e3.5DayDayUp365.py
def dayUp(df):
    dayup = 1.0
    for i in range(365):
        if i%7 in [6,0]:
            dayup = dayup * (1-0.01)
        else:
            dayup = dayup * (1+df)
    return dayup
dayfactory = 0.01
while (dayUp(dayfactory)<37.78):
    dayfactory += 0.001
print("每天的努力参数是：{:.3f}".format(dayfactory))
