from pytdx.hq import TdxHq_API
from pytdx.params import TDXParams
import pandas as pd
pd.set_option('display.max_rows', None)
# from pandas.core.frame import DataFrame
api = TdxHq_API()
api.connect('119.147.212.81', 7709)
c0 = api.get_history_transaction_data(TDXParams.MARKET_SZ, '000001', 0, 4000, 20230613)
c1 = api.get_history_transaction_data(TDXParams.MARKET_SZ, '000001', 2000, 4000, 20230613)
c2 = api.get_history_transaction_data(TDXParams.MARKET_SZ, '000001', 4000, 4000, 20230613)
c3 = api.get_history_transaction_data(TDXParams.MARKET_SZ, '000001', 6000, 4000, 20230613)
data0=pd.DataFrame(c0)#将字典转换成为数据框
data1=pd.DataFrame(c1)#将字典转换成为数据框
data2=pd.DataFrame(c2)#将字典转换成为数据框
data3=pd.DataFrame(c3)#将字典转换成为数据框
print(data3)
print("-------------------------------------------------------------")
print(data2)
print("-------------------------------------------------------------")
print(data1)
print("-------------------------------------------------------------")
print(data0)

#data4 = data3 + data2 + data1 + data0
print("---------------------------------------------------------------------------------")
data4 = pd.concat([data3,data2,data1,data0],ignore_index=True)

print(data4)
