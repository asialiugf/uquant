# https://udata.hs.net/help/294
from hs_udata import set_token,stock_list        # 引入hs_udata模块中set_token和stock_list
set_token(token = 'O984HHV9p7m4y4rNOeEgCSLlROSIfct6y6gvXYqxRwqWO2yJOTZnVPOalmGrUsLV')        # 设置Token
data = stock_list()                            # 获取 股票列表数据，返回格式为dataframe
print(data.head())                                # 打印数据前5行
data.to_csv('stock_list.csv',sep=',',encoding='utf_8_sig')     # 写出CSV文件
