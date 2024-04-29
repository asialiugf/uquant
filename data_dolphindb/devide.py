import os
import csv
import pandas as pd
import numpy as np


def mkdir(path):
    # 去除首位空格
    path = path.strip()
    # 去除尾部 \ 符号
    path = path.rstrip("/")
    # 判断路径是否存在
    print(path)

    isExists = os.path.exists(path)
    # 判断结果
    if not isExists:
        os.makedirs(path.encode("utf-8"))
        return True
    else:
        return False


def process_csv_file(path, file,p0,p1):
    # 打印当前处理的文件名
    print(file)
    temp = file.split("_", 3)
    print(temp[0])
    print(temp[1])
    print(temp[2])
    f0 = temp[0] + "_" + temp[1][0:6] + ".csv"
    f1 = temp[0] + "_" + temp[2][0:6] + ".csv"
    print(f0)
    print(f1)

    ech0 = "echo \"      \" > " + "./" + p0 + "/" + f0
    ech1 = "echo \"      \" > " + "./" + p1 + "/" + f1
    os.popen(ech0)
    os.popen(ech1)

    # 获取文件大小
    file_name = path + "/" + file
    size = os.path.getsize(file_name)  # 判断文件大小是否大于 10 字节
    if size < 10:
        # print(file_name + "00000000000000000")
        cpp0 = "cp " + file_name +" " + "./" + p0 + "/" + f0
        cpp1 = "cp " + file_name +" " + "./" + p1 + "/" + f1 
        os.popen(cpp0)
        os.popen(cpp1)
        return()
    if size > 10:
        # 读取 CSV 文件
        csv_data = pd.read_csv(
            file_name,
            encoding="utf-8-sig",  # 指定编码方式
            low_memory=False,  # 关闭内存优化
        )

        csv_df = pd.DataFrame(csv_data)
        # 删除"Unnamed: 0"这一列
        if "Unnamed: 0" in csv_df.columns:
            csv_df.drop(columns=["Unnamed: 0"], inplace=True)

        """
        # 调整列顺序
        order = [
            "stockid",
            "market",
            "date",
            "time",
            "open",
            "high",
            "low",
            "close",
            "turnover_volume",
            "turnover_value",
            "change",
            "change_pct",
        ]
        csv_df = csv_df[order]
        """

        # 指定每列需要保留的小数位数
        decimals = {
            "open": 4,
            "high": 4,
            "low": 4,
            "close": 4,
            "turnover_volume": 0,
            "turnover_value": 4,
            "change": 4,
            "change_pct": 5,
        }

        # 对每列数据进行四舍五入
        csv_df = csv_df.round(decimals=decimals)

        csv_df['open'] = csv_df['open'].map('{:.4f}'.format)
        csv_df['high'] = csv_df['high'].map('{:.4f}'.format)
        csv_df['low'] = csv_df['low'].map('{:.4f}'.format)
        csv_df['close'] = csv_df['close'].map('{:.4f}'.format)
        csv_df['turnover_value'] = csv_df['turnover_value'].map('{:.4f}'.format)
        csv_df['change_pct'] = csv_df['change_pct'].map('{:,.5f}'.format)
        csv_df['change'] = csv_df['change'].map('{:.5f}'.format)
        #csv_df['change_pct'] = csv_df['change_pct'].map('{:.5f}'.format)
        #csv_df['date']=pd.to_datetime(csv_df['date'],format="%Y%m%d")


        dg =  csv_df.groupby(csv_df.date.str[0:7])
        tt0 = p0[0:4] + "-" + p0[4:6] 
        tt1 = p1[0:4] + "-" + p1[4:6] 
        for t,i in dg:
            #print(t)
            #print(tt0)
            if(t==tt0):
                #print(i)
                i.to_csv("./" + p0 + "/" + f0)
            if(t==tt1):
                #print(i)
                i.index = np.arange(0, len(i))
                i.to_csv("./" + p1 + "/" + f1)
            if(t!=tt0 and t!=tt1):
                print (file_name + "----------------------------------------------")

        return()

        # 将第一行和第二行的"turnover_volume"和"turnover_value"相加
        csv_df.loc[1, "turnover_volume"] += csv_df.loc[0, "turnover_volume"]
        csv_df.loc[1, "turnover_value"] += csv_df.loc[0, "turnover_value"]
        # 删除第一行
        csv_df.drop(index=0, inplace=True)

        # 将 time 列转换为时间类型
        # csv_df["time"] = pd.to_datetime(csv_df["time"], format="%H%M").dt.time
        csv_df["time"] = pd.to_datetime(csv_df["time"], format="%H%M").dt.strftime(
            "%H:%M"
        )
        csv_df["date"] = pd.to_datetime(csv_df["date"], format="%Y-%m-%d")
        """
        # 修改date的格式由 2023-09-01 改为 20230901
        csv_df["date"] = pd.to_datetime(csv_df["date"], format="%Y-%m-%d").dt.strftime(
            "%Y%m%d"
        )
        """
        """
        csv_df['open'] = csv_df['open'].map('{:,.4f}'.format)
        csv_df['high'] = csv_df['high'].map('{:,.4f}'.format)
        csv_df['low'] = csv_df['low'].map('{:,.4f}'.format)
        csv_df['close'] = csv_df['close'].map('{:,.4f}'.format)
        csv_df['turnover_value'] = csv_df['turnover_value'].map('{:,.4f}'.format)
        csv_df['change'] = csv_df['change'].map('{:,.5f}'.format)
        csv_df['change_pct'] = csv_df['change_pct'].map('{:,.5f}'.format)
        """
        csv_df['open'] = csv_df['open'].map('{:.4f}'.format)
        csv_df['high'] = csv_df['high'].map('{:.4f}'.format)
        csv_df['low'] = csv_df['low'].map('{:.4f}'.format)
        csv_df['close'] = csv_df['close'].map('{:.4f}'.format)
        csv_df['turnover_value'] = csv_df['turnover_value'].map('{:.4f}'.format)
        #csv_df['change'] = csv_df['change'].map('{:.5f}'.format)
        #csv_df['change_pct'] = csv_df['change_pct'].map('{:.5f}'.format)
        #csv_df['date']=pd.to_datetime(csv_df['date'],format="%Y%m%d")
        csv_df['date']=pd.to_datetime(csv_df['date'].dt.strftime("%Y/%m/%d"))


        order = [
            "stockid",
            "market",
            "date",
            "time",
            "open",
            "high",
            "low",
            "close",
            "turnover_volume",
            "turnover_value",
        ]
        csv_df = csv_df[order]
        # 打印处理后的 DataFrame
        # print(csv_df)
        # 将处理后的 DataFrame 保存为 CSV 文件
        csv_df.to_csv(path + "/" + path + "/" + "x_" + file, index=False)


path = "./20221101_20221231"  # 文件夹目录
path_temp = path.split("/", 1)
xxx = path_temp[1].split("_",1)
print(xxx[0])
print(xxx[1])
path0=xxx[0][0:6]
path1=xxx[1][0:6]
print(path0)
print(path1)
files = os.listdir(path)  # 得到文件夹下的所有文件名称
mkdir(path0)
mkdir(path1)

for file in files:  # 遍历文件夹
    if not os.path.isdir(file):  # 判断是否是文件夹，不是文件夹才打开
        # print(file)
        process_csv_file(path, file,path0,path1)
    #break
