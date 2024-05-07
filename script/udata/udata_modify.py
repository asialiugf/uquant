import os
import csv
import pandas as pd


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


def process_csv_file(path, file):
    # 打印当前处理的文件名
    print(file)
    # 获取文件大小
    file_name = path + "/" + file
    size = os.path.getsize(file_name)  # 判断文件大小是否大于 10 字节
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

        # 调整列顺序
        order = [
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

        # 指定每列需要保留的小数位数
        decimals = {
            "open": 4,
            "high": 4,
            "low": 4,
            "close": 4,
            "turnover_volume": 0,
            "turnover_value": 0,
            "change": 4,
            "change_pct": 5,
        }

        # 对每列数据进行四舍五入
        csv_df = csv_df.round(decimals=decimals)

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
        # 打印处理后的 DataFrame
        print(csv_df)
        # 将处理后的 DataFrame 保存为 CSV 文件
        csv_df.to_csv(path + "/" + path + "/" + "x_" + file, index=False)


path = "./202305"  # 文件夹目录
files = os.listdir(path)  # 得到文件夹下的所有文件名称
mkdir(path + "/" + path)

for file in files:  # 遍历文件夹
    if not os.path.isdir(file):  # 判断是否是文件夹，不是文件夹才打开
        print(file)
        process_csv_file(path, file)
    break
