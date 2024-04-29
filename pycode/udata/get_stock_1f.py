import datetime
import calendar
import time

# 引入hs_udata模块中set_token和stock_list
from hs_udata import set_token, stock_list
from hs_udata import set_token, stock_quote_minutes

# 设置Token
set_token(token='O984HHV9p7m4y4rNOeEgCSLlROSIfct6y6gvXYqxRwqWO2yJOTZnVPOalmGrUsLV')
data = stock_list()

print(data.hs_code)

for i in range(len(data.hs_code)):
    print('第{}个元素为：{}，其index为：{}'.format(
        i, data.hs_code.iloc[i], data.hs_code.index[i]))

now = datetime.datetime.now()
year = now.year
month = now.month

for n in range(1):
    year = 2022
    month = 2
    last_day = calendar.monthrange(year, month)[1]
    start = datetime.date(year, month, 1).strftime('%Y%m%d')
    end = datetime.date(year, month, last_day).strftime('%Y%m%d')
    print(start)
    print(end)
    # for
    for i in range(len(data.hs_code)):
        print('第{}个元素为：{}，其index为：{}'.format(
            i, data.hs_code.iloc[i], data.hs_code.index[i]))
        dat = stock_quote_minutes(
            en_prod_code=data.hs_code.iloc[i], begin_date=start, end_date=end)
        print(dat)
        time.sleep(0.1)
        filename = "../data/" + data.hs_code.iloc[i] + "_" + \
            str(start) + "_" + str(end) + ".csv"
        print(filename)
        dat.to_csv(filename, sep=',', encoding='utf_8_sig')
