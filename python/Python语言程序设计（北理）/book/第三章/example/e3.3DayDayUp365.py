# e3.3DayDayUp365.py
import math
dayfactory = 0.01
dayup = math.pow((1.0 + dayfactory),365)
daydown = math.pow((1.0 - dayfactory),365)
print("向上：{:.2f},向下：{:.2f}".format(dayup,daydown))