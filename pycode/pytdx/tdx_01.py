from pytdx.hq import TdxHq_API
from pytdx.params import TDXParams
import pandas as pd

pd.set_option("display.max_rows", None)
# from pandas.core.frame import DataFrame
api = TdxHq_API()
api.connect("119.147.212.81", 7709)
c3 = api.get_security_list(1, 1000)

data3 = pd.DataFrame(c3)  # 将字典转换成为数据框
print(data3)
